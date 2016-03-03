#ifndef PROGRAM_H
#define PROGRAM_H

#include <GLFW/glfw3.h>
#include "point2D.h"
#include <vector>

using namespace std;

class Program
{
public:
	enum State { NORMAL, ADD, DEL, MOV };

	void render();
	void addPoint();
	void curve(float u);
	vector<Point2D> points;

private:
	int k;
	float u;
	int selected;
};

#endif
