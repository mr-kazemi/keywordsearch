#include <iostream>
#include <bits/stdc++.h>
#include <cmath> 
using namespace std;

#define pll pair<long long,long long>

struct Point{
    long double x,y;
    int color;
    Point(long double _x=0,long double _y=0,int _color=0){
        x=_x;
        y=_y;
        color=_color;
    }
};

map<pll,set<int>> grid{ // output of another task! it's just a sample.
    {pll(0, 2), {1, 2}},
	{pll(3, 1), {2}},
	{pll(3, 5), {1}},
	{pll(5, 5), {1}}
};

double diameter(int dimensions){
	map<pll,set<int>>::iterator itr; 
    double diam = 0; // min possible
    for(itr = grid.begin(); itr != grid.end(); itr++) { // points
        pll point = itr->first;
        for(int row=point.first; row <= dimensions; row++) { // lower rows
        	for(int col = 0; col <= point.second; col++){
        		if(grid.count(pll(row, col)) > 0) { // find first left point in the row
        			if (point.first == row && point.second == col) { // same point
        				break;
        			}
	        		double dist = sqrt(pow((point.first - row), 2) + pow((point.second - col), 2)); // distance between two points
	        		if (diam < dist) { // update diameter
	        			diam = dist;
	        			//cout << "d: " << diam << endl;
	        			//cout << "first: " << point.first << "\t second: " << point.second << endl;
	        			//cout << "row: " << row << "\t col: " << col << endl;
	        		}
	        		break;
	        	}
        	}
        	for(int col = dimensions; col >= point.second; col--){
        		if(grid.count(pll(row, col)) > 0) { // find first right point in the row
        			if (point.first == row && point.second == col) { // same point
        				break;
        			}
	        		double dist = sqrt(pow((point.first - row), 2) + pow((point.second - col), 2)); // distance between two points
	        		if (diam < dist) { // update diameter
	        			diam = dist;
	        			//cout << "d: " << diam << endl;
	        			//cout << "first: " << point.first << "\t second: " << point.second << endl;
	        			//cout << "row: " << row << "\t col: " << col << endl;
	        		}
	        		break;
	        	}
        	}
        }
    } 

	return diam;
}

int main() {
	double epsilon = 0.1; // user's input! it's just a sample.
	int dimensions = 1 / epsilon;
	double diam = diameter(dimensions);
	cout << "Diameter: " << diam << endl;
  	return 0;
}