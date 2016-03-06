#include "bspline.h"

Point2D **BSpline::getSplineLines(int m, int k, Point2D *ctrlPts, float *knots, float stepSize)
{
	float u = 0;
	int numSteps = (int)(1.0f / stepSize);

	Point2D **result = new Point2D*[numSteps];

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

		//Point2D p = BSpline::bruteSum(m, k, u, ctrlPts, knots);
		Point2D &p = *bs.effSum(d, u);
		result[i] = new Point2D(p.x, p.y);
		u += stepSize;
		i++;
	}

	return result;
}

Point2D BSpline::bruteSum(int m, int k, float u, Point2D *ctrlPts, float *knots)
{
	Point2D s = Point2D(0, 0);
	for (int i = 0; i <= m; i++)
	{
		double contrib = bSplineBasis(i, m, k, u, knots);
		s = s + ctrlPts[i] * contrib;
	}
	return s;
}

float *BSpline::standardKnotSeq(int m, int k)
{
	float *knots = new float[m + k + 1];
	for (int i = 0; i < k; i++)
		knots[i] = 0;

	float step = (float)1 / ((m + 1) - (k - 1));

	float v = step;
	for (int i = k; i < m + 1; i++)
	{
		knots[i] = v;
		v += step;
	}
	for (int i = m + 1; i <= m + k; i++)
	{
		knots[i] = 1;
	}
	return knots;
}

double BSpline::bSplineBasis(int i, int m, int k, double u, float *knots)
{
	if (u >= knots[m + 1] && i >= m)
		return 1;
	return bSplineBasis(i, k, u, knots);
}

double BSpline::bSplineBasis(int i, int k, double u, float *knots)
{
	if (k <= 0)
		return 0;
	if (k == 1)
	{
		if (knots[i] <= u && u < knots[i + 1])
			return 1;
		else
			return 0;
	}
	double denomA = knots[i + k - 1] - knots[i];
	double denomB = knots[i + k] - knots[i + 1];
	double a = denomA == 0 ? 0 : (u - knots[i]) / denomA * bSplineBasis(i, k - 1, u, knots);
	double b = denomB == 0 ? 0 : (knots[i + k] - u) / denomB * bSplineBasis(i + 1, k - 1, u, knots);
	return (a + b);
}