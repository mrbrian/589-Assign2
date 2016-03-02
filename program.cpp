#include "program.h"

using namespace std;

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

double bSpline(int i, int order, double u, float *knots)
{
    if (order == 1)
    {
        if (knots[i] <= u && u < knots[i+1])
            return 1;
        else
            return 0;
	}
	double a = (1 - u) * bSpline(i, order - 1, u, knots);
	double b = u * bSpline(i + 1, order - 1, u, knots);
	return (a + b);
}
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