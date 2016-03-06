#ifndef PROGRAM_H
#define PROGRAM_H

#include <GLFW/glfw3.h>
#include "point2D.h"
#include <vector>
#include "bspline.h"
#include <iostream>

using namespace std;

class Program
{
public:
	enum State { NORMAL, ON_CURVE };
	State state = State::NORMAL;

	void render();
	void addPoint();
	void deleteSelected();

	vector<Point2D*> ctrlPts;
	vector<Point2D*> splinePts;
	vector<float> splinePts_u;
	vector<Point2D*> geoPts;
	vector<Point2D*> convexPts;

	void mouseClick(int button, double mouseX, double mouseY);
	void mouseDrag(double mouseX, double mouseY);
	void mouseRelease();
	int modifyOrder(int v);
	float modifyStep(float v);

private:
	BSpline spline;
	int order = 2;
	int selected = -1;
	float step_u = 0.01f;
	float selectDistance = 0.05;

	void updateBSpline();
	void getSplineLines();
	void scanCurvePoints(double mouseX, double mouseY);
};

#endif
