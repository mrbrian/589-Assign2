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
#include "program.h"

using namespace std;

int w, h;
Program prog;
GLFWwindow *window;
double mouseX, mouseY;

void render() 
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Functions for changing transformation matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Functions for changing projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -1, 1);

	// Render the curves
	prog.render();
}

void keyboard(GLFWwindow *sender, int key, int scancode, int action, int mods)
{
	if ((action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		switch (key)
		{
		case GLFW_KEY_A:
			cout << "A was pressed.\n";
			break;
		case GLFW_KEY_MINUS:		// change curve step increment
			prog.modifyStep(0.01);
			break;
		case GLFW_KEY_EQUAL:		// change curve step increment
			prog.modifyStep(-0.01);
			break;
		case GLFW_KEY_N:			// toggle between nurbs or b-spline curve
			prog.toggleNurbs();
			break;
		case GLFW_KEY_ESCAPE:
			printf("Exiting..\n");
			glfwSetWindowShouldClose(window, GL_TRUE);
			return;
		}
	}
}

void mouseClick(GLFWwindow *sender, int button, int action, int mods) 
{
	if (action == GLFW_PRESS){
		prog.mouseClick(button, mouseX, mouseY);
	}

	if (action == GLFW_RELEASE){
		prog.mouseRelease();
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	prog.modifyOrder((int)yoffset);
}

void mousePos(GLFWwindow *sender, double x, double y) 
{
	double newMouseX = (x / w) * 2 - 1;
	double newMouseY = (y / h) * (-2) + 1;

	prog.mouseDrag(mouseX, mouseY, newMouseX, newMouseY);	
	
	mouseX = newMouseX;
	mouseY = newMouseY;
}

int main() 
{
	if (!glfwInit())
		return 1;

	window = glfwCreateWindow(640, 480, "My Window", NULL, NULL);
	if (!window)
		return 1;

	printf("CPSC589 Assignment2\n");

	glfwMakeContextCurrent(window);
	
	// mouse/keyboard input callbacks
	glfwSetKeyCallback(window, keyboard);
	glfwSetScrollCallback(window, scroll_callback);		
	glfwSetMouseButtonCallback(window, mouseClick);
	glfwSetCursorPosCallback(window, mousePos);

	while (!glfwWindowShouldClose(window)) 
	{
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

