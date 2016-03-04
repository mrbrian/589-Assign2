#include "program.h"

using namespace std;

void Program::updateBSpline()
{
	Point2D *c = new Point2D[points.size()];
	int m = points.size() - 1;

	for (int i = 0; i < points.size(); i++)
	{
		c[i] = points[i];
	}

	spline.setControlPoints(m, c);
	float *knots = BSpline::standardKnotSeq(m, order);
	spline.setKnots(knots);
	spline.setOrder(order);
	getSplineLines();
}

void Program::getSplineLines()
{
	spline.getLinePoints(&splinePoints, step_u);
}

void Program::mouseRelease()
{
	selected = -1;
}

void Program::mouseDrag(double mouseX, double mouseY)
{
	if (selected < 0)// || selected > m)
		return;
	Point2D &p = points[selected];

	cout << p.x << "\n";
	p.x = mouseX;
	p.y = mouseY;
	updateBSpline();
}

void Program::mouseClick(int button, double mouseX, double mouseY)
{
	for (int i = 0; i < points.size(); i++){
		if (abs(points[i].x - mouseX) <= selectDistance &&
			abs(points[i].y - mouseY) <= selectDistance){
			selected = i;
		}
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && selected == -1){
		selected = points.size();
		points.push_back(Point2D(mouseX, mouseY));
		updateBSpline();
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && selected > -1){
		points.erase(points.begin() + selected);
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