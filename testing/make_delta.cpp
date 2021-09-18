
using namespace std;

/*include need before run:
  define point structure==>"point.h"
  calculate distance==>"squared_distance.cpp"
  make point for testing==>"make_test.cpp"

*/


///find delta for griding space,
///     input==> 'points' is all point in our test,
///              'n_color' is number of color we have
double makedelta(vector<Point> points,int n_color){


    /// min_dist[i] is the shortest distance of one point from other points with different color,
    ///         this list will fill on every point
    double min_dist[n_color+1];

    double MAX=10000000000.0; /// used in make delta


    /// helping points
    Point P_1;
    Point P_2;
    ///

    ///every time after filling the list "min_dist" ,
    ///  we'll save maximum value between all element of the list in "max_dist_point"
    double max_dist_point;


    double delta=MAX;///save minimum value between different value of "max_dist_point" as "delta"

    for(int i=0;i<(int)points.size();i++){
        fill(min_dist,min_dist+n_color,MAX);

        max_dist_point=-1;

        P_1=points[i];///assign one point for filling "min_dist"

        ///trace all other point for filling "min_dist"
        for(int j=0;j<(int)points.size();j++){
            P_2=points[j];
            if(P_2.color!=P_1.color){/// check for different color
                min_dist[P_2.color]=min(min_dist[P_2.color],squdist(P_1,P_2));
            }
        }

        ///finding value of "max_dist_point"
        for(int j=0;j<n_color;j++){
            if(min_dist[j]!=MAX){
                max_dist_point=max(max_dist_point,min_dist[j]);
            }
        }


        ///calculate value of "delta"
        if(max_dist_point!=-1)
            delta=min(delta,max_dist_point);
    }

    return sqrt(delta);
}

