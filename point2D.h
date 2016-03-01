#include<GLFW/glfw3.h>

class Point2D	// your basic Point3D class
{
public:
	float x;	// point coordinates
	float y;

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
};

class BSpline
{
public:
    Point2D *ctrlPts;
    float *knots;
    int order;

    Point2D getPoint(float u)
    {
        return Point2D(-1, -1);
    }

    void setControlPoints(Point2D *p)
    {
        ctrlPts = p;
    }

    void setOrder(int k)
    {
        order = k;
    }

    void setKnots(float *U)
    {
        knots = U;
    }
};
