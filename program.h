#ifndef PROGRAM_H
#define PROGRAM_H

#include <GLFW/glfw3.h>
#include "point2D.h"
#include <vector>
#include "bspline.h"
#include <iostream>
#include "nurbs.h"

using namespace std;

class Program
{
public:
	enum State { NORMAL, WEIGHT, ON_CURVE };
	bool nurbs_on = false;
	State state = State::NORMAL;
	int activeIdx = -1;
	int selectedIdx = -1;
	

	Program();
	void render();
	void addPoint();
	void deleteSelected();

	vector<Point2D*> ctrlPts;
	vector<Point2D*> splinePts;
	vector<float> splinePts_u;
	vector<Point2D*> geoPts;
	vector<Point2D*> convexPts;
	vector<float> weights;

	void mouseClick(int button, double mouseX, double mouseY);
	void mouseDrag(double mouseX, double mouseY, double newMouseX, double newMouseY);
	void mouseRelease();
	int modifyOrder(int v);
	void modifyStep(float v);
	void modifyWeight(float v);
	bool toggleNurbs();

private:
	Nurbs nurbs;
	BSpline spline;
	BSpline *curve;
	int order = 2;
	float step_u = 0.01f;
	float selectDistance = 0.05;

	void updateCurveCtrlPoints();
	void updateCurveWeights();
	void updateCurve();
	void getSplineLines();
	bool selectCurvePoint(double mouseX, double mouseY);
};

#endif
