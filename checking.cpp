#include<iostream>
#include <vector>
#include "point.h"
using namespace std;
//This a checking function that checks point has the all of colors in the theNumberOfColors
bool checking(vector<Point> point, int m, vector<int> theNumberOfColors){
    bool check[m] = {false};
    int n = point.size();
    for (int l = 0; l <n; l++)
        check[point[l].color] = true;
    int sizeColors = theNumberOfColors.size();
    for (int l = 0; l < sizeColors; l++){
        if (check[theNumberOfColors[l]] == false){
            return 0;
        }
    }
    return 1;
}
int main(){
    int m = 10;//the number of all colors
    vector<Point> c;// just as an example for checking
    Point d = Point(0.49, 0.001, 0);
    Point k = Point(2, -5, 1);
    c.push_back(d);
    c.push_back(k);
    vector<int> theNumberOfColors;
    theNumberOfColors.push_back(0);
    theNumberOfColors.push_back(1);
    theNumberOfColors.push_back(2);
    theNumberOfColors.push_back(3);
    cout<<checking(c, m, theNumberOfColors);
    return 0;
}
