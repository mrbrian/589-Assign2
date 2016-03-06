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
	double sumWeights(int d, double u);			// sum up the total weight for a position u
	Point2D *sumPointWeights(int d, double u);		// sum up the total point influence for a position u
	void setWeights(vector<float> *U);		// setter
	void getLinePoints(vector<Point2D*> *list, vector<float> *u_list, float step_u) override;	// evaluates the points on the curve for rendering

private:
	vector<float> *weights;					// pointer to the program class weight list 
};


#endif