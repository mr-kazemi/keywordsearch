#include<iostream>
#include <vector>
#include "point.h"
using namespace std;


//I can say, n is a length of the points and m is the number of the colors.
vector<vector<int>> subsetWithOutDividing(vector<Point> points, int n, int m, int k, vector<int> theSetOfTheColors){
    int a[n];
    int i, j, checkPoint = 0;
    int b[m] = {0};//Saving the frequent of each color which are in the specific set
    bool color[m] = {false};//For saving the colors which user gives us
    for(int l = 0; l < theSetOfTheColors.size(); l++)
        color[theSetOfTheColors[l]] = true;
    int counter = 0;//Counter consists of datas that exist in it
    vector<vector<int>> listForSaving;//Just a list for saving all the sets
    vector<int> data;//Just a list for saving a specific set
    for(i = 0; i < n; i++)//This array Addresses the points
        a[i] = i+1;
    for(int l = 0; l < k; l++){
        b[points[a[l]-1].color] = b[points[a[l]-1].color]+1;
        if(color[points[a[l]-1].color] == true)
            counter++;
    }
    while(i != 0){
        for(i = 0; i < k; i++){
            data.push_back(a[i]);
        }
        if(counter == theSetOfTheColors.size()){
            listForSaving.push_back(data);
            for(int l = 0; l < data.size(); l++)//Just for showing available sets
                cout<<data[l]<<",";
            cout<<"\\\\\\\\\\\\\\"<<"\n";
        }
        data.clear();
        i = k;
        while(i > 0 && a[i-1] == n-k+i)
            i -= 1;
        if(i > 0){

            checkPoint = i-1;//Because of changing set from this point
            for(int l = checkPoint; l < k; l++){//Changing a set from this point
                if(b[points[a[l]-1].color] == 1 && color[points[a[l]-1].color] == true){
                    counter--;
                }
                b[points[a[l]-1].color] -= 1;
            }

            a[i-1] += 1;
            for(j = i; j < n; j++){

                    a[j] = a[j-1] + 1;
            }

            for(int l = checkPoint; l < k; l++){
                if(b[points[a[l]-1].color] == 0 && color[points[a[l]-1].color] == true){
                    counter++;
                }
                b[points[a[l]-1].color] += 1;
            }
        }
    }
    return listForSaving;


}

//This is a method that inserts the subsets which are less or equal than k
vector<vector<int>> show(vector<Point> points, int m, int k, vector<int> theSetOfTheColors){
    int n = points.size();
    vector<vector<int>> listForSaving, swaping;
    for(int l = k; l > 0; l--){
        swaping = subsetWithOutDividing(points, n, m, l, theSetOfTheColors);
        listForSaving.insert(listForSaving.end(), swaping.begin(), swaping.end());
    }
    return listForSaving;
}


int main(){

    int m = 10;//the number of all colors
    vector<Point> c;// just as an example for checking
    Point d = Point(0.49, 0.001, 1);
    Point k = Point(2, -5, 2);
    Point l = Point(2, -5, 3);
    Point f = Point(2, -5, 4);
    Point n = Point(2, -5, 5);
    c.push_back(d);
    c.push_back(k);
    c.push_back(l);
    c.push_back(Point(2, -5, 1));
    c.push_back(Point(2, -5, 2));
    c.push_back(f);
    c.push_back(n);
    vector<int> theNumberOfColors;
    theNumberOfColors.push_back(1);
    theNumberOfColors.push_back(2);
    theNumberOfColors.push_back(5);
    vector<vector<int>> h;
    h = show(c, m, 4, theNumberOfColors);
    return 0;


return 0;
}
