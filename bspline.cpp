#include "bspline.h"

Point2D BSpline::bruteSum(int m, int k, float u, Point2D *ctrlPts, float *knots)
{
	Point2D s = Point2D(0, 0);
	for (int i = 0; i <= m; i++)
	{
		double contrib = bSpline(i, k, u, knots);
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
	for (int i = m+1; i <= m + k; i++)
	{
		knots[i] = 1;
	}
	return knots;
}

double BSpline::bSpline(int i, int k, double u, float *knots)
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
	double a = denomA == 0 ? 0 : (u - knots[i]) / denomA * bSpline(i, k - 1, u, knots);
	double b = denomB == 0 ? 0 : (knots[i + k] - u) / denomB * bSpline(i + 1, k - 1, u, knots);
	return (a + b);
}