#include "nurbs.h"

void Nurbs::setWeights(vector<float> *U)
{
	weights = U;
}

double Nurbs::sumWeights(double u)
{
	double result = 0;
	int numPts = m + 1;

	for (int i = 0; i < numPts; i++)
	{
		result += (*weights)[i] * bSplineBasis(i, m, k, u, knots);
	}
	return result;
}

Point2D *Nurbs::sumPointWeights(double u)
{
	Point2D p = Point2D(0, 0);

	int numPts = m + 1;

	for (int i = 0; i < numPts; i++)
	{
		p = p + *(*ctrlPts)[i] * (*weights)[i] * bSplineBasis(i, m, k, u, knots);
	}
	double totalWeight = sumWeights(u);
	p = p * (1.0 / totalWeight);
	return new Point2D(p);
}

void Nurbs::getLinePoints(vector<Point2D*> *list, vector<float> *u_list, float step_u)
{
	if (u_list)
		u_list->clear();
	if (list)
		list->clear();
	float u = 0;
	float prev_u = 0;
	int numSteps = (int)(1.0f / step_u);

	vector<Point2D*> *result = new vector<Point2D*>;

	if (m < 2)
		return;

	int i = 0;
	int d = 0;
	bool end = false;
	while (u <= 1)
	{
		while (u < 1 && u >= knots[d + 1] && d < m + k)
			d++;

		Point2D &p = *sumPointWeights(u);
		if (u_list)
			u_list->push_back(u);
		if (list)
			list->push_back(new Point2D(p.x, p.y));

		u += step_u;
		if (prev_u < 1 && u > 1 && !end)
		{
			end = true;
			u = 1;
		}
		prev_u = u;
		i++;
	}
}
