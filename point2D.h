#include<GLFW/glfw3.h>

class Point2D	// your basic Point3D class
{
public:
	float x;	// point coordinates
	float y;

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
