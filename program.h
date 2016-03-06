#ifndef PROGRAM_H
#define PROGRAM_H

#include <GLFW/glfw3.h>
#include "point2D.h"
#include "bspline.h"
#include "nurbs.h"
#include <vector>
#include <math.h>
#include <iostream>

using namespace std;

class Program
{
public:
	bool nurbs_on = false;			// is nurbs activated?  default off
	
	enum State { NORMAL, WEIGHT, ON_CURVE };	// ON_CURVE = touching curve, show geometric display,  WEIGHT = editing NURBS weights, NORMAL = otherwise
	State state = State::NORMAL;	// program state 
	int activeIdx = -1;				// the control/curve point the user is clicked on (resets to -1 after mouse release)
	int selectedIdx = -1;			// the selected control point (persistent after mouse release)
	
	Program();						// constructor
	void render();					// render function
	void renderPoints_NURBS();		// render NURBS curve
	void renderPoints_BSpline();	// render Bspline curve
	void renderGeometric();			// render the geometric display
	
	vector<Point2D*> ctrlPts;		// the main list of control points
	vector<Point2D*> splinePts;		// evaluated points on the curve (for rendering)
	vector<float> splinePts_u;		// associated u values for each rendered curve point (for geometric display)
	vector<Point2D*> geoPts;		// the geometric display lines  
	vector<Point2D*> convexPts;		// the lines between the control points with some influence
	vector<float> weights;			// NURBS control point weight list

	void clear();
	void mouseClick(int button, double mouseX, double mouseY);							// process mouse clicks
	void mouseDrag(double mouseX, double mouseY, double newMouseX, double newMouseY);	// handle points dragging or editing NURBS weights
	void mouseRelease();			// just resets the program state to NORMAL
	int modifyOrder(int v);			// modfifier: clamps 2 <= order 
	void modifyStep(float v);		// modifier: clamps 0.01 <= step <= 1 
	void modifyWeight(float v);		// modifier: clamps 0 <= weight 
	void modifyStep(float v, bool rel);		// modifier: clamps 0.01 <= step <= 1 
	bool toggleNurbs();				// switch between displaying the nurbs/bspline curve
	float getStep();				// getter

private:
	Nurbs nurbs;					// nurbs object
	BSpline spline;					// spline object
	BSpline *curve;					// points at the active curve depending on the mode (BSpline or NURBS)
	int order = 2;					// order of the curve
	float step_u = 0.01f;			// step increment of u
	float selectDistance = 0.05;	// distance threshold for point selection

	void updateCurve();				// update the render points for the curve
	bool selectCurvePoint(double mouseX, double mouseY);	// if within range, select a point on the curve.  TRUE = a point was selected
};

#endif
