#ifndef NURBS_H
#define NURBS_H

#include "bspline.h"
#include "point2D.h"
#include <vector>
#include <iostream>

using namespace std;

class Nurbs : public BSpline
{
public:
	vector<float> *weights;

	void setWeights(vector<float> *U);
	void getLinePoints(vector<Point2D*> *list, vector<float> *u_list, float step_u) override;
	Point2D *sumPointWeights(double u);
	double sumWeights(double u);
};


#endif