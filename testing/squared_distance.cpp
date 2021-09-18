#include <bits/stdc++.h>

using namespace std;

/*include need before run:
  define point structure==>"point.h"

*/

///square of distance between two points
double squdist(Point a,Point b){
    double dist=(a.x-b.x)*(a.x-b.x);
    dist+=((a.y-b.y)*(a.y-b.y));
    return dist;
}
