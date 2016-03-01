#include "tests.h"
#include "program.h"
#include <stdio.h>
#include <iostream>

void testBSplineCurve()
{
    Point2D expected = Point2D(1,1);

    float u = 0.25;
    int m = 3;
    int k = 3;
    Point2D points[4] = {Point2D(0,0), Point2D(0,1), Point2D(1,1), Point2D(1,0)};
    float knots[7] = {0, 0, 0, 0.5, 1, 1, 1};

    //iterate
    // generate a single bspline point
    BSpline bs = BSpline();
    bs.setControlPoints(points);
    bs.setKnots(knots);
    bs.setOrder(k);
    Point2D actual = bs.getPoint(u);

    if (expected.equals(&actual))
        cout << "testBSplineCurve pass\n";
    else
        cout << "testBSplineCurve fail\n";
}

void Tests::bSplineBasis_1()
{
    float expected = 0;
    float knots[4] = {0, 1, 2, 3};
    double actual = bSpline(0, 2, 0, knots);

    if (expected == actual)
        cout << "bSplineBasis_1 pass\n";
    else
        cout << "bSplineBasis_1 fail\n";
}

void Tests::bSplineBasis_2()
{
    float expected = 0.5;
    float knots[3] = {0, 1, 2};
    double actual = bSpline(0, 2, 0.5, knots);

    if (expected == actual)
        cout << "bSplineBasis_2 pass\n";
    else
        cout << "bSplineBasis_2 fail\n";
}

void Tests::indexFocus_1()
{
    float expected = 2;
    float knots[5] = {0, 1, 1, 2, 3};
    int actual = getIndex(1.2, 4, 2, knots);

    if (expected == actual)
        cout << "indexFocus_1 pass\n";
    else
        cout << "indexFocus_1 fail\n";
}

/*
void test::bSplineTable()
{
}

void test::bernstein()
{
    float expected = 0;
    double actual = bernstein(0, 2, 0);

}
*/

Tests::Tests()
{
    bSplineBasis_1();
    bSplineBasis_2();
    indexFocus_1();
}
