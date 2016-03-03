#ifndef BSPLINE_H
#define BSPLINE_H

#include "point2D.h"

using namespace std;

class BSpline
{
public:
	Point2D *ctrlPts;
	float *knots;
	int k;
	int m;

	Point2D getPoint(float u)
	{
		float x = 0;
		float y = 0;
		for (int i = 0; i < k; i++)
		{
			Point2D p = ctrlPts[i];
			x += p.x;
			y += p.y;
		}
		return Point2D(-1, -1);
	}

	void setControlPoints(int in_m, Point2D *p)
	{
		m = in_m;
		ctrlPts = p;
	}

	void setOrder(int in_k)
	{
		k = in_k;
		if (k < 1)
			k = 1;
	}

	void setKnots(float *U)
	{
		knots = U;
	}

	int getIndex(float u)
	{
		int i = 0;
		for (i = 0; i < m + k; i++)
		{
			if (u >= knots[i] && u < knots[i + 1])
				return i;
		}
		if (u >= knots[i])
			return i - 1;
		return -1;
	}

	Point2D bruteSum(float u)
	{
		return bruteSum(m, k, u, ctrlPts, knots);
	}

	Point2D sum(float u)
	{
		//Input k, m, E[], u[], u
		//k: order of B-spline
		//m: number of control points
		//E[ ]: coefficient vector( can be x[ ], y[ ], z[ ] of the control points
		//u[ ]: knot sequence
		//u: fixed parameter value

		int d = getIndex(u);
		d = 3;
		Point2D *c = new Point2D[k];
		for (int i = 0; i <= k - 1; i++)
		{
			c[i] = ctrlPts[d - i]; //nonzero coefficients
		}
		int step = 0;
		for (int r = k; r >= 2; r--)
		{
			int i = d;
			for (int s = 0; s <= r - 2; s++)
			{
				float omega = (u - knots[i]) / (knots[i + r - 1] - knots[i]);
				c[s] = c[s] * omega + c[s + 1] * (1 - omega);
				i = i - 1;
			}
		}
		return c[0];
	}

	static Point2D **getSplineLines(int m, int k, Point2D *ctrlPts, float *knots, float stepSize);
	static float *standardKnotSeq(int m, int k);
	static double bSplineBasis(int i, int m, int k, double u, float *knots);
	static double bSplineBasis(int i, int k, double u, float *knots);
	static Point2D bruteSum(int m, int k, float u, Point2D *ctrlPts, float *knots);
};

#endif