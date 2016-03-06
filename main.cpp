#ifdef WIN32
	#include <windows.h>
#endif

#define GLFW_DLL
#include<GLFW/glfw3.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "tests.h"
#include "program.h"

using namespace std;

Program prog;
GLFWwindow *window;
int w, h;
double mouseX, mouseY;

void renderPoints_NURBS()
{
	for (int i = 0; i < prog.ctrlPts.size(); i++)
	{
		float psize = fmax(2, prog.weights[i] * 2);
		if (prog.selectedIdx == i)
			psize += 1;

		glPointSize(psize);
		glBegin(GL_POINTS);

		if (prog.selectedIdx == i)
			glColor3f(1, 1, 1);
		else
			glColor3f(0.0f, 1.0f, 0.0f);

		glVertex2f((*prog.ctrlPts[i]).x, (*prog.ctrlPts[i]).y);
		glEnd();
	}
}

void renderPoints_BSpline()
{
	glPointSize(5.0);
	glBegin(GL_POINTS);

	for (int i = 0; i < prog.ctrlPts.size(); i++)
	{
		if (prog.selectedIdx == i)
			glColor3f(1, 1, 1);
		else
			glColor3f(1, 0, 1);

		glVertex2f((*prog.ctrlPts[i]).x, (*prog.ctrlPts[i]).y);
	}
	glEnd();
}

void renderGeometric()
{
	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 0.0f);

	for (int i = 0; i < prog.geoPts.size() - 1; i++)
	{
		glVertex2f((*prog.geoPts[i]).x, (*prog.geoPts[i]).y);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(1.0f, 0.0f, 0.0f);
	for (int i = 0; i < prog.convexPts.size(); i++)
	{
		glVertex2f((*prog.convexPts[i]).x, (*prog.convexPts[i]).y);
	}
	glEnd();

	int idx = prog.geoPts.size() - 1;
	glBegin(GL_POINTS);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f((*prog.geoPts[idx]).x, (*prog.geoPts[idx]).y);
	glEnd();
}

void render() {
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Functions for changing transformation matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Functions for changing projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -1, 1);

	// Render the control points
	if (prog.nurbs_on)
		renderPoints_NURBS();	
	else
		renderPoints_BSpline();

	// Render the curve
	glBegin(GL_LINE_STRIP);
	glColor3f(1.0f, 0.0f, 1.0f);

	for (int i = 0; i < prog.splinePts.size(); i++)
	{
		glVertex2f((*prog.splinePts[i]).x, (*prog.splinePts[i]).y);
	}
	glEnd();

	// Geometric display  (bspline only)
	if (!prog.nurbs_on && prog.state == Program::State::ON_CURVE)
		renderGeometric();
}

void keyboard(GLFWwindow *sender, int key, int scancode, int action, int mods) {
	if ((action == GLFW_PRESS || action == GLFW_REPEAT))
		switch (key)
	{
		case GLFW_KEY_A:
			cout << "A was pressed.\n";
			break;
		case GLFW_KEY_MINUS:
				prog.modifyStep(0.01);
			break;
			case GLFW_KEY_EQUAL:
				prog.modifyStep(-0.01);
				break;
			case GLFW_KEY_N:
				prog.toggleNurbs();
				break;
		case GLFW_KEY_ESCAPE:
			printf("Exciting..\n");
			glfwSetWindowShouldClose(window, GL_TRUE);
			return;
	}
}

void mouseClick(GLFWwindow *sender, int button, int action, int mods) {
	if (action == GLFW_PRESS){
		prog.mouseClick(button, mouseX, mouseY);
	}

	if (action == GLFW_RELEASE){
		prog.mouseRelease();
	}

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		cout << mouseX << ' ' << mouseY << '\n';
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	prog.modifyOrder((int)yoffset);
}

void mousePos(GLFWwindow *sender, double x, double y) {
	double newMouseX = (x / w) * 2 - 1;
	double newMouseY = (y / h) * (-2) + 1;

	prog.mouseDrag(mouseX, mouseY, newMouseX, newMouseY);
	
	mouseX = newMouseX;
	mouseY = newMouseY;
}

int main() {

    Tests t = Tests();
	if (!glfwInit())
		return 1;

	window = glfwCreateWindow(640, 480, "My Window", NULL, NULL);
	if (!window)
		return 1;

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, keyboard);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouseClick);
	glfwSetCursorPosCallback(window, mousePos);
	while (!glfwWindowShouldClose(window)) {
		glfwGetFramebufferSize(window, &w, &h);
		glViewport(0, 0, w, h);

		render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

