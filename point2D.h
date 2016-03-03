#ifndef POINT2D_H
#define POINT2D_H

#include <GLFW/glfw3.h>

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

	Point2D operator *(float f)
	{
		return Point2D(x * f, y * f);
	}

    float x;	// point coordinates
    float y;
};

#endif