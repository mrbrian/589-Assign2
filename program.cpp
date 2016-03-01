#include "program.h"

using namespace std;

void Program::curve(float u)
{
}

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

double bSpline(int i, int n, float *knots, double u)
{
	if (n == 1)
	{
		if (u
	}
}
// knot sequence U is global
int delta(u, m, k)
{
	for i = 0 to m + k - 1
		if u >= U[i] and u < U[i + 1] return i
			end
			return -1
}

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

void test_bSplineTable()
{
}

void test_bSplineBasis()
{
	float expected = 0;
	double actual = bSpline(0, 2, 0);
}

void test_bernstein()
{
	float expected = 0;
	double actual = bernstein(0, 2, 0);

}