#ifndef BSPLINE_H
#define BSPLINE_H

#include "point2D.h"
#include <vector>
#include <iostream>

using namespace std;

class BSpline
{
public:
	vector<Point2D*> *ctrlPts;	// a pointer to the control point list in program
	float *knots;				// knot array
	int k;						// curve order
	int m;						// index of last control point

	int getOrder();
	void setOrder(int in_k);
	void setKnots(float *U);
	Point2D getPoint(float u);
	int getIndexOfFocus(float u);
	Point2D *effSum(int d, float u);
	void setControlPoints(int in_m, vector<Point2D*> *p);
	Point2D *effSum(int d, float u, vector<Point2D*> *geoPts, vector<Point2D*> *convexPts);
	virtual void getLinePoints(vector<Point2D*> *list, vector<float> *u_list, float step_u);

	static float *standardKnotSeq(int m, int k);
	static double bSplineBasis(int i, int m, int k, double u, float *knots);
};

#endif