#include <bits/stdc++.h>


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
/// maketest ("max_x" max in x coordinates
///            ,"max_y" max in y coordinates
///             , "top_ncolor" max number of each color
///             , "n_color" number of color)
vector<Point> maketest(double max_x,double max_y,int top_ncolor,int n_color)
*/


#include "make_delta.cpp"
/*
///find delta for griding space,
///     input==> 'points' is all point in our test,
///              'n_color' is number of color we have
double makedelta(vector<Point> points,int n_color)
*/



#define pll pair<long long ,long long>


#include "make_grid.cpp"
/*
///define grid view from space with delta and epsilon
///make_gird("points" is all point that we make with make_test
///          ,"delta" is value that we calculate with make_delta
///         ,"epsilon" is value that participate to calculate size of "square_side")

map<pll,set<int> > make_grid(vector<Point> points,double delta,double epsilon)
*/



#include <bits/stdc++.h>

#include "diameter_square.cpp"
/*
///calculate the square of the diameter of some poins,
///     input==> 'points' is a list of points of the grid

double diameter_square(vector<pll> points)
*/


using namespace std;

int main()
{
    int n_color=6;
    vector<Point> all_points=maketest(5,3,5,n_color);
    double delta=makedelta(all_points,n_color)*2;
    grid=make_grid(all_points,delta,0.3);
    double diam = diameter_square({pll(0, 2), pll(3, 1), pll(3, 5), pll(5, 5)});
    cout<<(square_side);
    return 0;
}
