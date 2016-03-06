#include "program.h"

using namespace std;

Program::Program()
{
	curve = &spline;	// default mode is bspline, so point at the BSpline
	nurbs.setWeights(&weights);		// link the NURBS curve weights to the program weight list
}

void Program::updateCurveCtrlPoints()
{
	int m = ctrlPts.size() - 1;
	curve->setControlPoints(m, &ctrlPts);
}

void Program::updateCurve()
{
	updateCurveCtrlPoints();
	int m = ctrlPts.size() - 1;
	float *knots = BSpline::standardKnotSeq(m, order);
	curve->setKnots(knots);
	curve->setOrder(order);
	curve->getLinePoints(&splinePts, &splinePts_u, step_u);
}

void Program::mouseRelease()
{
	state = State::NORMAL;
	activeIdx = -1;
}

void Program::mouseDrag(double mouseX, double mouseY, double newMouseX, double newMouseY)
{
	double dx = newMouseX - mouseX;
	
	if (state == State::WEIGHT && selectedIdx != -1)
	{
		modifyWeight(dx);
		return;
	}
	if (state == State::ON_CURVE)
	{
		selectCurvePoint(mouseX, mouseY);
		return;
	}

	if (activeIdx < 0)
		return;
	Point2D &p = *ctrlPts[activeIdx];

	p.x = mouseX;
	p.y = mouseY;
	updateCurve();
}

bool Program::selectCurvePoint(double mouseX, double mouseY)
{
	for (int i = 0; i < splinePts.size(); i++)	// for all points on the curve in our rendered list
	{
		if (abs((*splinePts[i]).x - mouseX) <= selectDistance &&	// if within range..
			abs((*splinePts[i]).y - mouseY) <= selectDistance)
		{
			state = State::ON_CURVE;					// switch to curve touching state 
			float u = splinePts_u[i];					// get the associated u of that curve point
			int d = curve->getIndexOfFocus(u);			// get the index of focus..
			curve->effSum(d, u, &geoPts, &convexPts);	// update the geometric lines & convex hull lines
			activeIdx = i;								// mousedown over control point i
			return true;								// return true: we have selected a point on the curve
		}
	}
	return false;		// didn't click on the curve
}

void Program::mouseClick(int button, double mouseX, double mouseY)
{
	for (int i = 0; i < ctrlPts.size(); i++)	// scan all control points
	{
		if (abs((*ctrlPts[i]).x - mouseX) <= selectDistance &&		// if distance within the threshold
			abs((*ctrlPts[i]).y - mouseY) <= selectDistance)
		{
			state = State::NORMAL;		// reset to normal state
			activeIdx = i;				
			break;
		}
	}

	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		selectedIdx = activeIdx;		// update the selected point index here (dont include the below curve points in the selected idx)
		if (activeIdx == -1)
		{
			if (!selectCurvePoint(mouseX, mouseY))		// if the curve wasn't clicked..
			{
				state = State::NORMAL;
				activeIdx = ctrlPts.size();							// currently mousedown over the newest control point
				ctrlPts.push_back(new Point2D(mouseX, mouseY));		// add a new control point
				weights.push_back(1);								// with an associated weight of 1
				updateCurve();										// update curve display
			}
		}
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if (activeIdx != -1)
		{
			state = State::NORMAL;
			ctrlPts.erase(ctrlPts.begin() + activeIdx);
			weights.erase(weights.begin() + activeIdx);
			activeIdx = -1;
			selectedIdx = activeIdx;
			updateCurve();
		}
		else
		{
			state = State::WEIGHT;
		}
	}
}

void Program::modifyStep(float v)
{
	step_u += v;

	printf("U Step Increment: %f\n", v);

	if (step_u < 0.01f)
		step_u = 0.01f;

	if (step_u > 1)
		step_u = 1;

	updateCurve();
}

bool Program::toggleNurbs()
{
	nurbs_on = !nurbs_on;
	
	if (nurbs_on)
		curve = &nurbs;		// point at the nurbs curve
	else
		curve = &spline;	// point at the B-spline
				
	updateCurve();			// update the render lists
	return nurbs_on;
}

void Program::modifyWeight(float v)
{
	if (!nurbs_on)
	{
		printf("NURBS is not active.  (Press N to toggle)\n");
		return;
	}
	if (selectedIdx == -1)
	{
		printf("No vertex selected.\n");
		return;
	}
	int idx = selectedIdx;
	float &w = weights[idx];
	w += v;
	if (w < 0)		// clamp 0 <= weight 
		w = 0;

	printf("NURBS weight: %f\n", w);
	updateCurve();
}

int Program::modifyOrder(int v)
{	
	order += v;
	if (order < 2)		// minimum curve order of 2
		order = 2;

	printf("Spline order: %d\n", order);
	updateCurve();
	return order;
}

void Program::renderPoints_NURBS()
{
	for (int i = 0; i < ctrlPts.size(); i++)
	{
		float psize = fmax(2, weights[i] * 2);
		if (selectedIdx == i)
			psize += 1;

		glPointSize(psize);
		glBegin(GL_POINTS);

		if (selectedIdx == i)
			glColor3f(1, 1, 1);
		else
			glColor3f(0.0f, 1.0f, 0.0f);

		glVertex2f((*ctrlPts[i]).x, (*ctrlPts[i]).y);
		glEnd();
	}
}

void Program::renderPoints_BSpline()
{
	glPointSize(5.0);
	glBegin(GL_POINTS);

	for (int i = 0; i < ctrlPts.size(); i++)
	{
		if (selectedIdx == i)
			glColor3f(1, 1, 1);
		else
			glColor3f(1, 0, 1);

		glVertex2f((*ctrlPts[i]).x, (*ctrlPts[i]).y);
	}
	glEnd();
}

void Program::renderGeometric()
{
	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 0.0f);

	for (int i = 0; i < geoPts.size() - 1; i++)
	{
		glVertex2f((*geoPts[i]).x, (*geoPts[i]).y);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3f(1.0f, 0.0f, 0.0f);
	for (int i = 0; i < convexPts.size(); i++)
	{
		glVertex2f((*convexPts[i]).x, (*convexPts[i]).y);
	}
	glEnd();

	int idx = geoPts.size() - 1;
	glBegin(GL_POINTS);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f((*geoPts[idx]).x, (*geoPts[idx]).y);
	glEnd();
}

void Program::render()
{
	// Render the control points
	if (nurbs_on)
		renderPoints_NURBS();
	else
		renderPoints_BSpline();

	// Render the curve
	glBegin(GL_LINE_STRIP);
	glColor3f(1.0f, 0.0f, 1.0f);

	for (int i = 0; i < splinePts.size(); i++)
	{
		glVertex2f((*splinePts[i]).x, (*splinePts[i]).y);
	}
	glEnd();

	// Geometric display  (bspline only)
	if (!nurbs_on && state == Program::State::ON_CURVE)
		renderGeometric();
}
