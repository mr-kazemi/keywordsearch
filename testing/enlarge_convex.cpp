
using namespace std;


///finding gravity point of convex hull to enlarge convex hull
pdd gravity_point(){
    double grav_x=0,grav_y=0;///"grav_x" and "grav_y" shows coordinate of gravity point

    ///#calculate coordinate of the point,
    ///             "selected_convex_points" is global <pll> vector that saved points that make convex hull
    for(int i=0;i<int(selected_convex_points.size());i++){
        grav_x+=selected_convex_points[i].first*1.0;
        grav_y+=selected_convex_points[i].second*1.0;
    }
    ///change scale to real scaling
    grav_x*=square_side;
    grav_y*=square_side;
    grav_x/=int(selected_convex_points.size());
    grav_y/=int(selected_convex_points.size());
    ///##

    pdd grav_p=pdd(grav_x,grav_y);
    return grav_p;
}


///find norm of input vector to add to real vector to enlarge it,
///     "vec" is input vector
pdd squar_norm_vec(pdd vec){
    ///calculate and save real size of vector in "size"
    double siz=vec.first*vec.first;
    siz+=vec.second*vec.second;
    siz=sqrt(siz);

    ///# make norm vector and save in "norm_vec"
    pdd norm_vec;
    ///enlarge each vector with multiple norm vector by "square_side*sqrt(2)",
    ///             "square_side*sqrt(2)" is diameter of square with side size "square_side"
    norm_vec.first=vec.first*square_side*sqrt(2);
    norm_vec.second=vec.second*square_side*sqrt(2);
    norm_vec.first/=siz;
    norm_vec.second/=siz;

    ///##
    return norm_vec;
}


/// function for enlarge convex hull that saved in "selected_convex_points",
///                     "selected_convex_points" is global <pll> vector that saved points that make convex hull,
///                     output of function is "enlarge_points" , this vector is global <pdd> vector that saved points that show enlarge convex
void enlarge_convex(){

    enlarge_points.clear();/// points that show enlarge convex

    pdd grav_p=gravity_point();///gravity point

    pdd vec;
    double x,y;

    ///calculate enlarge convex points
    for(int i=0;i<int(selected_convex_points.size());i++){
        ///#change scale of each point to real by multiplied by "square_side"
        x=(selected_convex_points[i].first*1.0);
        x*=square_side;
        y=(selected_convex_points[i].second*1.0);
        y*=square_side;
        ///##

        ///find vector of each point from gravity point
        vec.first=x-grav_p.first;
        vec.second=y-grav_p.second;

        ///calculate norm of vector with enlarge it
        vec=squar_norm_vec(vec);

        /// add enlarged norm vector
        x+=vec.first;
        y+=vec.second;

        ///save new position of points
        enlarge_points.push_back(pdd(x,y));
    }

}

