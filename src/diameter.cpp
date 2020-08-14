#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#define pll pair<long long,long long>

double diameter_square(vector<pll> points, float gridSize, int num_rows){

	// find left most and right most in each row
	vector<long long> left;
	vector<long long> right;
	for(int i=0; i<num_rows; i++){
		left.push_back(-1);
		right.push_back(-1);
	}
	
	for(int i=0; i<points.size(); i++){
		// find left in every row
		if(left[points[i].first] == -1) {
			left[points[i].first] = points[i].second;
		}
		else if(left[points[i].first] > points[i].second) {
			left[points[i].first] = points[i].second;
		}

		// find right in every row
		if(right[points[i].first] == -1) {
			right[points[i].first] = points[i].second;
		}
		else if(right[points[i].first] < points[i].second) {
			right[points[i].first] = points[i].second;
		}
	}

	// find diameter
	double diam = 0;
	double d = 0;
	for(int i=0; i<left.size(); i++) {
		if(left[i] == -1) {
			continue;
		}
		for(int j=0; j<right.size(); j++) {
			if(right[j] == -1) {
				continue;
			}
			d = (i - j) * (i - j) + (left[i] - right[j]) * (left[i] - right[j]);
			if(diam < d) {
				diam = d;
			}
		}
		for(int j=i; j<left.size(); j++) {
			if(right[j] == -1) {
				continue;
			}
			d = (i - j) * (i - j) + (left[i] - left[j]) * (left[i] - left[j]);
			if(diam < d) {
				diam = d;
			}
		}
	}

	diam = diam * gridSize * gridSize;

	return diam;
}

int main() {
	vector<pll> points = {pll(0, 2), pll(3, 1), pll(3, 5), pll(5, 5)};
	float gridSize = 10;
	int num_rows = 6; // number of rows in grid
	double diam = diameter_square(points, gridSize, num_rows);
	cout << "Diameter: " << diam << endl;
  	return 0;
}