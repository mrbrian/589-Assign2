#ifndef POINT2D_H
#define POINT2D_H

#include <GLFW/glfw3.h>

class Point2D	// basic Point3D class
{
public:
	float x;	// point coordinates
	float y;

	// comparator
    bool equals(Point2D *p)		
    {
        if (this->x == p->x && this->y == p->y)
            return true;
        return false;
    }

	// default constructor
	Point2D()	
	{
	}
	
	// constructor
	Point2D(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	// copy constructor
    Point2D(const Point2D &p)	
    {
        this->x = p.x;
        this->y = p.y;
    }

	// addition
	Point2D& operator +(const Point2D& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	// scaling
	Point2D operator *(float f)
	{
		return Point2D(x * f, y * f);
	}
};

#endif