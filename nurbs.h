#ifndef NURBS_H
#define NURBS_H

#include "point2D.h"
#include <vector>
#include <iostream>
#include "bspline.h"

using namespace std;

class Nurbs : public BSpline
{
public:
	void setWeights(float *U);
	vector<Point2D*> *getCurveLines(float stepSize);
	Point2D *sumPointWeights(double u);
	double sumWeights(double u);
private:
	float *weights;
};


#endif