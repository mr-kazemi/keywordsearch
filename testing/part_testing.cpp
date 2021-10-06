#include <bits/stdc++.h>
using namespace std;

#define pll pair<long long,long long>
#define pdd pair<double,double>

vector<int> Mycolor; /// colors to use in making color spanning subset


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
/// making points with control on delta value for testing main part method
/// make_test ("max_x" max in x coordinates
///            ,"max_y" max in y coordinates
///             , "top_ncolor" max number of each color
///             , "n_color" number of color)
vector<Point> make_test(double max_x,double max_y,int top_ncolor,int n_color)
*/



#include "make_delta.cpp"
/*
///find delta for griding space,
///     input==> 'points' is all point in our test,
///              'n_color' is number of color we have
double make_delta(vector<Point> points,int n_color)
*/




#include "make_grid.cpp"
/*
///define grid view from space with delta and epsilon
///make_gird("points" is all point that we make with make_test
///          ,"delta" is value that we calculate with make_delta
///         ,"epsilon" is value that participate to calculate size of "square_side")

map<pll,set<int> > make_grid(vector<Point> points,double delta,double epsilon)
*/



#include "points_in_convex_hull.cpp"
// used in "practical_way.cpp"
/*
///remove all points that are outside of convex hull (on the right side of convex hull's edges)
///     input==> 'points' is a list of points of the grid,
///               'convex_hull' is a list of dimentions of points (not from the grid) forming the convex hull

vector<pll> points_in_convex_hull(vector<pll> points, vector<pdd> convex_hull)
*/


#include "diameter_square.cpp"
// used in "practical_way.cpp"
/*
///calculate the square of the diameter of some poins,
///     input==> 'points' is a list of points of the grid

double diameter_square(vector<pll> points)
*/


#include "color_spanning.cpp"
// used in "practical_way.cpp"
/*
///check if a core_set is color spanning,
///     input==> 'points' is a list of points of the grid

bool color_spanning(vector<pll> points)
*/


int main()
{
    int n_color=6;
    vector<Point> all_points=make_test(5,3,5,n_color);
    double delta=make_delta(all_points,n_color)*2;
    grid=make_grid(all_points,delta,0.3);
    cout<<(square_side);

    vector<pll> core_set = points_in_convex_hull({pll(1, 2), pll(3, 1), pll(3, 5), pll(5, 5)}, {pdd(3.0*square_side , 0.0*square_side), pdd(5.0*square_side, 4.0*square_side), pdd(0.0*square_side, 3.0*square_side)}); // used in "practical_way.cpp" so the input is just a test
    cout << "\ncore set: ";
    for(int i=0; i<core_set.size(); i++){
    	cout << "\t" << core_set[i].first << ", " << core_set[i].second;
    }

    double diam = diameter_square({pll(0, 2), pll(3, 1), pll(3, 5), pll(5, 5)}); // used in "practical_way.cpp" so the input is just a test
    cout << "\nsquare of diameter: " << diam << endl;

    int My_color_size=8;
    Mycolor.clear();
    for(int i=0;i<My_color_size;i++){
        Mycolor.push_back(i+1);
    }
    bool check = color_spanning({pll(0, 2), pll(3, 1), pll(3, 5), pll(5, 5)}); // used in "practical_way.cpp" so the input is just a test
    cout << "color spanning: " << check << endl;

    return 0;
}
