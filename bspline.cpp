#include "bspline.h"

int BSpline::getIndexOfFocus(float u)
{
	int i = 0;
	for (i = 0; i < m + k; i++)
	{
		if ((u == 1 && knots[i + 1] >= 1) || (u >= knots[i] && u < knots[i + 1]))
			return i;
	}
	return -1;
}

Point2D BSpline::getPoint(float u)
{
	float x = 0;
	float y = 0;
	for (int i = 0; i < k; i++)
	{
		Point2D p = *(*ctrlPts)[i];
		x += p.x;
		y += p.y;
	}
	return Point2D(-1, -1);
}

void BSpline::setControlPoints(int in_m, vector<Point2D*> *p)
{
	m = in_m;
	ctrlPts = p;
}

int BSpline::getOrder()
{
	return k;
}

void BSpline::setOrder(int in_k)
{
	k = in_k;
	if (k < 1)
		k = 1;
}

void BSpline::setKnots(float *U)
{
	knots = U;
}

/* 
effsum: Efficient algorithm for BSplines
Given a index of focus, evaluate the point at u, and add the geometric interpretation points, 
and influencing control points into the given geoPts, convexPts lists	
*/
Point2D *BSpline::effSum(int d, float u, vector<Point2D*> *geoPts, vector<Point2D*> *convexPts)
{
	// clear the lists
	if (convexPts)
		convexPts->clear();
	if (geoPts)
		geoPts->clear();

	Point2D *c = new Point2D[k];	

	for (int i = 0; i <= k - 1; i++)
	{
		c[i] = *(*ctrlPts)[d - i];		//nonzero coefficients
		if (convexPts)
			convexPts->push_back((*ctrlPts)[d - i]);		// add as a contributing control point
	}
	int step = 0;
	for (int r = k; r >= 2; r--)
	{
		int i = d;
		for (int s = 0; s <= r - 2; s++)
		{
			float omega = (u - knots[i]) / (knots[i + r - 1] - knots[i]);
			c[s] = c[s] * omega + c[s + 1] * (1 - omega);
			//cout << "x:" << c[s].x << " y:" << c[s].y << "\n";
			i = i - 1;
			if (geoPts)
			{
				geoPts->push_back(new Point2D(c[s]));
				if (s > 0 && s < r - 2)
					geoPts->push_back(new Point2D(c[s]));
			}
		}
	}
	Point2D *result = new Point2D(c[0]);
	return result;
}

Point2D *BSpline::effSum(int d, float u)
{
	return effSum(d, u, 0, 0);
}

void BSpline::getLinePoints(vector<Point2D*> *list, vector<float> *u_list, float step_u)
{
	list->clear();
	u_list->clear();

	float u = 0;
	float prev_u = 0;

	if (m + 1 < k)
		return;
	int d = 0;

	bool end = false;
	while (u <= 1)
	{
		while (u < 1 && u >= knots[d + 1] && d < m + k)
			d++;

		list->push_back(effSum(d, u));
		u_list->push_back(u);
		
		u += step_u;
		
		if (prev_u < 1 && u > 1 && !end)
		{
			u = 1;
			end = true;
		}
		prev_u = u;
	}
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
	double a = denomA == 0 ? 0 : (u - knots[i]) / denomA * bSplineBasis(i, m, k - 1, u, knots);
	double b = denomB == 0 ? 0 : (knots[i + k] - u) / denomB * bSplineBasis(i + 1, m, k - 1, u, knots);
	return (a + b);
}