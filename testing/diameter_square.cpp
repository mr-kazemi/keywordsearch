
#include <bits/stdc++.h>
using namespace std;

#define pll pair<long long,long long>


///calculate the square of the diameter of some poins,
///     input==> 'points' is a list of points of the grid
double diameter_square(vector<pll> points){
    int points_size=points.size();
    /// find number of rows
    int min = -1; // first row number
    int max = -1; // last row number
    for(int i=0; i<points_size; i++){
        if(min == -1 || min > points[i].second) {
            min = points[i].second;
        }
        if(max == -1 || max < points[i].second) {
            max = points[i].second;
        }
    }
    int num_rows = max - min + 1;

    /// find left most and right most in each row
    vector<long long> left;
    vector<long long> right;
    for(int i=0; i<num_rows; i++){
        left.push_back(-1);
        right.push_back(-1);
    }

    for(int i=0; i<points_size; i++){
        /// find left in every row
        if(left[points[i].second - min] == -1) { // not assigned yet
            left[points[i].second - min] = points[i].first;
        }
        else if(left[points[i].second - min] > points[i].first) {
            left[points[i].second - min] = points[i].first;
        }

        /// find right in every row
        if(right[points[i].second - min] == -1) { // not assigned yet
            right[points[i].second - min] = points[i].first;
        }
        else if(right[points[i].second - min] < points[i].first) {
            right[points[i].second - min] = points[i].first;
        }
    }

    /// find diameter
    double diam = 0;
    double d = 0;
    for(int i=0; i<left.size(); i++) {
        if(left[i] == -1) { // empty row
            continue;
        }

        // distance of a left point and a right point
        for(int j=0; j<right.size(); j++) {
            if(right[j] == -1) { // empty row
                continue;
            }
            d = (i - j) * (i - j) + (left[i] - right[j]) * (left[i] - right[j]);
            if(diam < d) {
                diam = d;
            }
        }

        // distance of two left points
        for(int j=i+1; j<left.size(); j++) {
            if(left[j] == -1) { // empty row
                continue;
            }
            d = (i - j) * (i - j) + (left[i] - left[j]) * (left[i] - left[j]);
            if(diam < d) {
                diam = d;
            }
        }
    }

    // distance of two right points
    for (int i=0; i<right.size(); i++) {
        if (right[i] == -1) { // empty row
            continue;
        }
        for (int j=i+1; j<right.size(); j++) {
            if (right[j] == -1) { // empty row
                continue;
            }
            d = (i - j) * (i - j) + (right[i] - right[j]) * (right[i] - right[j]);
            if (diam < d) {
                diam = d;
            }
        }
    }

    /// diam = diam * gridSize * gridSize;
    return diam;
}
