#include <bits/stdc++.h>
#include "point.h"
#define pdd pair<double,double>
using namespace std;
double squdist(Point a,Point b){
    double dist=(a.x-b.x)*(a.x-b.x);
    dist+=((a.y-b.y)*(a.y-b.y));
    return dist;
}
///maketest (max x coordinates,max y coordinates , top of number per color , number of color)
vector<Point> maketest(double x,double y,int top,int n_color){
    srand(time(0));
    vector<Point> output;
    /// generating number of colors in t_color for each of colors
    vector<int> t_color;
    t_color.push_back(0);
    for(int i=1;i<=n_color;i++){
        t_color.push_back((rand()%top)+1);
        //cout<<t_color[i]<<"\t";
    }
    //cout<<endl;
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
    Point point_c1;
    Point point_c2;
    for(int i=0;i<t_color[1];i++){
        for(int j=0;j<t_color[2];j++){
            //cout<<squdist(listpoints_c1[i],listpoints_c2[j])<<endl;
            if(dist>squdist(listpoints_c1[i],listpoints_c2[j])){
                dist=squdist(listpoints_c1[i],listpoints_c2[j]);
                point_c1=listpoints_c1[i];
                point_c2=listpoints_c2[j];
            }
        }
    }
    cout<<"dist==>"<<dist<<endl;
    /// generating points where has located in the circle,
    ///   by diam between the point_c1 and the point_c2 for each of colors
    double R=sqrt(squdist(point_c1,point_c2));
    R/=2;
    double centerX=point_c1.x+point_c2.x;
    centerX/=2;
    double centerY=point_c1.y+point_c2.y;
    centerY/=2;
    double r;
    double teta;
    for(int i=3;i<=n_color;i++){
        r=R*(rand()/RAND_MAX);
        teta=(rand()/RAND_MAX)*2*M_PI;
        t_color[i]--;
        output.push_back(Point(centerX+(r*cos(teta)),centerY+(r*sin(teta)),i));
    }
    /// generating coordination of the points for other colors
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
int main()
{
    vector<Point> a;
    a=maketest(100,100,10,10);
    cout<<"Point==:"<<endl;
    for(int i=0;i<(int)a.size();i++){
        cout<<"("<<a[i].x<<","<<a[i].y<<","<<a[i].color<<")"<<endl;
    }
    return 0;
}
