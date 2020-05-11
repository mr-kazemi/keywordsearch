#include <iostream>
#include <bits/stdc++.h>
#include <cmath> 
using namespace std;

#define pll pair<long long,long long>

double diameter(vector<pll> points, float gridSize, int number){

	//find left most and right most in each row
	vector<long long> left;
	vector<long long> right;
	for(int i=0; i<number; i++){
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
	for(int i=0; i<left.size(); i++) {
		if(left[i] == -1) {
			continue;
		}
		for(int j=0; j<right.size(); j++) {
			if(right[j] == -1) {
				continue;
			}
			double d = pow(i - j, 2) + pow(left[i] - right[j], 2);
			if(diam < d) {
				diam = d;
			}
		}
	}
	diam = sqrt(diam) * gridSize;

	return diam;
}

int main() {
	vector<pll> points = {pll(0, 2), pll(3, 1), pll(3, 5), pll(5, 5)};
	float gridSize = 10;
	int number = 6; // number of rows in grid
	double diam = diameter(points, gridSize, number);
	cout << "Diameter: " << diam << endl;
  	return 0;
}