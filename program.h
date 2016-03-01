#ifndef PROGRAM_H
#define PROGRAM_H

#include <GLFW/glfw3.h>
#include "Point2D.h"
#include <vector>

using namespace std;

class Program
{
public:
	enum State { NORMAL, ADD, DEL, MOV };

	void render();
	void addPoint();
	void curve(float u);

private:
	int k;
	float u;
	int selected;
	vector<Point2D> points;
};

#endif