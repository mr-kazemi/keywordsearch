#include <bits/stdc++.h>
#include "point.h"
using namespace std;

///square of distance between two points
double squdist(Point a,Point b){
    double dist=(a.x-b.x)*(a.x-b.x);
    dist+=((a.y-b.y)*(a.y-b.y));
    return dist;
}


/// maketest ("max_x" max in x coordinates ,"max_y" max in y coordinates , "top_ncolor" max number of each color , "n_color" number of color)
vector<Point> maketest(double max_x,double max_y,int top_ncolor,int n_color){
    srand(time(0));
    vector<Point> output;/// vector of points that generated
    /// generating number of colors in "ni_color" vector for each of colors
    vector<int> ni_color;
    ni_color.push_back(0);
    ///fill the 'ni_color' with random number
    ///     top of the random number is "top_ncolor"
    for(int i=1;i<=n_color;i++){
        ni_color.push_back((rand()%top_ncolor)+1);
    }
    /// generating coordination of points for the color 1 with random number,
    ///         top number of coordinations is (max_x,max_y)
    Point listpoints_c1[ni_color[1]];
    for(int i=0;i<ni_color[1];i++){
        listpoints_c1[i].x=(double)rand()/RAND_MAX;
        listpoints_c1[i].x*=max_x;
        listpoints_c1[i].y=(double)rand()/RAND_MAX;
        listpoints_c1[i].y*=max_y;
        listpoints_c1[i].color=1;
        output.push_back(Point(listpoints_c1[i].x,listpoints_c1[i].y,1));
    }

    /// generating coordination of points for the color 2 with random number,
    ///         top number of coordinations is (max_x,max_y)
    Point listpoints_c2[ni_color[2]];
    for(int i=0;i<ni_color[2];i++){
        listpoints_c2[i].x=(double)rand()/RAND_MAX;
        listpoints_c2[i].x*=max_x;
        listpoints_c2[i].y=(double)rand()/RAND_MAX;
        listpoints_c2[i].y*=max_y;
        listpoints_c2[i].color=2;
        output.push_back(Point(listpoints_c2[i].x,listpoints_c2[i].y,2));
    }

    /// finding minimum diameter between the points of color 1 and color 2
    Point point_c1,point_c2; /// start points to make circle (color 1 and 2)
    double min_diam=(max_x*max_x)+(max_y*max_y)+1;/// save possible maximum value in "min_diam" for diameter and then find minimum
    ///trace all points in color 1 and color 2
    for(int i=0;i<ni_color[1];i++){
        for(int j=0;j<ni_color[2];j++){
            if(min_diam>squdist(listpoints_c1[i],listpoints_c2[j])){
                min_diam=squdist(listpoints_c1[i],listpoints_c2[j]);
                point_c1=listpoints_c1[i];
                point_c2=listpoints_c2[j];
            }
        }
    }

    cout<<"min_diam==>"<<sqrt(min_diam)<<endl;
    /// generating points located in the circle,
    ///   by diameter between the "point_c1" and the "point_c2" for each of colors
    double R=sqrt(squdist(point_c1,point_c2));///Radius of circle between "point_c1" and "point_c2"
    R/=2;
    double centerX=point_c1.x+point_c2.x;///find X coordinate for center of circle
    centerX/=2;
    double centerY=point_c1.y+point_c2.y;///find Y coordinate for center of circle
    centerY/=2;
    cout<<"center of the circle"<<centerX<<" , "<<centerY<<endl;
    double side_of_squar_inside=R*sqrt(2);///? /// reduce Radius for sure points located in circle
    centerX-=(side_of_squar_inside/2);///?
    centerY-=(side_of_squar_inside/2);///?
    double help_x,help_y;///helping variable for generate point in circle
    vector<Point> insid_circle; /// points of other colors in the circle
    for(int i=3;i<=n_color;i++){
        help_x=(double)rand()/RAND_MAX;
        help_x*=side_of_squar_inside;
        help_y=(double)rand()/RAND_MAX;
        help_y*=side_of_squar_inside;
        ni_color[i]--;
        insid_circle.push_back(Point(centerX+(help_x),centerY+(help_y),i));
        output.push_back(Point(centerX+(help_x),centerY+(help_y),i));
    }
    /// generating coordination of the rest points for colors except color 1 and 2
    double ax,ay;
    for(int i=3;i<=n_color;i++){
        for(int j=0;j<ni_color[i];j++){
            ax=(double)rand()/RAND_MAX;
            ax=ax*(max_x);
            ay=(double)rand()/RAND_MAX;
            ay=ay*(max_y);
            output.push_back(Point(ax,ay,i));
        }
    }
    /// graphic part
    ofstream file;
    file.open("C:\\Users\\Acer\\Desktop\\Point_Data.txt");
    file<<n_color<<" ";
    file<<point_c1.x<<" "<<point_c1.y<<" "<<point_c1.color<<" ";
    file<<point_c2.x<<" "<<point_c2.y<<" "<<point_c2.color;
    for(int i=0;i<int(insid_circle.size());i++){
        file<<" "<<insid_circle[i].x<<" "<<insid_circle[i].y<<" "<<insid_circle[i].color;
    }
    for(int i=0;i<int(output.size());i++){

        file<<" "<<output[i].x<<" "<<output[i].y<<" "<<output[i].color;
    }
    file.close();
    ///

    return output;


}
int main()
{
    vector<Point> all_points=maketest(5,3,5,6);
    return 0;
}
