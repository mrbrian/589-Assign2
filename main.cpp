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
#include "point3D.h"
#include <vector>
#include <stdio.h>

#define RAD_STEP	M_PI / 180	// step size for rendering circles/hypocycloid
#define STEP        0.01		// step size for modifying values via keyboard

int delta(float u, int m, int k)
{
    for (i=0; i <= m+k-1; i++)
    {
       if (u>=U[i] && u<U[i+1])
           return i;
    }
    return -1;
}

int main () {

    if (!glfwInit()) {
        std::cout << "Could not initialize.\n";
        return 1;
    }

    GLFWwindow *window = glfwCreateWindow (640, 640, "My Window", NULL, NULL);
    if (!window) {
        std::cout << "Could not create window.\n";
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent (window);	
    glfwSetKeyCallback(window, key_callback);	// setup input callback 


	// Separate point lists for each screen element

    int curveOrder;
    float increment;

    std::vector<Point3D*> conrolPts;

    Point3D points[] = new Point3D[10];


    // get indexFocus  evaluate the basis funcs
    if ((u+ inc) > ufocus+1)
        then focus = focus + ufocus+1;

    while (!glfwWindowShouldClose (window))
    {
        // generate basis funcs
        render(points_h, points_R, points_r, points_l);		// render the scene
        glfwSwapBuffers(window);

		glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
