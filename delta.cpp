#include <bits/stdc++.h>
#include "point.h"
using namespace std;
double MAX=10000000000.0;
double squdist(Point a,Point b){
    double dist=(a.x-b.x)*(a.x-b.x);
    dist+=((a.y-b.y)*(a.y-b.y));
    return dist;
}
double makedelta(vector<Point> point,int k){
    double dist[k];
    Point P_1;
    Point P_2;
    double delta=MAX;
    double max_dist_point;
    for(int i=0;i<(int)point.size();i++){
        fill(dist,dist+k,MAX);
        max_dist_point=-1;
        P_1=point[i];
        for(int j=0;j<(int)point.size();j++){
            P_2=point[j];
            if(P_2.color!=P_1.color){
                /*cout<<"pos "<<i<<' '<<j<<endl;
                cout<<"collllllllor==>"<<P_2.color<<' '<<P_1.color<<endl;
                cout<<"first==>"<<dist[P_2.color-1]<<endl;*/

                dist[P_2.color-1]=min(dist[P_2.color-1],squdist(P_1,P_2));


                /*cout<<"dist==>"<<squdist(P_1,P_2)<<endl;
                cout<<"second==>"<<dist[P_2.color-1]<<endl;*/
            }
        }
        for(int j=0;j<k;j++){
            if(dist[j]!=MAX){
                max_dist_point=max(max_dist_point,dist[j]);
            }
        }
        //cout<<i<<" max dist per point "<<max_dist_point<<endl;

        if(max_dist_point!=-1)
            delta=min(delta,max_dist_point);
    }
    //cout<<delta<<endl;

    return sqrt(delta);

}

int main()
{
    double x,y;
    int color;
    Point p;
    vector<Point> point;
    while(true){
        cin>>x>>y>>color;
        if(x==0 && y==0&&color==0)
            break;
        p=Point(x,y,color);
        point.push_back(p);

    }
    cout<<makedelta(point,3)<<endl;
    return 0;
}
/*
3 4 1
5 6 1
0 0 1
2 2 2
8 7 2
5 4 3
6 4 3
0 0 0
*/
