#include "program.h"

using namespace std;

Program::Program()
{
	curve = &spline;		
}

void Program::updateCurveWeights()
{
	float *c = new float[weights.size()];

	for (int i = 0; i < weights.size(); i++)
	{
		c[i] = weights[i];
	}

	int m = weights.size() - 1;
	nurbs.setWeights(c);
}

void Program::updateCurveCtrlPoints()
{
	Point2D *c = new Point2D[ctrlPts.size()];

	for (int i = 0; i < ctrlPts.size(); i++)
	{
		c[i] = *ctrlPts[i];
	}

	int m = ctrlPts.size() - 1;
	curve->setControlPoints(m, c);
}

void Program::updateCurve()
{
	updateCurveWeights();
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
	for (int i = 0; i < splinePts.size(); i++)
	{
		if (abs((*splinePts[i]).x - mouseX) <= selectDistance &&
			abs((*splinePts[i]).y - mouseY) <= selectDistance)
		{
			state = State::ON_CURVE;
			float u = splinePts_u[i];
			int d = curve->getIndexOfFocus(u);
			curve->effSum(d, u, &geoPts, &convexPts);
			activeIdx = i;
			return true;
		}
	}
	return false;
}

void Program::mouseClick(int button, double mouseX, double mouseY)
{
	for (int i = 0; i < ctrlPts.size(); i++)
	{
		if (abs((*ctrlPts[i]).x - mouseX) <= selectDistance &&
			abs((*ctrlPts[i]).y - mouseY) <= selectDistance)
		{
			state = State::NORMAL;
			activeIdx = i;
			break;
		}
	}

	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		selectedIdx = activeIdx;
		if (activeIdx == -1)
		{
			if (!selectCurvePoint(mouseX, mouseY))		// if the curve wasn't clicked
			{
				state = State::NORMAL;
				activeIdx = ctrlPts.size();
				ctrlPts.push_back(new Point2D(mouseX, mouseY));
				weights.push_back(1);
				updateCurve();
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
		curve = &nurbs;
	else
		curve = &spline;

	updateCurve();
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
	if (w < 0)
		w = 0;

	printf("NURBS weight: %f\n", w);
	updateCurve();
}

int Program::modifyOrder(int v)
{	
	order += v;
	if (order < 2)
		order = 2;

	printf("Spline order: %d\n", order);
	updateCurve();
	return order;
}