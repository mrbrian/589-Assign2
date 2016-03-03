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

int selected = -1;

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

	glPointSize(5.0);
	//We draw a line on the screen, which gets transformed by the modelview matrix
	glBegin(GL_POINTS); //GL_LINE_STRIP, GL_POINTS, GL_QUADS, etc...
	glColor3f(1.0f, 1.0f, 1.0f);
	for (int i = 0; i < prog.points.size(); i++)
	{
		glVertex2f(prog.points[i].x, prog.points[i].y);
	}
	glEnd();

	glBegin(GL_LINE_STRIP); //GL_LINE_STRIP, GL_POINTS, GL_QUADS, etc...
	glColor3f(1.0f, 0.0f, 1.0f);

	for (int i = 0; i < prog.splinePoints.size(); i++)
	{
		glVertex2f(prog.splinePoints[i].x, prog.splinePoints[i].y);
	}
	glEnd();
}


void keyboard(GLFWwindow *sender, int key, int scancode, int action, int mods) {
	if ((action == GLFW_PRESS || action == GLFW_REPEAT))
		switch (key)
	{
		case GLFW_KEY_A:
			cout << "A was pressed.\n";
			break;
		case GLFW_KEY_EQUAL:
			prog.modifyOrder(1);
			printf( "Spline order: %d\n", prog.getOrder());
			break;
		case GLFW_KEY_MINUS:
			prog.modifyOrder(-1);
			printf("Spline order: %d\n", prog.getOrder());
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
		selected = -1;
	}

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		cout << mouseX << ' ' << mouseY << '\n';
}

void mousePos(GLFWwindow *sender, double x, double y) {
	mouseX = (x / w) * 2 - 1;
	mouseY = (y / h) * (-2) + 1;

	/*if (selected > -1){		
		cx[selected] = mouseX;
		cy[selected] = mouseY;
	}*/
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

