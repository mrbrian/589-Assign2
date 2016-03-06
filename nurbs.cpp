#include "nurbs.h"

void Nurbs::setWeights(vector<float> *U)
{
	weights = U;
}

// calculate the total weight of curve position u
double Nurbs::sumWeights(int d, double u)
{
	double result = 0;
	int numPts = m + 1;

	for (int i = d; (i > d - k) && (i >= 0); i--)		// add up weights of the non-zero basis funcs
	{
		result += (*weights)[i] * bSplineBasis(i, m, k, u, knots);
	}
	return result;
}

Point2D *Nurbs::sumPointWeights(int d, double u)
{
	Point2D p = Point2D(0, 0);

	int numPts = m + 1;

	for (int i = d; (i > d - k) && (i >= 0); i--)
	{
		p = p + *(*ctrlPts)[i] * (*weights)[i] * bSplineBasis(i, m, k, u, knots);
	}
	double totalWeight = sumWeights(d, u);
	p = p * (1.0 / totalWeight);
	return new Point2D(p);
}

/*
	getLinePoints: Evaluate all the points on the curve with a given step increment, step_u, and store
	the points to render into list, and keep the associated u values in u_list (for finding geometric display)
*/
void Nurbs::getLinePoints(vector<Point2D*> *list, vector<float> *u_list, float step_u)
{
	if (u_list)
		u_list->clear();		// clear the target lists
	if (list)
		list->clear();


	if (m < 2)
		return;

	int d = 0;			// index of focus
	float u = 0;
	float prev_u = 0;
	bool end = false;	// keeps track if we clamped u to the end of the curve (only clamp it once so the loop can end after)

	while (u <= 1)
	{
		while (u < 1 && u >= knots[d + 1] && d < m + k)	// deal with higher multiplicities
			d++;

		Point2D &p = *sumPointWeights(d, u);
		if (u_list)
			u_list->push_back(u);
		if (list)
			list->push_back(new Point2D(p.x, p.y));

		u += step_u;
		if (prev_u < 1 && u > 1 && !end)	// clamp it if we havent clamped it already
		{
			end = true;
			u = 1;
		}
		prev_u = u;
	}
}
