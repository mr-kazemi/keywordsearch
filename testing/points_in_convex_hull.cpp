
#include <bits/stdc++.h>
using namespace std;


// used in "practical_way.cpp"


///remove all points that are outside of convex hull (on the right side of convex hull's edges)
///     input==> 'points' is a list of points of the grid,
///               'convex_hull' is a list of dimentions of points (not from the grid) forming the convex hull
vector<pll> points_in_convex_hull(vector<pll> points, vector<pdd> convex_hull){
	double Ax, Ay, Bx, By, X, Y;
	int i = 0;
	while(i<points.size()){
		bool remove = false;
		for(int j=0; j<convex_hull.size()-1 && remove == false; j++) {
			// (Bx - Ax) * (Y - Ay) - (By - Ay) * (X - Ax)
			// It is 0 on the line, and >0 on left side, <0 on right side.
			Ax = convex_hull[j].first;
			Ay = convex_hull[j].second;
			Bx = convex_hull[j+1].first;
			By = convex_hull[j+1].second;
			X = points[i].first*square_side;
			Y = points[i].second*square_side;
			if(((Bx - Ax) * (Y - Ay) - (By - Ay) * (X - Ax)) < 0){ // points[i] is on the right side of the edge (Ax, Ay)(Bx, By), so it's outside of the convex hull
				points.erase(points.begin() + i);
				remove = true;
				break;
			}
		}
		if(remove == false){ // the point is not removed
			// (Bx - Ax) * (Y - Ay) - (By - Ay) * (X - Ax)
			// for the last edge
			// (Bx - Ax) * (Y - Ay) - (By - Ay) * (X - Ax)
			// It is 0 on the line, and >0 on left side, <0 on right side.
			Ax = convex_hull[convex_hull.size()-1].first;
			Ay = convex_hull[convex_hull.size()-1].second;
			Bx = convex_hull[0].first;
			By = convex_hull[0].second;
			X = points[i].first*square_side;
			Y = points[i].second*square_side;
			if(((Bx - Ax) * (Y - Ay) - (By - Ay) * (X - Ax)) < 0){
				points.erase(points.begin() + i);
				remove = true;
			}
		}
		if(remove == false){ // points[i] is not removed. if it's removed, the points[i+1] has been relocated to points[i]
			i += 1;
		}
	}
	return points;
}
