#include "program.h"

using namespace std;

void Program::updateBSpline()
{
	Point2D *c = new Point2D[ctrlPts.size()];
	int m = ctrlPts.size() - 1;

	for (int i = 0; i < ctrlPts.size(); i++)
	{
		c[i] = *ctrlPts[i];
	}

	spline.setControlPoints(m, c);
	float *knots = BSpline::standardKnotSeq(m, order);
	spline.setKnots(knots);
	spline.setOrder(order);
	getSplineLines();
}

void Program::getSplineLines()
{
	spline.getLinePoints(&splinePts, &splinePts_u, step_u);
}

void Program::mouseRelease()
{
	state = State::NORMAL;
	selected = -1;
}

void Program::mouseDrag(double mouseX, double mouseY)
{
	if (state == State::ON_CURVE)
	{
		scanCurvePoints(mouseX, mouseY);
		return;
	}

	if (selected < 0)// || selected > m)
		return;
	Point2D &p = *ctrlPts[selected];

	p.x = mouseX;
	p.y = mouseY;
	updateBSpline();
}

void Program::scanCurvePoints(double mouseX, double mouseY)
{
	for (int i = 0; i < splinePts.size(); i++){
		if (abs((*splinePts[i]).x - mouseX) <= selectDistance &&
			abs((*splinePts[i]).y - mouseY) <= selectDistance){
			state = State::ON_CURVE;
			float u = splinePts_u[i];
			int d = spline.getIndexOfFocus(u);
			spline.effSum(d, u, &geoPts, &convexPts);
			selected = i;
			break;
		}
	}
}

void Program::mouseClick(int button, double mouseX, double mouseY)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		for (int i = 0; i < ctrlPts.size(); i++){
			if (abs((*ctrlPts[i]).x - mouseX) <= selectDistance &&
				abs((*ctrlPts[i]).y - mouseY) <= selectDistance){
				state = State::NORMAL;
				selected = i;
				return;
			}
		}

		scanCurvePoints(mouseX, mouseY);

		if (selected == -1){
			state = State::NORMAL;
			selected = ctrlPts.size();
			ctrlPts.push_back(new Point2D(mouseX, mouseY));
			updateBSpline();
		}
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && selected > -1){
		state = State::NORMAL;
		ctrlPts.erase(ctrlPts.begin() + selected);
		updateBSpline();
		selected = -1;
	}
}

float Program::modifyStep(float v)
{
	step_u += v;

	if (step_u < 0.01f)
		step_u = 0.01f;

	updateBSpline();
	return step_u;
}

int Program::modifyOrder(int v)
{	
	order += v;
	if (order <= 0)
		order = 1;

	updateBSpline();
	return order;
}