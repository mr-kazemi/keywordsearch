#include <bits/stdc++.h>
#include "point.h"
using namespace std;
#define pll pair<long long,long long>

map<pll,set<int> > task_2(vector<Point> point,double delta,double epsilon){
    map<pll,set<int> > table;
    double a=(epsilon)/3;
    a*=delta;
    long long help_x,help_y;
    for(int i=0;i<(int)point.size();i++){
        help_x=floor(point[i].x/a);
        help_y=floor(point[i].y/a);
        //cout<<help_x<<' '<<help_y<<endl;
        table[pll(help_x,help_y)].insert(point[i].color);
    }
    return table;
}
int main()
{
    vector<Point> c;
    Point d=Point(0.49,0.001,1);
    c.push_back(d);
    map<pll,set<int> > a=task_2(c,3,0.11);
    //cout<<a[pll(0.44,0)].size()<<endl;
    //set<int> b=a[pdd(1.33,2)];
    /*for(set<int>::iterator it=b.begin();it!=b.end();++it){
        cout<<*it<<endl;
    }*/
    return 0;
}
