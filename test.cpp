#include "tests.h"
#include "bspline.h"
#include <stdio.h>
#include <iostream>
#include "point2D.h"
#include "program.h"

using namespace std;

void geometric_1()	// making a simple line..
{
	// i expect a single straight lines.   setup a
	float u = 0.5;
	Point2D expected[3] = { Point2D(0.5, 0.5), Point2D(-0.5, 0.5), Point2D(0, 0.5) };

	Point2D pts[3] = { Point2D(-1, 0), Point2D(0, 1), Point2D(1, 0) };
	float *knots = BSpline::standardKnotSeq(2, 3);

	BSpline bs;
	bs.setKnots(knots);
	bs.setControlPoints(2, pts);
	bs.setOrder(3);

	vector<Point2D*> actual;
	bs.effSum(2, u, &actual, 0);

	for (int i = 0; i < 3; i++)
	{
		if (!expected[i].equals(actual[i]))
			cout << "geometric_1 fail\n";
	}
	cout << "geometric_1 pass\n";
}

void geometric_2()	// making a simple line..
{
	// i expect a single straight lines.   setup a
	float u = 0.75;
	int k = 2;
	Point2D expected[3] = { Point2D(0.5, 0.5) };

	Point2D pts[3] = { Point2D(-1, 0), Point2D(0, 1), Point2D(1, 0) };
	float *knots = BSpline::standardKnotSeq(2, k);  // 0,0,1/2,1,1

	BSpline bs;
	bs.setKnots(knots);
	bs.setControlPoints(2, pts);
	bs.setOrder(k);

	vector<Point2D*> actual;
	bs.effSum(2, u, &actual, 0);

	for (int i = 0; i < 1; i++)
	{
		if (!expected[i].equals(actual[i]))
			cout << "geometric_2 fail\n";
	}
	cout << "geometric_2 pass\n";
}

void geometric_3()	// making a simple line..
{
	// i expect a single straight lines.   setup a
	float u = 0.5;
	int k = 4;
	int m = 3;
	Point2D expected[7] = { Point2D(1, 0.5), Point2D(0, 1), Point2D(0, 1), Point2D(-1, 0.5), Point2D(0.5, 0.75), Point2D(-0.5, 0.75), Point2D(0, 0.75) };

	Point2D pts[4] = { Point2D(-1, 0), Point2D(-1, 1), Point2D(1, 1), Point2D(1, 0) };
	float *knots = BSpline::standardKnotSeq(m, k);  // 0,0,0,0.5,1,1,1,1

	BSpline bs;
	bs.setKnots(knots);
	bs.setControlPoints(m, pts);
	bs.setOrder(k);

	vector<Point2D*> actual;
	int d = bs.getIndexOfFocus(u);
	bs.effSum(d, u, &actual,0);

	for (int i = 0; i < 7; i++)
	{
		if (!expected[i].equals(actual[i]))
			cout << "geometric_3 fail\n";
	}
	cout << "geometric_3 pass\n";
}

void geometric_4()	// making a simple line..
{
	// i expect a single straight lines.   setup a
	float u = 0.25;
	int k = 4;
	int m = 3;
	Point2D expected[4] = { Point2D(1, 0), Point2D(1, 1), Point2D(-1, 1), Point2D(-1, 0) };

	Point2D pts[6] = { Point2D(-1, 0), Point2D(-1, 1), Point2D(1, 1), Point2D(1, 0), Point2D(2, 1), Point2D(3, 0) };
	float *knots = BSpline::standardKnotSeq(m, k);  // 0,0,0,0.5,1,1,1,1

	BSpline bs;
	bs.setKnots(knots);
	bs.setControlPoints(m, pts);
	bs.setOrder(k);

	vector<Point2D*> actual;
	int d = bs.getIndexOfFocus(u);
	bs.effSum(d, u, 0, &actual);

	for (int i = 0; i < 4; i++)
	{
		if (!expected[i].equals(actual[i]))
			cout << "geometric_4 fail\n";
	}
	cout << "geometric_4 pass\n";
}

void program_getSplineLines_1()	// making a simple line..
{
	Point2D expected[3] = { Point2D(-1, 1), Point2D(0, 1), Point2D(1, 1) };

	Point2D pts[3] = { Point2D(-1, 1), Point2D(0, 1), Point2D(1, 1) };
	float knots[5] = { 0, 0, 0.5, 1, 1 };
	Point2D **actual = BSpline::getSplineLines(2, 2, pts, knots, 0.5);

	for (int i = 0; i < 3; i++)
	{
		if (!expected[i].equals(actual[i]))
			cout << "program_getSplineLines_1 fail\n";
	}
	cout << "program_getSplineLines_1 pass\n";
}

void eff_program_getSplineLines_2()	// use the efficient index finding 
{
	Point2D expected[3] = { Point2D(-1, 1), Point2D(0, 1), Point2D(1, 1) };

	Point2D pts[3] = { Point2D(-1, 1), Point2D(0, 1), Point2D(1, 1) };
	float knots[5] = { 0, 0, 0.5, 1, 1 };
	Point2D **actual = BSpline::getSplineLines(2, 2, pts, knots, 0.5);

	for (int i = 0; i < 3; i++)
	{
		if (!expected[i].equals(actual[i]))
			cout << "program_getSplineLines_1 fail\n";
	}
	cout << "program_getSplineLines_1 pass\n";
}

void make_standardKnotSeq_1()
{
	float expected[9] = {0,0,0,0.25,0.5,0.75,1,1,1};
	float *actual = BSpline::standardKnotSeq(5, 3);

	for (int i = 0; i < 9; i++)
	{
		if (expected[i] != actual[i])			
			cout << "make_standardKnotSeq_1 fail\n";
	}
	cout << "make_standardKnotSeq_1 pass\n";
}

void bSplinePoint_Efficient_1()
{
	Point2D expected = Point2D(0, 0.5);

	float u = 0.5f;
	int m = 2;
	int k = 3;
	Point2D pts[4] = { Point2D(-1, 1), Point2D(0, 0), Point2D(1, 1)};
	float *knots = BSpline::standardKnotSeq(m, k);  // 0,0,0,1,1,1

	//iterate
	// generate a single bspline point
	BSpline bs = BSpline();
	bs.setControlPoints(m, pts);
	bs.setKnots(knots);
	bs.setOrder(k);
	int d = 2;
	Point2D actual = *bs.effSum(d, u);

	if (expected.equals(&actual))
		cout << "bSplinePoint_Efficient_1 pass\n";
	else
		cout << "bSplinePoint_Efficient_1 fail\n";
}

void bSplinePoint_2b()
{
	Point2D expected = Point2D(1, 0);

	float u = 1;
	int m = 3;
	int k = 3;
	Point2D pts[4] = { Point2D(0, 0), Point2D(0, 1), Point2D(1, 1), Point2D(1, 0) };
	float knots[7] = { 0, 0, 0, 0.5, 1, 1, 1 };

	//iterate
	// generate a single bspline point
	BSpline bs = BSpline();
	bs.setControlPoints(m, pts);
	bs.setKnots(knots);
	bs.setOrder(k);
	Point2D actual = *bs.effSum(3, u);

	if (expected.equals(&actual))
		cout << "bSplinePoint_2b pass\n";
	else
		cout << "bSplinePoint_2b fail\n";
}

void bruteBSplinePoint_Head()
{
	Point2D expected = Point2D(0, 0);

	float u = 0;
	int m = 3;
	int k = 3;
	Point2D pts[4] = { Point2D(0, 0), Point2D(0, 1), Point2D(1, 1), Point2D(1, 0) };
	float knots[7] = { 0, 0, 0, 0.5, 1, 1, 1 };

	//iterate
	// generate a single bspline point
	BSpline bs = BSpline();
	bs.setControlPoints(m, pts);
	bs.setKnots(knots);
	bs.setOrder(k);
	Point2D actual = bs.bruteSum(u);

	if (expected.equals(&actual))
		cout << "bruteBSplinePoint_Head pass\n";
	else
		cout << "bruteBSplinePoint_Head fail\n";
}

void bruteBSplinePoint_Tail()
{
	Point2D expected = Point2D(1, 0);

	float u = 1;
	int m = 3;
	int k = 3;
	Point2D pts[4] = { Point2D(0, 0), Point2D(0, 1), Point2D(1, 1), Point2D(1, 0) };
	float knots[7] = { 0, 0, 0, 0.5, 1, 1, 1 };

	//iterate
	// generate a single bspline point
	BSpline bs = BSpline();
	bs.setControlPoints(m, pts);
	bs.setKnots(knots);
	bs.setOrder(k);
	Point2D actual = bs.bruteSum(u);

	if (expected.equals(&actual))
		cout << "bruteBSplinePoint_Tail pass\n";
	else
		cout << "bruteBSplinePoint_Tail fail\n";
}

void bSplineBasis_1()
{
    float expected = 1;
    float knots[4] = {0, 1, 2, 3};
	double actual = BSpline::bSplineBasis(1, 2, 2.1, knots);
	actual += BSpline::bSplineBasis(2, 2, 2.1, knots);

    if (expected == actual)
        cout << "bSplineBasis_1 pass\n";
    else
        cout << "bSplineBasis_1 fail\n";
}

void bSplineBasis_2()
{
	float expected = 0.5;
	float knots[3] = { 0, 1, 2 };
	double actual = BSpline::bSplineBasis(0, 2, 0.5, knots);

	if (expected == actual)
		cout << "bSplineBasis_2 pass\n";
	else
		cout << "bSplineBasis_2 fail\n";
}

void bSplineBasis_1_2_1()
{
	float expected = 1;
	float knots[6] = { 0, 0.33, 0.66, 1 };
	double actual = BSpline::bSplineBasis(0, 2, 0.75, knots);
	actual += BSpline::bSplineBasis(1, 2, 0.75, knots);
	actual += BSpline::bSplineBasis(2, 2, 0.75, knots);

	if (expected == actual)
		cout << "bSplineBasis_1_2_1 pass\n";
	else
		cout << "bSplineBasis_1_2_1 fail\n";
}

void bSplineBasis_1_1_1()
{
	float expected = 1;
	float knots[6] = { 0, 0.33, 0.66, 1 };
	double actual = BSpline::bSplineBasis(0, 1, 0.99, knots);
	actual = BSpline::bSplineBasis(1, 1, 0.999, knots);
	actual = BSpline::bSplineBasis(2, 1, 0.999, knots);

	if (expected == actual)
		cout << "bSplineBasis_1_1_1 pass\n";
	else
		cout << "bSplineBasis_1_1_1 fail\n";
}

void bSplineBasis_1_1_0()
{
	float expected = 1;
	float knots[6] = { 0, 0.33, 0.66, 1 };
	double actual = BSpline::bSplineBasis(0, 1, 0, knots);

	if (expected == actual)
		cout << "bSplineBasis_1_1_0 pass\n";
	else
		cout << "bSplineBasis_1_1_0 fail\n";
}

void bSplineBasis_3()
{
	float expected = 1;
	float knots[6] = { 0, 0, 0.33, 0.66, 1, 1 };
	double actual = BSpline::bSplineBasis(3, 2, 0.8, knots);
	actual += BSpline::bSplineBasis(2, 2, 0.8, knots);

	if (expected == actual)
		cout << "bSplineBasis_3 pass\n";
	else
		cout << "bSplineBasis_3 fail\n";
}

void eff_bSplinePoint_1()
{
	BSpline bs;
	Point2D pts[3] = { Point2D(-1, 1), Point2D(0, 1), Point2D(1, 1) };
	bs.setControlPoints(2, pts);

	float *knots = BSpline::standardKnotSeq(2,3); // 0,0,0,1,1,1
	bs.setKnots(knots);
	bs.setOrder(3);

	Point2D expected = Point2D(1, 1);
	Point2D actual = *bs.effSum(2, 0.5f);
	actual = *bs.effSum(2, 1);

	if (expected.equals(&actual))
		cout << "eff_bSplinePoint_1 pass\n";
	else
		cout << "eff_bSplinePoint_1 fail\n";
}

Tests::Tests()
{
	// efficient algorithm
	geometric_1();
	geometric_2();
	geometric_3();
	geometric_4();
	eff_bSplinePoint_1();
	bSplinePoint_Efficient_1();
	eff_program_getSplineLines_2();

	program_getSplineLines_1();
	make_standardKnotSeq_1();
	bSplineBasis_1_1_0();
	bSplineBasis_1_1_1();
	bSplineBasis_1_2_1();
	bSplineBasis_3();
	bruteBSplinePoint_Head();
	bruteBSplinePoint_Tail();
	bSplinePoint_2b();
    bSplineBasis_1();
    bSplineBasis_2();
	program_getSplineLines_1();
}
