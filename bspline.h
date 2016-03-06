#ifndef BSPLINE_H
#define BSPLINE_H

#include "point2D.h"
#include <vector>
#include <iostream>

using namespace std;

class BSpline
{
public:
	void setOrder(int in_k);						// setter
	void setKnots(float *U);						// setter
	void setControlPoints(vector<Point2D*> *p);		// setter
	virtual void getLinePoints(vector<Point2D*> *list, vector<float> *u_list, float step_u);	// evaluate a list of points on the curve

	int getIndexOfFocus(float u);					// find the index of focus
	Point2D *effSum(int d, float u, vector<Point2D*> *geoPts, vector<Point2D*> *convexPts);		// efficient algorithm to evaluate a point on the curve

	static float *standardKnotSeq(int m, int k);								// generates the standard knot sequence for given m and k
	static double bSplineBasis(int i, int m, int k, double u, float *knots);	// evaluate a specified bspline basis func 

protected:
	int k;						// curve order
	float *knots;				// knot array
	vector<Point2D*> *ctrlPts;	// a pointer to the control point list in program
};

#endif