#include <iostream>
#include "point.h"
/*
Point(double _x=0,double _y=0,int _color=0)
*/


#include "squared_distance.cpp"
/*
///square of distance between two points
double squdist(Point a,Point b)
*/


#include "make_test.cpp"
/*
/// maketest ("max_x" max in x coordinates ,"max_y" max in y coordinates , "top_ncolor" max number of each color , "n_color" number of color)
vector<Point> maketest(double max_x,double max_y,int top_ncolor,int n_color)
*/


#include "make_delta.cpp"
/*
///find delta for griding space,
///     input==> 'points' is all point in our test,
///              'n_color' is number of color we have
double makedelta(vector<Point> points,int n_color)
*/

using namespace std;

int main()
{
    int n_color=6;
    vector<Point> all_points=maketest(5,3,5,n_color);
    cout<<"delta==>"<<makedelta(all_points,n_color)*2;
    return 0;
}
