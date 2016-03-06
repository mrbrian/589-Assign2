#ifndef BSPLINE_H
#define BSPLINE_H

#include "point2D.h"
#include <vector>
#include <iostream>

using namespace std;

class BSpline
{
public:
	vector<Point2D*> *ctrlPts;
	float *knots;
	int k;
	int m;

	int getIndexOfFocus(float u);
	Point2D getPoint(float u);
	void setControlPoints(int in_m, vector<Point2D*> *p);
	int getOrder();
	void setOrder(int in_k);
	void setKnots(float *U);
	Point2D bruteSum(float u);
	Point2D *effSum(int d, float u, vector<Point2D*> *geoPts, vector<Point2D*> *convexPts);
	Point2D *effSum(int d, float u);
	virtual void getLinePoints(vector<Point2D*> *list, vector<float> *u_list, float step_u);
	static float *standardKnotSeq(int m, int k);
	static double bSplineBasis(int i, int m, int k, double u, float *knots);
	static Point2D bruteSum(int m, int k, float u, vector<Point2D*> *ctrlPts, float *knots);
};

#endif