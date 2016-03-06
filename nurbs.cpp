#include "nurbs.h"

void Nurbs::setWeights(float *U)
{
	weights = U;
}

double Nurbs::sumWeights(double u)
{
	double result = 0;
	int numPts = m + 1;

	for (int i = 0; i < k; i++)
	{
		result += weights[i] * bSplineBasis(i, m, k, u, knots);
	}
	return result;
}

Point2D *Nurbs::sumPointWeights(double u)
{
	Point2D p = Point2D(0, 0);

	int numPts = m + 1;

	for (int i = 0; i < numPts; i++)
	{
		p = p + ctrlPts[i] * weights[i] * bSplineBasis(i, m, k, u, knots);
	}
	double totalWeight = sumWeights(u);
	p = p * (1.0 / totalWeight);
	return new Point2D(p);
}

vector<Point2D*> *Nurbs::getCurveLines(float stepSize)
{
	float u = 0;
	int numSteps = (int)(1.0f / stepSize);

	vector<Point2D*> *result = new vector<Point2D*>;

	if (m < 2)
		return 0;
	BSpline bs;
	bs.setControlPoints(m, ctrlPts);
	bs.setKnots(knots);
	bs.setOrder(k);

	int i = 0;
	int d = 0;
	while (u <= 1)
	{
		while (u < 1 && u >= knots[d + 1] && d < m + k)
			d++;

		Point2D &p = *sumPointWeights(u);
		result->push_back(new Point2D(p.x, p.y));
		u += stepSize;
		i++;
	}

	return result;
}
