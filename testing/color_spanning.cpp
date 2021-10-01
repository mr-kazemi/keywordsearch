
#include <bits/stdc++.h>
using namespace std;


// used in "practical_way.cpp"


///check if a core_set is color spanning,
///     input==> 'points' is a list of points of the grid
bool color_spanning(vector<pll> points){
	map<int,bool> color; // creating a list to show if Mycolor[i] is being used or not
	for(int i=0; i<Mycolor.size(); i++){
		color.insert({Mycolor[i], false});
	}
	int color_count = 0;  // number of used colors
	for(int i=0; i<points.size(); i++){
		set<int> point_color = grid[points[i]];
		for (int elem : point_color){
		    if(color.count(elem) == 1 && color[elem] == false){
		    	//cout << elem << "\t" << color[elem] << endl;
				color[elem] = true;
				color_count += 1;
			}
		}
	}

	//cout << "check" << endl;
	/*for(int i=0; i<Mycolor.size(); i++){
		cout << color[Mycolor[i]] << "\t";
	}*/
	//cout << color_count << endl;

 	// check if all colors are used
	bool check = false;
	if(color_count == Mycolor.size()){
		check = true;
	}
	return check;
}
