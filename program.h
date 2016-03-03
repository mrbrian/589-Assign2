#ifndef PROGRAM_H
#define PROGRAM_H

#include <GLFW/glfw3.h>
#include "point2D.h"
#include <vector>
#include "bspline.h"

using namespace std;

class Program
{
public:
	enum State { NORMAL, ADD, DEL, MOV };

	void render();
	void addPoint();
	void curve(float u);
	vector<Point2D> points;
	vector<Point2D> splinePoints;
	void mouseClick(int button, double mouseX, double mouseY);

private:
	BSpline spline;
	int selectDistance = 0.05;
	int k = 3;
	int selected = -1;

	void updateBSpline();
	void getSplineLines();
};

#endif
