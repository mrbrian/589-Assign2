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

	Point2D()
	{
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

	Point2D& operator +(const Point2D& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	Point2D& operator *(float f)
	{
		x *= f;
		y *= f;
		return *this;
	}

	float getX()
	{
		return x;
	}

	float getY()
	{
		return y;
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
		float x = 0;
		float y = 0;
		for (int i = 0; i < k; i++)
		{
			Point2D p = ctrlPts[i];
			x += p.getX();
			y += p.getY();
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
			return i;
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
		
		int d = getIndex(u);
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
};
