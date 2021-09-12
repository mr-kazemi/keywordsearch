#include <bits/stdc++.h>
#include "point.h"
using namespace std;
//#include <chrono>
//using namespace std::chrono;
#define pll pair<long long, long long>

double MAX = 10000000000.0; /// used in make delta
vector<pll> key; /// all point in grid
vector<pll> delta_dist_points; /// in vector delta_dist_points, there are points within distance of delta from point delta_dist_points[0]
Point point_c1,point_c2; /// start points to make circle (color 1 and 2)
//vector<Point> insid_circle; /// points of other colors in the circle
double best_diameter = -1; /// to save the best diameter
double square_side;
vector<pll> final_points; /// subset of points that have best diameter
map<pll, set<int>> grid;

/// square of distance between two points
double squdist(Point a, Point b) {
    double dist = (a.x - b.x) * (a.x - b.x);
    dist += ((a.y - b.y) * (a.y - b.y));
    return dist;
}

/// maketest (max x coordinates, max y coordinates, max number of each color, number of color)
vector<Point> maketest(double x, double y, int top, int n_color) {
    //auto start = high_resolution_clock::now();
    srand(time(0));
    vector<Point> output;
    /// generating number of colors in t_color for each of colors
    vector<int> t_color;
    t_color.push_back(0);
    for (int i=1; i<=n_color; i++) {
        t_color.push_back((rand() % top) + 1);
    }
    /// generating coordination of points for the color 1
    Point listpoints_c1[t_color[1]];
    for (int i=0; i<t_color[1]; i++) {
        listpoints_c1[i].x = (double)rand() / RAND_MAX;
        listpoints_c1[i].x *= x;
        listpoints_c1[i].y = (double)rand() / RAND_MAX;
        listpoints_c1[i].y *= y;
        output.push_back(Point(listpoints_c1[i].x, listpoints_c1[i].y, 1));
    }

    /// generating coordination of points for the color 2
    Point listpoints_c2[t_color[2]];
    for (int i=0; i<t_color[2]; i++) {
        listpoints_c2[i].x = (double)rand() / RAND_MAX;
        listpoints_c2[i].x *= x;
        listpoints_c2[i].y = (double)rand() / RAND_MAX;
        listpoints_c2[i].y *= y;
        output.push_back(Point(listpoints_c2[i].x, listpoints_c2[i].y, 2));
    }

    /// finding minimum diam between the points of color 1 and color 2
    double dist = (x * x) + (y * y) + 1;
    for (int i=0; i<t_color[1]; i++) {
        for (int j=0; j<t_color[2]; j++) {
            if (dist > squdist(listpoints_c1[i], listpoints_c2[j])) {
                dist = squdist(listpoints_c1[i], listpoints_c2[j]);
                point_c1 = listpoints_c1[i];
                point_c2 = listpoints_c2[j];
            }
        }
    }

    cout << "dist in specific test case ==> " << sqrt(dist) << endl;
    /// generating points located in the circle,
    ///   by diam between the point_c1 and the point_c2 for each of colors
    double R = sqrt(squdist(point_c1, point_c2));
    R /= 2;
    double centerX = point_c1.x + point_c2.x;
    centerX /= 2;
    double centerY = point_c1.y + point_c2.y;
    centerY /= 2;
    //cout << centerX << " , " << centerY << endl;
    double side_of_squar_inside = R * sqrt(2);
    centerX -= (side_of_squar_inside / 2);
    centerY -= (side_of_squar_inside / 2);
    double help_x, help_y;
    for (int i=3; i<=n_color; i++) {
        help_x = (double)rand() / RAND_MAX;
        help_x *= side_of_squar_inside;
        help_y = (double)rand() / RAND_MAX;
        help_y *= side_of_squar_inside;
        t_color[i] --;
        //insid_circle.push_back(Point(centerX + (help_x), centerY+(help_y), i));
        output.push_back(Point(centerX + (help_x), centerY+(help_y), i));
    }
    /// generating coordination of the points for colors except color 1 and 2
    double ax, ay;
    for (int i=3; i<=n_color; i++) {
        for (int j=0; j<t_color[i]; j++) {
            ax = (double)rand() / RAND_MAX;
            ax = ax * (x);
            ay = (double)rand() / RAND_MAX;
            ay = ay * (y);
            output.push_back(Point(ax, ay, i));
        }
    }

    //auto stop = high_resolution_clock::now();
    //auto duration2 = duration_cast<milliseconds>(stop - start);
    //cout << "Time taken by function maketest: " << duration2.count() << " milliseconds" << endl;
    return output;


}
double makedelta(vector<Point> points, int num_colors) {
    //auto start = high_resolution_clock::now();

    double dist[num_colors + 1];///In each round of loop,distance between a point and each color
    Point P_1;
    Point P_2;
    double delta = MAX;
    double max_dist_point;
    for (int i=0; i<(int)points.size(); i++) {
        fill(dist, dist + (num_colors + 1), MAX);
        max_dist_point = -1;
        P_1 = points[i];
        for (int j=0; j<(int)points.size(); j++) {
            P_2 = points[j];
            if (P_2.color != P_1.color) {
                dist[P_2.color] = min(dist[P_2.color], squdist(P_1, P_2));
            }
        }
        for (int j=1; j<=num_colors; j++) {
            if (dist[j] != MAX) {
                max_dist_point = max(max_dist_point, dist[j]);
            }
        }

        if (max_dist_point != -1)
            delta = min(delta, max_dist_point);
    }

    //auto stop = high_resolution_clock::now();
    //auto duration2 = duration_cast<milliseconds>(stop - start);
    //cout << "Time taken by function makedelta: " << duration2.count() << " milliseconds" << endl;
    return sqrt(delta);

}

map<pll, set<int>> make_grid(vector<Point> points, double delta, double epsilon) {
    //auto start = high_resolution_clock::now();

    //ofstream file; /// for graphic
    //file.open("C:\\Users\\Fatemi\\Desktop\\PP.txt");
    map<pll, set<int>> grid_table;
    /// square_side ==> the side of square in the grid
    square_side = (epsilon) / 3;
    square_side *= delta;
    //file << delta << " " << square_side << " ";
    //file << point_c1.x << " " << point_c1.y << " ";
    //file << point_c2.x << " " << point_c2.y << " ";
    //cout << "side of squre ==> " << square_side << endl;
    long long help_x, help_y;
    /// Changing every coordination of points which are given to me in integer form-
    ///    that they show the number of squares on all sides of coordination
    /// Every point can have different colors
    for (int i=0; i<(int)points.size(); i++) {
        help_x = floor(points[i].x / square_side);
        help_y = floor(points[i].y / square_side);
        //file << help_x << " " << help_y << " " << points[i].color << " ";
        grid_table[pll(help_x, help_y)].insert(points[i].color);
    }
    /// printing starting points and random points in the circle
   /*help_x = floor(point_c1.x / square_side);
    help_y = floor(point_c1.y / square_side);
    cout << "(" << help_x << "," << help_y << ")\t";
    file << help_x << " " << help_y << " " << 1 << " ";
    help_x = floor(point_c2.x / square_side);
    help_y = floor(point_c2.y / square_side);
    cout << "(" << help_x << "," << help_y << ")" << endl;
    file << help_x << " " << help_y << " " << 2 << " ";
    for (int i=0; i<insid_circle.size(); i++) {
        help_x = floor(insid_circle[i].x / square_side);
        help_y = floor(insid_circle[i].y / square_side);
        cout << "(" << help_x << "," << help_y << ")" << endl;
        file << help_x << " " << help_y << " " << i + 3 << " ";
    }
    file.close();*/

    //auto stop = high_resolution_clock::now();
    //auto duration2 = duration_cast<milliseconds>(stop - start);
    //cout << "Time taken by function make_grid: " << duration2.count() << " milliseconds" << endl;
    return grid_table;
}

double diameter_square(pll points[], int points_size) {
    //auto start = high_resolution_clock::now();

    /// find number of rows
    int min = -1;
    int max = -1;
    for (int i=0; i<points_size; i++) {
        if (min == -1 || min > points[i].second) {
            min = points[i].second;
        }
        if (max == -1 || max < points[i].second) {
            max = points[i].second;
        }
    }
    int num_rows = max - min + 1;

    /// find left most and right most in each row
    vector<long long> left;
    vector<long long> right;
    for (int i=0; i<num_rows; i++) {
        left.push_back(-1);
        right.push_back(-1);
    }

    for (int i=0; i<points_size; i++) {
        /// find left in every row
        if (left[points[i].second - min] == -1) {
            left[points[i].second - min] = points[i].first;
        }
        else if (left[points[i].second - min] > points[i].first) {
            left[points[i].second - min] = points[i].first;
        }

        /// find right in every row
        if (right[points[i].second - min] == -1) {
            right[points[i].second - min] = points[i].first;
        }
        else if (right[points[i].second - min] < points[i].first) {
            right[points[i].second - min] = points[i].first;
        }
    }

    /// find diameter
    double diam = 0;
    double d = 0;
    for (int i=0; i<left.size(); i++) {
        if (left[i] == -1) {
            continue;
        }
        for (int j=0; j<right.size(); j++) {
            if (right[j] == -1) {
                continue;
            }
            d = (i - j) * (i - j) + (left[i] - right[j]) * (left[i] - right[j]);
            if (diam < d) {
                diam = d;
            }
        }
        for (int j=i; j<left.size(); j++) {
            if (right[j] == -1) {
                continue;
            }
            d = (i - j) * (i - j) + (left[i] - left[j]) * (left[i] - left[j]);
            if (diam < d) {
                diam = d;
            }
        }
    }

    /// diam = diam * gridSize * gridSize;
    //auto stop = high_resolution_clock::now();
    //auto duration2 = duration_cast<milliseconds>(stop - start);
    //cout << "Time taken by function diameter_square: " << duration2.count() << " milliseconds" << endl;
    return diam;
}

/// position in delta_dist_points, subset of points, position of element in array subset, number of left points to choose for subset,
///   number of unselected color,array of counting colors
void colorspanning_subset(int pos, pll subset[], int pos_subset, int num_member_left, int cont, int color_counter[]) {
    //auto start = high_resolution_clock::now();

    if (num_member_left == 0) {
        if (cont == 0){ /// if color spaning
            /// calculate diameter of subset
            double diam = diameter_square(subset, pos_subset);
            /// update best diameter and best final points
            if (best_diameter == -1 || best_diameter > diam) {
                best_diameter = diam;
                final_points.clear();
                for (int i=0; i<pos_subset; i++) {
                    final_points.push_back(subset[i]);

                }
            }
        }
        return;
    }
    /// impossible to make such subset
    if (((int)delta_dist_points.size()) - pos + 1 <= num_member_left) {
        return;
    }
    if (pos >= ((int)delta_dist_points.size())) {
       return;
    }
    /// ==> if delta_dist_points[pos] is in array subset
    subset[pos_subset] = (delta_dist_points[pos]);
    set<int> b = grid[delta_dist_points[pos]];
    for (set<int>::iterator it = b.begin(); it!=b.end(); ++it) {
        if (color_counter[*it] != -1) {
            if (color_counter[*it] == 0) {
                cont --;
            }
            color_counter[*it] ++;
        }
    }

    colorspanning_subset(pos + 1, subset,pos_subset + 1, num_member_left - 1, cont, color_counter);
    /// ==> if delta_dist_points[pos] is not in array subset
    /// configuration conditions for removing delta_dist_points[pos] and minus its colors from color_counter
    for (set<int>::iterator it = b.begin(); it!=b.end(); ++it) {
        if (color_counter[*it] != -1) {
            if (color_counter[*it] == 1) {
                cont ++;
            }
            color_counter[*it] --;
        }
    }
    colorspanning_subset(pos + 1, subset, pos_subset, num_member_left, cont, color_counter);

    //auto stop = high_resolution_clock::now();
    //auto duration2 = duration_cast<milliseconds>(stop - start);
    //cout << "Time taken by function colorspanning_subset: " << duration2.count() << " milliseconds" << endl;
}

void check_every_subset(int m, int max_member_subset, vector<int> Mycolor, double delta) {
    //auto start = high_resolution_clock::now();

    int color_counter[m + 1]; /// number of each color
    fill(color_counter, color_counter + (m + 1), -1);
    int sp_col_size = (int)Mycolor.size();
    /// -1:not in Mycolor,0:in Mycolor
    for (int i=0; i<sp_col_size; i++) {
        color_counter[Mycolor[i]] = 0;
    }
    int cont = sp_col_size;
    double help;
    int key_size = key.size();
    pll subset[max_member_subset];
    /// subsets of size less than max_member_subset for each row
    for (int i=0; i<key_size; i++) {
        delta_dist_points.clear();
        delta_dist_points.push_back(key[i]);
        for (int j=0; j<key_size; j++) {
            if (i == j) continue;
            help = (key[i].first - key[j].first) * (key[i].first - key[j].first) + (key[i].second - key[j].second) * (key[i].second - key[j].second);
            help *= square_side * square_side;

            if (help <= (delta * delta)) {
                delta_dist_points.push_back(key[j]);

            }

        }
        cont = sp_col_size;
        set<int> b = grid[key[i]];
        for (set<int>::iterator it = b.begin(); it!=b.end(); ++it) {
            if (color_counter[*it] != -1) {
                if (color_counter[*it] == 0) {
                    cont --;
                }
                color_counter[*it] ++;
            }
        }
        for (int j=1; j<=max_member_subset; j++) {

            subset[0] = key[i];

            colorspanning_subset(1, subset, 1, j - 1, cont,color_counter);
        }
        for (int i=0; i<sp_col_size; i++) {
            color_counter[Mycolor[i]] = 0;
        }
    }

    //auto stop = high_resolution_clock::now();
    //auto duration2 = duration_cast<milliseconds>(stop - start);
    //cout << "Time taken by function check_every_subset: " << duration2.count() << " milliseconds" << endl;
}


int main()
{
    //auto start = high_resolution_clock::now();

    int number_of_color = 10;
    int MaxX = 50;
    int MaxY = 50;
    int Max_of_member_color = 100;
    int My_color_size = 5;
    int max_member_subset = 5;
    double epsilon = 0.2;
    vector<Point> vec_of_point = maketest(MaxX, MaxY, Max_of_member_color, number_of_color);
    //cout << vec_of_point.size() << endl;
    double delta = makedelta(vec_of_point, number_of_color);
    delta *= 2;
    cout << "delta ==> " << delta << endl;
    grid = make_grid(vec_of_point, delta, epsilon);
    /// fills key
    for (std::map<pll,set<int>>::iterator it = grid.begin(); it!=grid.end(); ++it) {
        key.push_back(it -> first);
    }
    //cout << key.size() << endl;



    vector<int> Mycolor; /// colors to use in making color spanning subset
    /// get colors from user
    int x;
    for (int i=0; i<My_color_size; i++) {
        //cin >> x;
        //cout << i+1 << endl;
        Mycolor.push_back(i + 1);
    }


    check_every_subset(number_of_color, max_member_subset, Mycolor,delta);
    best_diameter = best_diameter * square_side * square_side;
    cout << "diamter ==> " << sqrt(best_diameter) << endl;
    cout << "final subset:" << endl;
    for (int i=0; i<final_points.size(); i++) {
        cout << "("<<final_points[i].first << " , " << final_points[i].second << ")" << endl;

    }
    cout << endl;

    //auto stop = high_resolution_clock::now();
    //auto duration2 = duration_cast<milliseconds>(stop - start);
    //cout << "Total taken time: " << duration2.count() << " milliseconds" << endl;
    return 0;
}
