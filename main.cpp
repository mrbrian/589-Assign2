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

using namespace std;

GLFWwindow *window;
int w, h;
double mouseX, mouseY;

vector<double> cx, cy;
int selected = -1;
int selectDistance = 0.05;

void render() {
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Functions for changing transformation matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	/*	glTranslatef (0.0f, 0.5f, 0.0f);
	glRotatef (30.0f, 0.0f, 0.0f, 1.0f);
	glScalef (2.0f, 2.0f, 2.0f); */

	//Functions for changing projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -1, 1);
	//gluPerspective (fov, aspect ratio, near plane, far plane)
	//glFrustum

	glPointSize(5.0);
	//We draw a line on the screen, which gets transformed by the modelview matrix
	glBegin(GL_POINTS); //GL_LINE_STRIP, GL_POINTS, GL_QUADS, etc...
	glColor3f(1.0f, 1.0f, 1.0f);
	for (int i = 0; i < cx.size(); i++)
	{
		glVertex2f(cx[i], cy[i]);
	}
	glEnd();
}


void keyboard(GLFWwindow *sender, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT))
		cout << "A was pressed.\n";
}

void mouseClick(GLFWwindow *sender, int button, int action, int mods) {
	if (action == GLFW_PRESS){
		for (int i = 0; i < cx.size(); i++){
			if (abs(cx[i] - mouseX) <= selectDistance &&
				abs(cy[i] - mouseY) <= selectDistance){
				selected = i;
			}
		}
		if (button == GLFW_MOUSE_BUTTON_LEFT && selected == -1){
			cx.push_back(mouseX);
			cy.push_back(mouseY);
		}
		if (button == GLFW_MOUSE_BUTTON_RIGHT && selected > -1){
			cx.erase(cx.begin() + selected);
			cy.erase(cy.begin() + selected);
			selected = -1;
		}
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

	if (selected > -1){
		cx[selected] = mouseX;
		cy[selected] = mouseY;
	}
}

int main() {

    Tests t = Tests();
return 0;
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

