
using namespace std;


/*include need before run:
  define point structure==>"point.h"
  calculate distance==>"squared_distance.cpp"
  make point for testing==>"make_test.cpp"
  calculate delta==>"make_delta.cpp"

*/

double square_side ;/// square_side==>the side of square in the grid

map<pll,set<int> > grid;///output of make_grid.cpp

///define grid view from space with delta and epsilon
///make_gird("points" is all point that we make with make_test
///          ,"delta" is value that we calculate with make_delta
///         ,"epsilon" is value that participate to calculate size of "square_side")

map<pll,set<int> > make_grid(vector<Point> points,double delta,double epsilon){

    ///for saving points to show in graphic
    ofstream file;
    file.open("./data_point_with_delta.txt");
    ///

    /// saving points in grid view
    map<pll,set<int> > grid_table;


    ///# square_side==>the side of square in the grid
    square_side=(epsilon)/3;
    square_side*=delta;
    cout<<"side of squre==>"<<square_side<<endl;
    ///##



    ///# Changing every coordination of points which are given to me in integer form-
    ///    that they show the number of squares on all sides of coordination
    /// Every point can have different colors

    long long help_x,help_y;///helping value for calculating process, coordinate of points in grid view
    vector<Point> grided_points;
    for(int i=0;i<(int)points.size();i++){
        help_x=floor(points[i].x/square_side);
        help_y=floor(points[i].y/square_side);
        grided_points.push_back(Point(help_x*square_side,help_y*square_side,points[i].color));
        grid_table[pll(help_x,help_y)].insert(points[i].color);
    }

    ///##


    ///# cout points in/on the circle

    ///two point on circle
    cout<<"point on circle"<<endl;
    help_x=floor(point_c1.x/square_side);
    help_y=floor(point_c1.y/square_side);
    cout<<"("<<help_x<<","<<help_y<<")\t";

    help_x=floor(point_c2.x/square_side);
    help_y=floor(point_c2.y/square_side);
    cout<<"("<<help_x<<","<<help_y<<")"<<endl;

    ///other points inside circle
    for(int i=0;i<insid_circle.size();i++){
        help_x=floor(insid_circle[i].x/square_side);
        help_y=floor(insid_circle[i].y/square_side);
        cout<<"("<<help_x<<","<<help_y<<")"<<endl;
    }


    ///##


    ///# saving points in/on the circle
    file<<square_side<<" ";
    file<<(int(insid_circle.size())+2)<<" ";
    ///two point on circle
    help_x=floor(point_c1.x/square_side);
    help_y=floor(point_c1.y/square_side);
    file<<(help_x*square_side)<<" "<<(help_y*square_side)<<" "<<point_c1.color<<" ";

    help_x=floor(point_c2.x/square_side);
    help_y=floor(point_c2.y/square_side);
    file<<(help_x*square_side)<<" "<<(help_y*square_side)<<" "<<point_c2.color;

    ///other points inside circle
    for(int i=0;i<insid_circle.size();i++){
        help_x=floor(insid_circle[i].x/square_side);
        help_y=floor(insid_circle[i].y/square_side);
        file<<" "<<(help_x*square_side)<<" "<<(help_y*square_side)<<" "<<insid_circle[i].color;
    }
    for(int i=0;i<grided_points.size();i++){
        file<<" "<<grided_points[i].x<<" "<<grided_points[i].y<<" "<<grided_points[i].color;
    }
    file.close();

    ///##

    return grid_table;
}


