#include <bits/stdc++.h>
#include <graphics.h>
#include "point.h"
using namespace std;
#define pll pair<long long,long long>
double MAX=10000000000.0;
vector<pll> key;
Point point_c1,point_c2;
vector<Point> insid_circle;
float best_diameter = -1;
vector<pll> final_points;
//pll final_points[];
map<pll,set<int> > grid;
int number;
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
        insid_circle.push_back(Point(centerX+(r*cos(teta)),centerY+(r*sin(teta)),i));
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
        //cout<<i<<" max dist per point "<<max_dist_point<<endl;

        if(max_dist_point!=-1)
            delta=min(delta,max_dist_point);
    }
    //cout<<delta<<endl;

    return sqrt(delta);

}
map<pll,set<int> > task_2(vector<Point> points,double delta,double epsilon){
    //ofstream file;
    //file.open("C:\\Users\\Acer\\Desktop\\PP.txt");
    map<pll,set<int> > table;
    double a=(epsilon)/3;
    /// a==>the side of square in the grid
    a*=delta;
    cout<<"side of squre==>"<<a<<endl;
    long long help_x,help_y;
    /// Changing every coordination of points which give to me in to the integers-
    ///    that they show the number of squares on all sides of coordination
    /// Every point can have different colors
    for(int i=0;i<(int)points.size();i++){
        help_x=floor(points[i].x/a);
        help_y=floor(points[i].y/a);
        //cout<<help_x<<' '<<help_y<<endl;
        //row.insert(help_y);
        //file<<help_x<<" "<<help_y<<" "<<points[i].color<<" ";
        table[pll(help_x,help_y)].insert(points[i].color);
    }
    help_x=floor(point_c1.x/a);
    help_y=floor(point_c1.y/a);
    cout<<"("<<help_x<<","<<help_y<<")\t";
    help_x=floor(point_c2.x/a);
    help_y=floor(point_c2.y/a);
    cout<<"("<<help_x<<","<<help_y<<")"<<endl;
    for(int i=0;i<insid_circle.size();i++){
        help_x=floor(insid_circle[i].x/a);
        help_y=floor(insid_circle[i].y/a);
        cout<<"("<<help_x<<","<<help_y<<")"<<endl;
    }
    return table;
}

double diameter_square(pll points[], int points_size){

    //find number of rows
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

    // find left most and right most in each row
    vector<long long> left;
    vector<long long> right;
    for(int i=0; i<num_rows; i++){
        left.push_back(-1);
        right.push_back(-1);
    }

    for(int i=0; i<points_size; i++){
        // find left in every row
        if(left[points[i].second - min] == -1) {
            left[points[i].second - min] = points[i].first;
        }
        else if(left[points[i].second - min] > points[i].first) {
            left[points[i].second - min] = points[i].first;
        }

        // find right in every row
        if(right[points[i].second - min] == -1) {
            right[points[i].second - min] = points[i].first;
        }
        else if(right[points[i].second - min] < points[i].first) {
            right[points[i].second - min] = points[i].first;
        }
    }

    // find diameter
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

    //diam = diam * gridSize * gridSize;

    return diam;
}

///position pos in key,vector of chose element,position of element in a,const number member of subset,number of unselected color,position list of my color,array of counting my color
void f(int pos,pll a[],int posa,int k,int cont,int collpos[],int contcol[]){
    if(((int)key.size())-pos+1<k){
        return;
    }
    //cout<<pos<<"\t"<<cont<<endl;
    if(k==0){

        //cout<<number<<endl;
        /*for(int i=0;i<posa;i++){
            cout<<"("<<a[i].first<<","<<a[i].second<<")"<<" , ";
        }*/
        //cout<<endl;
        if(cont==0){
            /// here is correct position to check diameter
            //int points_size = sizeof(a)/sizeof(a[0]);
            double diam = diameter_square(a, posa);
            if(best_diameter == -1 || best_diameter > diam) {
                best_diameter = diam;
                cout<<"ss"<<endl;
                for(int i=0; i<posa; i++){
                    final_points.push_back(a[i]);

                }
                final_points.push_back(pll(0,0));
                //final_points = a;
            }
            //cout<<"calculate diam"<<endl;
            number++;
            //cout<<"color spanning"<<endl;
        }
        /*else{
            cout<<"not color spanning"<<endl;
        }*/
        return;
    }
    if(pos>=((int)key.size())){
       return;
    }
    //cout<<cont<<endl;
    ///if key[pos] is in a
    a[posa]=(key[pos]);
    set<int> b=grid[key[pos]];
    for(set<int>::iterator it=b.begin();it!=b.end();++it){
        if(collpos[*it]!=-1){
            if(contcol[collpos[*it]]==0){
                cont--;
            }
            contcol[collpos[*it]]++;
        }
    }
    f(pos+1,a,posa+1,k-1,cont,collpos,contcol);
    ///configuration conditions for remove key[pos] and its colors from contcol and vector of points
    for(set<int>::iterator it=b.begin();it!=b.end();++it){
        if(collpos[*it]!=-1){
            if(contcol[collpos[*it]]==1){
                cont++;
            }
            contcol[collpos[*it]]--;
        }
    }
    f(pos+1,a,posa,k,cont,collpos,contcol);


}
void ColorSpanningSets(int m,int k,vector<int> Mycolor){
    number=0;
    int all_color[m+1];///position of color in Mycolor set in  all_color and -1 for other color
    fill(all_color,all_color+(m+1),-1);
    int sp_col_size=(int)Mycolor.size();
    ///set up position of my color to all_color
    for(int i=0;i<sp_col_size;i++){
        all_color[Mycolor[i]]=i;
    }
    //cout<<"dd"<<endl;
    ///set up number of my color in contcol in method f
    int contcol[sp_col_size];
    memset(contcol,0,sizeof contcol);
    for(int i=1;i<=k;i++){
        pll a[i];
        //cout<<"dd"<<endl;
        f(0,a,0,i,sp_col_size,all_color,contcol);
    }

}

void print(vector<pll> p){
    for(int i=0;i<p.size();i++){
        cout<<"( "<<p[i].first<<" , "<<p[i].second<<" ) "<<endl;
    }
}
void printpoin(vector<Point> p){
    for(int i=0;i<p.size();i++){
        cout<<"( "<<p[i].x<<" , "<<p[i].y<<" , "<<p[i].color<<" ) "<<endl;
    }
}

//For presenting our approach
void geraphic(vector<Point> a)
{
    //First of all, opening a specific window
    initwindow(500, 500);
    //Moreover, a secondary step is that drawing the basic nodes in the shape of the circles
    for(int k =0; k < 10; k++){
         setcolor(a[k].color);
         setfillstyle(SOLID_FILL, a[k].color);
         circle(10*a[k].x+100, 10*a[k].y+100, 5);
         floodfill(10*a[k].x+100, 10*a[k].y+100, a[k].color);
         setcolor(a[k].color);
    }

    //then finding the min and max of the obtained nodes in the both of x and y axes
    pll m, n, x1, x2;
    n = final_points[0];
    for(int i = 1; i < final_points.size(); i++){
        if(n.second > final_points[i].second)
            n = final_points[i];
    }

    m = final_points[0];
    for(int i = 1; i < final_points.size(); i++){
        if(m.second < final_points[i].second)
            m = final_points[i];
    }

    x1 = final_points[0];
    for(int i = 1; i < final_points.size(); i++){
        if(x1.first < final_points[i].first)
            x1 = final_points[i];
    }

    x2 = final_points[0];
    for(int i = 1; i < final_points.size(); i++){
        if(x2.first > final_points[i].first)
            x2 = final_points[i];
    }

    //Finally, drawing a rectangle
    setcolor(RED);
    line(10*x1.first+5+100,10*n.second-5+100,10*x1.first+5+100,10*m.second+5+100);
    setcolor(RED);
    line(10*x2.first-5+100,10*n.second-5+100,10*x2.first-5+100,10*m.second+5+100);
    setcolor(RED);
    line(10*x1.first+5+100,10*n.second-5+100,10*x2.first-5+100,10*n.second-5+100);
    setcolor(RED);
    line(10*x1.first+5+100,10*m.second+5+100,10*x2.first-5+100,10*m.second+5+100);


    getch();
}

int main()
{
    int number_of_color=10;
    double epsilon=0.2;
    vector<Point> vec_of_point=maketest(5,5,7,10);
    cout<<vec_of_point.size()<<endl;
    //printpoin(vec_of_point);
   // print(vec_of_point);
    double delta=makedelta(vec_of_point,number_of_color);
    cout<<"delta==>"<<delta<<endl;
    map<pll,set<int> > output_of_make_gird;
    grid=task_2(vec_of_point,delta,epsilon);
    for (std::map<pll,set<int> >::iterator it=grid.begin(); it!=grid.end(); ++it)
        key.push_back(it->first);
    //print(key);
    cout<<key.size()<<endl;
    vector<int> Mycolor;
    int x;
    for(int i=0;i<3;i++){
        cin>>x;
        Mycolor.push_back(x);
    }
    ///k number of member of subset
    int k=5;
    ColorSpanningSets(number_of_color,k,Mycolor);
    float a=(epsilon)/3;
    /// a==>the side of square in the grid
    a*=delta;
    float gridSize = a ;
    best_diameter = best_diameter * gridSize * gridSize;
    cout << "diamter ==> " << (best_diameter) << endl;
    for(int i=0; i<final_points.size(); i++){
        cout<<"("<<final_points[i].first<<" , "<<final_points[i].second<<")"<<endl;

    }
    cout << endl;
    geraphic(vec_of_point);
    return 0;
}
