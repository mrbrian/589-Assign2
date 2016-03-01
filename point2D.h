#include<GLFW/glfw3.h>

class Point2D	// your basic Point3D class
{
public:
    bool equals(Point2D *p)
    {
        if (this->x == p->x && this->y == p->y)
            return true;
        return false;
    }

    Point2D(float x, float y)
    {
        this->x = x;
        this->y = y;
    }

    Point2D(const Point2D &p)	// copy constructor
    {
        this->x = p.x;
        this->y = p.y;
    }

    Point2D& operator =(const Point2D& other)
    {
      x = other.x;
      y = other.y;
      return *this;
    }

private:
    float x;	// point coordinates
    float y;
};

class BSpline
{
public:
    Point2D *ctrlPts;
    float *knots;
    int k;
    int m;

    Point2D getPoint(float u)
    {
        for (int i = 0; i < k; i++)
        {

        }
        return Point2D(-1, -1);
    }

    void setControlPoints(Point2D *p)
    {
        ctrlPts = p;
    }

    void setOrder(int in_k)
    {
        k = in_k;
    }

    void setKnots(float *U)
    {
        knots = U;
    }

    int getIndex(float u)
    {
        for (int i = 0; i < m + k; i++)
        {
            if (u >= U[i] && u < U[i + 1])
                return i;
        }
        return -1;
    }

    Point2D sum(float u)
    {
       //Input k, m, E[], u[], u
           //k: order of B-spline
           //m: number of control points
           //E[ ]: coefficient vector( can be x[ ], y[ ], z[ ] of the control points
           //u[ ]: knot sequence
           //u: fixed parameter value
       int d = delta(u);
       for (int i = 0 o to k - 1)
       {
           c[i] = E[δ - i]; //nonzero coefficients
       }
       for (int r = k o to 2 p step –1
           i = d;
       for s = 0 o to r - 2
           omega = (u - u[i]) / (u[i + r - 1] - u[i]);
       c[s] = omega*c[s] + (1 - omega)*c[s + 1];
       i = i - 1;
       endfor;
       endfor;
       t output c[0];
   }
};
