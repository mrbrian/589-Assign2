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
	spline.setOrder(k);
	float *knots = BSpline::standardKnotSeq(m, k);
	spline.setKnots(knots);
}

void Program::getSplineLines()
{
	float u = 0;
	float STEP = 0.01f;

	splinePoints.clear();

	if (points.size() <= 3)
		return;

	while (u < 1)
	{
		splinePoints.push_back(spline.bruteSum(u));
		u += STEP;
	}
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
		points.push_back(Point2D(mouseX, mouseY));
		updateBSpline();
		getSplineLines();
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && selected > -1){
		points.erase(points.begin() + selected);
		selected = -1;
	}
}

void Program::curve(float u)
{

}

/* sums of B-Spline algo

void what(int k, int m, E[], u[], u)
{
	//Input k, m, E[], u[], u
		//k: order of B-spline
		//m: number of control points
		//E[ ]: coefficient vector( can be x[ ], y[ ], z[ ] of the control points
		//u[ ]: knot sequence
		//u: fixed parameter value
	int δ = delta(u);
	for (i = 0 o to k - 1)
	{
		c[i] = E[δ - i]; //nonzero coefficients
	}
	for (r = k o to 2 p step –1
		i = δ;
	for s = 0 o to r - 2
		omega = (u - u[i]) / (u[i + r - 1] - u[i]);
	c[s] = omega*c[s] + (1 - omega)*c[s + 1];
	i = i - 1;
	endfor;
	endfor;
	t output c[0]; 
}
*/

/*
 wheres this from  whats it do
void E_delta_1(k, m, u)
{
	d = delta(u, m, k)
		for i = 0 to k - 1
			c[i] = E[d - i]
			end
			for r = k to 2 step - 1
				i = d
				for s = 0 to r - 2
					omega = (u - U[i]) / U[i + r - 1] - U[i])
					c[s] = omega * c[s] + (1 - omega) * c[s + 1]
					i = i - 1
					end
					end
					Output c[0]
}
*/