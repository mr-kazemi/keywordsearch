#include<iostream>
#include <vector>
using namespace std;
struct Point{
    long double x, y;
    int color;
    Point(long double x1= 0, long double y1= 0, int color1= 0){
        x = x1;
        y = y1;
        color = color1;
    }
};
bool checking(vector<Point> point, int m){
    bool check[m];
    int n = point.size();
    for (int l = 0; l <n; l++)
        check[point[l].color] = true;
    for (int l = 0; l < m; l++){
        if (check[l] == false){
            return 0;
        }
    }
    return 1;
}
int main(){
    int m = 2;//the number of colors
    vector<Point> c;// just as an example for checking
    Point d = Point(0.49, 0.001, 0);
    Point k = Point(2, -5, 0);
    c.push_back(d);
    c.push_back(k);
    cout<<checking(c, m);
    return 0;
}
