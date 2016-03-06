#include "nurbs.h"

void Nurbs::setWeights(vector<float> *U)
{
	weights = U;
}

// calculate the total weight of curve position u
double Nurbs::sumWeights(int d, double u)
{
	double result = 0;
	int m = ctrlPts->size() - 1;

	for (int i = d; (i > d - k) && (i >= 0); i--)		// add up weights of the non-zero basis funcs
	{
		result += (*weights)[i] * bSplineBasis(i, m, k, u, knots);
	}
	return result;
}

/*
	sumPointWeights: sum all of the point weights at position u, starting with a given index of focus, d
*/
Point2D *Nurbs::sumPointWeights(int d, double u)
{
	Point2D p = Point2D(0, 0);
	int m = ctrlPts->size() - 1;

	for (int i = d; (i > d - k) && (i >= 0); i--)	// iterate through non-zero basis funcs
	{
		p = p + *(*ctrlPts)[i] * (*weights)[i] * bSplineBasis(i, m, k, u, knots);
	}
	double totalWeight = sumWeights(d, u);		// get weight sum
	p = p * (1.0 / totalWeight);				// eval final NURBS curve point
	return new Point2D(p);
}

/*
	getLinePoints: Evaluate all the points on the curve with a given step increment, step_u, and store
	the points to render into list, and keep the associated u values in u_list (for finding geometric display)
*/
void Nurbs::getLinePoints(vector<Point2D*> *list, vector<float> *u_list, float step_u)
{
	if (u_list)
		u_list->clear();	// clear the target lists
	if (list)
		list->clear();

	int m = ctrlPts->size() - 1;
	if (m + 1 < k)		// need # of control points >= k for a line
		return;

	int d = 0;			// index of focus
	float u = 0;
	float prev_u = 0;
	bool end = false;	// keeps track if we clamped u to the end of the curve (only clamp it once so the loop can end after)

	while (u <= 1)
	{
		while (u < 1 && u >= knots[d + 1] && d < m + k)		// increase the index of focus if we pass a knot  (loop for higher multiplicities)
			d++;

		Point2D &p = *sumPointWeights(d, u);	// evaluate the final curve point
		if (u_list)
			u_list->push_back(u);						// store the u of the point
		if (list)
			list->push_back(new Point2D(p.x, p.y));		// store the actual point

		u += step_u;
		if (prev_u < 1 && u > 1 && !end)	// if we overshot the end of the curve, clamp it 
		{
			end = true;		// only clamp it once
			u = 1;			// clamp u to the end of the curve
		}
		prev_u = u;
	}
}
