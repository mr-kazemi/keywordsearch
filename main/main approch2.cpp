#include <bits/stdc++.h>
#include "point.h"
# define M_PI           3.14159265358979323846
#define pll pair<long long ,long long>
#define pdd pair<double,double>

using namespace std;
#include <chrono>
using namespace std::chrono;
double MAX=10000000000.0; /// used in make delta
Point point_c1,point_c2; /// start points to make circle (color 1 and 2)
vector<Point> insid_circle; /// points of other colors in the circle
vector<pll> delta_dist_points;/// in vector delta_dist_points, there are points within distance of delta from point delta_dist_points[0]
vector<pll> key;///all point in grid
//vector<pll> delta_dist_points;/// in vector delta_dist_points, there are points within distance of delta from point delta_dist_points[0]
pll selected_points[1000];
int selected_points_size;
int durationdepif;
int cooooonter;
int cooooonter1;
vector<pll> selected_convex_point;
vector<pll> ss_point;
vector<pdd> circle_points;
vector<pdd> enlarge_points;
vector<pll> core_set1;
int selected;
double Min_rec=MAX;
vector<pll> vec_rec;
double square_side ;
map<pll,set<int> > grid;
vector<int> Mycolor; /// colors to use in making color spanning subset
pll p0;

///square of distance between two points
double squdist(Point a,Point b){
    double dist=(a.x-b.x)*(a.x-b.x);
    dist+=((a.y-b.y)*(a.y-b.y));
    return dist;
}

/// maketest (max x coordinates,max y coordinates , max number o each color , number of color)
vector<Point> maketest(double x,double y,int top,int n_color){
    srand(time(0));
    vector<Point> output;
    /// generating number of colors in t_color for each of colors
    vector<int> t_color;
    t_color.push_back(0);
    for(int i=1;i<=n_color;i++){
        t_color.push_back((rand()%top)+1);
    }
    /// generating coordination of points for the color 1
    Point listpoints_c1[t_color[1]];
    for(int i=0;i<t_color[1];i++){
        listpoints_c1[i].x=(double)rand()/RAND_MAX;
        listpoints_c1[i].x*=x;
        listpoints_c1[i].y=(double)rand()/RAND_MAX;
        listpoints_c1[i].y*=y;
        output.push_back(Point(listpoints_c1[i].x,listpoints_c1[i].y,1));
    }

    /// generating coordination of points for the color 2
    Point listpoints_c2[t_color[2]];
    for(int i=0;i<t_color[2];i++){
        listpoints_c2[i].x=(double)rand()/RAND_MAX;
        listpoints_c2[i].x*=x;
        listpoints_c2[i].y=(double)rand()/RAND_MAX;
        listpoints_c2[i].y*=y;
        output.push_back(Point(listpoints_c2[i].x,listpoints_c2[i].y,2));
    }

    /// finding minimum diam between the points of color 1 and color 2
    double dist=(x*x)+(y*y)+1;
    for(int i=0;i<t_color[1];i++){
        for(int j=0;j<t_color[2];j++){
            if(dist>squdist(listpoints_c1[i],listpoints_c2[j])){
                dist=squdist(listpoints_c1[i],listpoints_c2[j]);
                point_c1=listpoints_c1[i];
                point_c2=listpoints_c2[j];
            }
        }
    }

    cout<<"dist==>"<<sqrt(dist)<<endl;
    /// generating points located in the circle,
    ///   by diam between the point_c1 and the point_c2 for each of colors
    double R=sqrt(squdist(point_c1,point_c2));
    R/=2;
    double centerX=point_c1.x+point_c2.x;
    centerX/=2;
    double centerY=point_c1.y+point_c2.y;
    centerY/=2;
    cout<<centerX<<" , "<<centerY<<endl;
    double side_of_squar_inside=R*sqrt(2);
    centerX-=(side_of_squar_inside/2);
    centerY-=(side_of_squar_inside/2);
    double help_x,help_y;
    for(int i=3;i<=n_color;i++){
        help_x=(double)rand()/RAND_MAX;
        help_x*=side_of_squar_inside;
        help_y=(double)rand()/RAND_MAX;
        help_y*=side_of_squar_inside;
        t_color[i]--;
        insid_circle.push_back(Point(centerX+(help_x),centerY+(help_y),i));
        output.push_back(Point(centerX+(help_x),centerY+(help_y),i));
    }
    /// generating coordination of the points for colors except color 1 and 2
    double ax,ay;
    for(int i=3;i<=n_color;i++){
        for(int j=0;j<t_color[i];j++){
            ax=(double)rand()/RAND_MAX;
            ax=ax*(x);
            ay=(double)rand()/RAND_MAX;
            ay=ay*(y);
            output.push_back(Point(ax,ay,i));
        }
    }
    return output;


}

double makedelta(vector<Point> points,int k){
    double dist[k+1];
    Point P_1;
    Point P_2;
    double delta=MAX;
    double max_dist_point;
    for(int i=0;i<(int)points.size();i++){
        fill(dist,dist+k,MAX);
        max_dist_point=-1;
        P_1=points[i];
        for(int j=0;j<(int)points.size();j++){
            P_2=points[j];
            if(P_2.color!=P_1.color){
                /*cout<<"pos "<<i<<' '<<j<<endl;
                cout<<"collllllllor==>"<<P_2.color<<' '<<P_1.color<<endl;
                cout<<"first==>"<<dist[P_2.color-1]<<endl;*/

                dist[P_2.color]=min(dist[P_2.color],squdist(P_1,P_2));


                /*cout<<"dist==>"<<squdist(P_1,P_2)<<endl;
                cout<<"second==>"<<dist[P_2.color-1]<<endl;*/
            }
        }
        for(int j=0;j<k;j++){
            if(dist[j]!=MAX){
                max_dist_point=max(max_dist_point,dist[j]);
            }
        }

        if(max_dist_point!=-1)
            delta=min(delta,max_dist_point);
    }

    return sqrt(delta);
}

map<pll,set<int> > make_grid(vector<Point> points,double delta,double epsilon){
    ofstream file; ///for graphic
    file.open("C:\\Users\\Acer\\Desktop\\PP.txt");
    map<pll,set<int> > grid_table;
    /// square_side==>the side of square in the grid
    square_side=(epsilon)/3;
    square_side*=delta;
    file<<delta<<" "<<square_side<<" ";
    cout<<"side of squre==>"<<square_side<<endl;
    long long help_x,help_y;
    /// Changing every coordination of points which are given to me in integer form-
    ///    that they show the number of squares on all sides of coordination
    /// Every point can have different colors
    for(int i=0;i<(int)points.size();i++){
        help_x=floor(points[i].x/square_side);
        help_y=floor(points[i].y/square_side);
        file<<help_x<<" "<<help_y<<" "<<points[i].color<<" ";
        grid_table[pll(help_x,help_y)].insert(points[i].color);
    }
    /// printing starting points and random points in the circle
    help_x=floor(point_c1.x/square_side);
    help_y=floor(point_c1.y/square_side);
    cout<<"("<<help_x<<","<<help_y<<")\t";
    file<<help_x<<" "<<help_y<<" "<<1<<" ";
    help_x=floor(point_c2.x/square_side);
    help_y=floor(point_c2.y/square_side);
    cout<<"("<<help_x<<","<<help_y<<")"<<endl;
    file<<help_x<<" "<<help_y<<" "<<2<<" ";
    for(int i=0;i<insid_circle.size();i++){
        help_x=floor(insid_circle[i].x/square_side);
        help_y=floor(insid_circle[i].y/square_side);
        cout<<"("<<help_x<<","<<help_y<<")"<<endl;
        file<<help_x<<" "<<help_y<<" "<<i+3<<" ";
    }
    file.close();
    return grid_table;
}

/*//Considering some points which are located on the circle
void dividing_circle(double epsilon, Point center, double delta){
	double rad = (delta*(sqrt(2)+1))+2*M_PI;	//the radious of the circle
	int number_of_parts = 2*(M_PI)*rad/ sqrt(epsilon);// the number of the points
//	cout<<"number_of_parts: "<<number_of_parts<<endl;
	double angle = 0;
	pdd p;
	circle_points.clear();
    for (int i = 0; i < number_of_parts; i++){
        angle = i * (2*M_PI / number_of_parts);
        p.first = center.x + rad * cos(angle);
        p.first*=square_side*1.0;
        p.second = center.y + rad * sin(angle);
        p.second*=square_side*1.0 ;
		circle_points.push_back(p);
        //cout << "x -> " << p.first << " y -> " << p.second << "\n";
    }
    selected_points_size=int(circle_points.size());
}*/
void dividing_circle(double epsilon, Point center, double delta){
    double rad = (delta*(sqrt(2)+1));
    cout<<"rad"<<rad<<endl;
	int number_of_parts = 2*(M_PI)/ sqrt(epsilon);
	double h=sqrt(epsilon);
	cout<<"jazr"<<h<<endl;
	cout<<"number of part"<<number_of_parts<<endl;
	double angle = 0;
	pdd p;
	circle_points.clear();
    for (int i = 0; i < number_of_parts; i++){
        angle = i * (2*M_PI / number_of_parts);
        p.first = center.x + rad * cos(angle);
        p.first*=square_side*1.0;
        p.second = center.y + rad * sin(angle);
        p.second*=square_side*1.0 ;
		circle_points.push_back(p);
        //cout << "x -> " << p.first << " y -> " << p.second << "\n";
    }
    for(int i=0;i<number_of_parts;i++){
        cout<<"("<<circle_points[i].first<<","<<circle_points[i].second<<")"<<"--------";
    }
    cout<<endl;
    selected_points_size=int(circle_points.size());
}
///////////////

///////////////
///swap, orientation, distSq, compare, nextToTop and removingRepetitions functions are related to graham , which calcutes the CH of the points

void swap(pll p1, pll p2){
    pll temp = p1;
    p1 = p2;
    p2 = temp;
}

int orientation(pll p, pll q, pll r){
    int val = (q.second - p.second) * (r.first - q.first) -
              (q.first - p.first) * (r.second - q.second);
    if (val == 0) return 0;
    return (val > 0)? 1: 2;
}

int distSq(pll p1, pll p2){
    return (p1.first - p2.first)*(p1.first - p2.first) +
          (p1.second - p2.second)*(p1.second- p2.second);
}
int compare(const void *vp1, const void *vp2){
   pll *p1 = (pll *)vp1;
   pll *p2 = (pll *)vp2;
   int o = orientation(p0, *p1, *p2);
   if (o == 0)
     return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1;
   return (o == 2)? -1: 1;
}

pll nextToTop(stack<pll> S){
    pll p = S.top();
    S.pop();
    pll res = S.top();
    S.push(p);
    return res;
}

vector<pll> removingRepetitions(pll vec[], int n){
	int i;
	set<pll> s;
	for (i = 0; i < n; i++) {
		s.insert(vec[i]);
	}
	set<pll>::iterator it;
    vector<pll> updated;
	for (it = s.begin(); it != s.end(); ++it){
		pll g;
		g. first = it->first;
		g.second = it->second;
		updated.push_back(g);
	}

	return updated;
}

//Calcuting the Convex Hull of the points
void graham(){
    selected_convex_point.clear();
    selected_convex_point = removingRepetitions(selected_points, selected_points_size);
    int k=selected_convex_point.size();
    //Finding the starting point
	int ymin = selected_convex_point[0].second, min_index = 0;
	for(int i = 1; i < k; i++){
		int y = selected_convex_point[i].second;
		if((y < ymin) || (ymin == y &&
         selected_convex_point[i].first < selected_convex_point[min_index].first)){
         	ymin = selected_convex_point[i].second, min_index = i;
		 }
	}
	swap(selected_convex_point[0], selected_convex_point[min_index]);
	p0 = selected_convex_point[0];
	qsort(&selected_convex_point[1], k-1, sizeof(pll), compare);//Sorting points around the p0
	int m = 1;//The number of points which are not in a line
	for(int i = 1; i < k; i++){
		while (i < k-1 && orientation(p0, selected_convex_point[i],
                                    selected_convex_point[i+1]) == 0)
          i++;
       selected_convex_point[m] = selected_convex_point[i];
       m++;
	}
	if (m < 3) return;
	stack<pll> S;//It is keeping Ch points
	//The first and second points are in CH
    S.push(selected_convex_point[0]);
    S.push(selected_convex_point[1]);
    S.push(selected_convex_point[2]);
    for(int i = 3; i < m; i++){//Finding other points of CH
    	while (orientation(nextToTop(S), S.top(), selected_convex_point[i]) != 2){
    		S.pop();
		}
		S.push(selected_convex_point[i]);
	}
	selected_convex_point.clear();
	while(!S.empty()){
		selected_convex_point.push_back(S.top());
		S.pop();
	}
	for(int j=0;j<k;j++){
	    S.push(selected_convex_point[j]);
	}
	selected_convex_point.clear();
	while(!S.empty()){
		selected_convex_point.push_back(S.top());
		S.pop();
	}
}

//This function is related to making CH a bit larger
pdd gravity_point(){
    double midx=0,midy=0;
    for(int i=0;i<selected_points_size;i++){
        midx+=selected_points[i].first*1.0;
        midy+=selected_points[i].second*1.0;
    }
    midx*=square_side;
    midy*=square_side;
    midx/=selected_points_size;
    midy/=selected_points_size;
    pdd mid=pdd(midx,midy);
    return mid;
}

//This function is related to making CH a bit larger
pdd squar_norm_vec(pdd vec){
    double siz=vec.first*vec.first;
    pdd new_vec;
    siz+=vec.second*vec.second;
    siz=sqrt(siz);
    new_vec.first=vec.first*square_side*sqrt(2);
    new_vec.second=vec.second*square_side*sqrt(2);
    new_vec.first/=siz;
    new_vec.second/=siz;
    return new_vec;
}

//This function is related to making CH a bit larger
void enlarge_convex(){
    enlarge_points.clear();
    pdd mid=gravity_point();
    pdd vec;
    double x,y;
    for(int i=0;i<int(selected_convex_point.size());i++){
        x=(selected_convex_point[i].first*1.0);
        x*=square_side;
        y=(selected_convex_point[i].second*1.0);
        y*=square_side;
        vec.first=x-mid.first;
        vec.second=y-mid.second;
        vec=squar_norm_vec(vec);

        x+=vec.first;
        y+=vec.second;

        enlarge_points.push_back(pdd(x,y));
    }

}


vector<pll> points_in_convex_hull(vector<pll> points, vector<pdd> convex_hull){
	//auto start = high_resolution_clock::now();

	// remove all points that are outside of convex hull (on the right side of convex hull's edges)
	//vector<pll>new_points;
	double Ax, Ay, Bx, By, X, Y;
	int i = 0;
	while(i<points.size()){
		bool remove = false;
		for(int j=0; j<convex_hull.size()-1; j++) {
			// (Bx - Ax) * (Y - Ay) - (By - Ay) * (X - Ax)
			// It is 0 on the line, and >0 on left side, <0 on right side.
			Ax = convex_hull[j].first;
			Ay = convex_hull[j].second;
			Bx = convex_hull[j+1].first;
			By = convex_hull[j+1].second;
			X = points[i].first*square_side;
			Y = points[i].second*square_side;
			if(((Bx - Ax) * (Y - Ay) - (By - Ay) * (X - Ax)) < 0){
				points.erase(points.begin() + i);
				remove = true;
				break;
			}
		}
		if(remove == false){
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
		if(remove == false){
			i += 1;
		}
	}

	//auto stop = high_resolution_clock::now();
    //auto duration2 = duration_cast<milliseconds>(stop - start);
    //cout << "Time taken by function points_in_convex_hull: " << duration2.count() << " milliseconds" << endl;
	return points;
}

double diameter_square(vector<pll> points){
    int points_size=points.size();
    /// find number of rows
    int min = -1;
    int max = -1;
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
        if(left[points[i].second - min] == -1) {
            left[points[i].second - min] = points[i].first;
        }
        else if(left[points[i].second - min] > points[i].first) {
            left[points[i].second - min] = points[i].first;
        }

        /// find right in every row
        if(right[points[i].second - min] == -1) {
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
    /// diam = diam * gridSize * gridSize;
    return diam;
}

bool color_spanning(vector<pll> points){
	//auto start = high_resolution_clock::now();
	map<int,bool> color;
	for(int i=0; i<Mycolor.size(); i++){
		color.insert({Mycolor[i], false});
	}
	int color_count = 0;
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
	//auto stop = high_resolution_clock::now();
    //auto duration2 = duration_cast<milliseconds>(stop - start);
    //cout << "Time taken by function color_spanning: " << duration2.count() << " milliseconds" << endl;
	return check;
}

//This function finds the nearest point in the circle to a point on the circle based to depth
pll chosen_point(int dep){
    long long min_dist=100000000000,help_2;
    double help;
    int pos_point=0;
    bool seen=1;
    for(int i=0;i<dep;i++){
        help=((selected_points[i].first*square_side)-circle_points[dep].first)*((selected_points[i].first*square_side)-circle_points[dep].first)*1.0;
        help+=((selected_points[i].second*square_side)-circle_points[dep].second)*((selected_points[i].second*square_side)-circle_points[dep].second)*1.0;
        help_2=help*1000;
        if(min_dist>help_2){
            pos_point=i;
            min_dist=help_2;
        }
    }
    //cout<<"nearest_point"<<selected_points[pos_point].first<<selected_points[pos_point].second<<endl;
    return selected_points[pos_point];
}

//Making a decision about locating a point which is candidate in or out of a circle
int in_circle(pdd center,pll on_perimeter,pll candid){
    double x_2=((candid.first*square_side)-(center.first))*((candid.first*square_side)-(center.first))*1.0;
    double y_2=((candid.second*square_side)-(center.second))*((candid.second*square_side)-(center.second))*1.0;
    double r_2=(center.first-(on_perimeter.first*square_side))*(center.first-(on_perimeter.first*square_side))*1.0;
    r_2+=(center.second-(on_perimeter.second*square_side))*(center.second-(on_perimeter.second*square_side))*1.0;
    x_2+=y_2;
    long long x_n=x_2*1000;
    long long r_n=r_2*1000;
    if(x_n==r_n)return 2;
    if(x_n<r_n){
        return 1;}
    return 0;
}

//This function removes points which locate insude a circle
vector<pll> removing_point(vector<pll> points,pll on_perimeter,pdd center,int dep){
    int answer;
    vector<pll> new_points;
    for(int i=0;i<int(points.size());i++){
        answer=in_circle(center,on_perimeter,points[i]);
        if(answer==0||answer==2){
            new_points.push_back(points[i]);
        }

    }
    return new_points;
}

///New approach is indicated by this function
void practical_way(vector<pll> points,int dep){
    cooooonter1+=1;
    if(dep==selected_points_size){
        auto start = high_resolution_clock::now();
        graham(); //Calcuting the CH of the points
        enlarge_convex(); //The CH of the points is widened
        cooooonter+=1;
        vector<pll> core_set=points_in_convex_hull(delta_dist_points,enlarge_points);

        double diam=diameter_square(core_set);//Calcuting the diameter of core_set

        if(Min_rec>diam||(Min_rec==diam && vec_rec.size()>core_set.size())){
            if(color_spanning(core_set)){ //if core_set is color_spaning, solution might be updated
                vec_rec.clear();
                Min_rec=diam;
                ss_point.clear();
                for(int i=0;i<selected_convex_point.size();i++){
                    ss_point.push_back(selected_convex_point[i]);
                }
                core_set1.clear();
                for(int i=0;i<dep;i++){
                    core_set1.push_back(selected_points[i]);
                }
                for(int i=0;i<core_set.size();i++){
                    vec_rec.push_back(core_set[i]);
                }
            }
        }
        auto stop = high_resolution_clock::now();
        durationdepif += (duration_cast<milliseconds>(stop - start)).count();
        return ;
    }
    selected=max(selected,dep);
    pll pre_point=chosen_point(dep);//It is the nearest point in the circle to a point on the circle related to depth
    vector<pll> candidate;
    vector<pll> new_points;
    int answer;
    for(int i=0;i<int(points.size());i++){
        answer=in_circle(circle_points[dep],pre_point,points[i]);
        if(answer==1||answer==2){
            selected_points[dep].first=points[i].first;
            selected_points[dep].second=points[i].second;
            new_points.clear();
            new_points=removing_point(points,points[i],circle_points[dep],dep);///That point which locates in a circle is removed
            practical_way(new_points,dep+1);
        }
    }
}

int main()
{
    int number_of_color=15;
    int MaxX=3;
    int MaxY=3;
    int Max_of_member_color=10;
    int My_color_size=5;
    int max_member_subset=5;
    double epsilon=0.8;
    cooooonter=0;
    cooooonter1=0;
    durationdepif=0;
    Mycolor.clear();
    /// Getting colors from user
    int x;
    for(int i=0;i<My_color_size;i++){
        Mycolor.push_back(i+1);
    }
    selected=0;
    vector<Point> vec_of_point=maketest(MaxX,MaxY,Max_of_member_color,number_of_color);
    double delta=makedelta(vec_of_point,number_of_color);
    auto start = high_resolution_clock::now();
    delta*=2;
    cout<<"delta==>"<<delta<<endl;
    grid=make_grid(vec_of_point,delta,epsilon);
    for (std::map<pll,set<int> >::iterator it=grid.begin(); it!=grid.end(); ++it){
        key.push_back(it->first);

    }
    cout<<key.size()<<endl;
    double help;
    vector<pll> new_points;
    int key_size=key.size();
    for(int i=0;i<key_size;i++){
        delta_dist_points.clear();
        delta_dist_points.push_back(key[i]);
        for(int j=0;j<key_size;j++){
            if(i==j)continue;
            help=(key[i].first-key[j].first)*(key[i].first-key[j].first)+(key[i].second-key[j].second)*(key[i].second-key[j].second);
            help*=square_side*square_side;

            if(help<=((delta*delta))){
                delta_dist_points.push_back(key[j]);

            }

        }
        dividing_circle(epsilon,Point(key[i].first,key[i].second,0),delta);
        for(int k=0;k<int(delta_dist_points.size());k++){
            selected_points[0]=delta_dist_points[k];
            new_points.clear();
            new_points=removing_point(delta_dist_points,delta_dist_points[k],circle_points[0],0);
            if(new_points.size()>0){
			            practical_way(new_points,1);
            }
        }

    }
    cout<<"core_set"<<endl;
    for(int i=0;i<vec_rec.size();i++){
        cout<<vec_rec[i].first<<","<<vec_rec[i].second<<endl;
    }
    cout<<"MIN_diam==>"<<sqrt(Min_rec)*square_side<<endl;
    auto stop = high_resolution_clock::now();
    auto duration2 = duration_cast<milliseconds>(stop - start);
    cout << "Total taken time: " << duration2.count() << " milliseconds" << endl;
    cout << "dep if time: " << durationdepif << " milliseconds" << endl;
    cout<<"time of repeat of dep==>"<<cooooonter<<endl;
    cout<<"time of repeat practical==>"<<cooooonter1<<endl;
    return 0;
}
