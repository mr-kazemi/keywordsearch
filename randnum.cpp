#include <bits/stdc++.h>
#include "point.h"
using namespace std;
vector<Point> rand_num_generation(double x,double y,int k,int n){
    srand(time(0));
    vector<Point> point;
    double ax,ay;
    int color;
    for(int i=0;i<n;i++){
        ax=(double)rand()/RAND_MAX;
        ax=ax*(x);
        ay=(double)rand()/RAND_MAX;
        ay=ay*(y);
        color=(rand()%k)+1;
        //cout<<ax<<" , "<<ay<<" , "<<color<<endl;
        point.push_back(Point(ax,ay,color));
    }
    return point;
}
int main()
{
    cout<<endl;
    //vector<Point> a=rand_num_generation(100,500,10,100);
    return 0;
}
