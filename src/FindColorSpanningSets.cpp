#include <bits/stdc++.h>
#include<iostream>
#include <vector>
#include <set>
#include <map>
//#include "point.h"
using namespace std;
#define pll pair<int,int>




//A recursive method to generate subsets
void combine(int a[], int i, int j, int k, int n, set<int> AbsColors, map<int,int> &ColorFreq, vector<pll> pcoords, vector<set<int>> pcolors ){
    vector<int> data;
    set<int> SetOfColors;
    map<pll,set<int> >::iterator itr;
    set<int>::iterator itrset;

    //for (itrset = AbsColors.begin(); itrset != AbsColors.end(); ++itrset)
                //cout<<"  abs_curr = " << *itrset;
    if(j == k){/*
        for(int i = 0; i < k; i++){
            cout<<"("<<pcoords[a[i]-1].first<<","<<pcoords[a[i]-1].second<<")"<<" , ";
            //cout<<  a[i] << "," ;
        }
        if(AbsColors.empty())
            cout<< " color-spanning" <<"\n" ;
        else
            cout<< " not color-spanning" <<"\n";
*/
    }
    else{
        if(i <= n){
            if(n-i >= k-j)
                combine(a, i+1, j, k, n, AbsColors, ColorFreq, pcoords, pcolors);
            //Replace j-th element of currently selected set by i
            if (a[j]){
                //itr = next(points.begin() , a[j]-1);
               // cout<<"  aj = "<< a[j]  ;
                //SetOfColors = itr->second;
                for (itrset = pcolors[a[j]-1].begin(); itrset != pcolors[a[j]-1].end(); ++itrset)
                    //cout<<"  color = "<< *itrset  ;
                    if ( ColorFreq.find(*itrset) != ColorFreq.end() ) {
                        //cout<< "bef_del: " << *itrset <<" freq: "<< ColorFreq[*itrset] <<" , ";
                        ColorFreq[*itrset]--;
                        //cout<< "aft_del: " << *itrset <<" freq: "<< ColorFreq[*itrset] <<" , ";
                        if ( ColorFreq[*itrset] == 0)
                            AbsColors.insert( *itrset );
                    }
            }
            //itr = next(points.begin() , i-1);
            //cout<<"("<<pcoords[i-1].first<<","<<pcoords[i-1].second<<")"<<" , ";
            //SetOfColors = (itr->second);
            for (itrset = pcolors[i-1].begin(); itrset != pcolors[i-1].end(); ++itrset)
                //cout<<"  color = " << *itrset ;
                if ( ColorFreq.find(*itrset) != ColorFreq.end() ) {
                    ColorFreq[*itrset]++;
                    //cout<< "add: " << *itrset <<" freq: "<< ColorFreq[*itrset] <<" , ";
                    AbsColors.erase(*itrset);
                }
            //for (itrset = AbsColors.begin(); itrset != AbsColors.end(); ++itrset)
                //cout<<"  abs_curr = " << *itrset;

            a[j] = i;
            j++;
            //End of replacement

            combine(a, i+1, j, k, n, AbsColors, ColorFreq, pcoords, pcolors);
        }
    }
}


//finding color-spanning sets of size k
void ColorSpanningSets( int k, map<pll,set<int> > points, vector<int> colors){
    int n = points.size();
    int m = colors.size();
    int a[n] = {0};     //Maintain subsets
    vector<set<int>> PointsColors;
    vector<pll> PonitsCoords;
    set<int> AbsColors;
    for (int x : colors)
        AbsColors.insert(x);

    //copy( AbsColors.begin(), AbsColors.end(),  back_inserter(colors));
    //set<int>::iterator itrset;
    //for (itrset = AbsColors.begin(); itrset != AbsColors.end(); ++itrset)
                //cout<<"  abs_curr = " << *itrset;

    map<int,int> ColorFreq;          //Maintain the frequency of each color in specified set
    for(int l = 0; l < m; l++)       //Initialize ColorFreq
        ColorFreq[colors[l]] = 0;
    for (std::map<pll,set<int> >::iterator it=points.begin(); it!=points.end(); ++it){
        PointsColors.push_back(it->second);
        PonitsCoords.push_back(it->first);
    }
/*
    for(int i = k; i > 0; i--){
        for(int j = 0; j < n; j++)
            a[j] = j+1;
        for(int j = 0; j < i; j++)
            b[k]=0;
        map<int,int> ColorFreq;          //Maintain the frequency of each color in specified set
        for(int l = 0; l < m; l++)       //Initialize ColorFreq
            ColorFreq[colors[l]] = 0;
*/int i = k;
        combine(a, 1, 0, i, n, AbsColors, ColorFreq, PonitsCoords, PointsColors);   //Recursive set generator
//    }
}





int main(){


    map<pll,set<int> > grid;// just as an example for checking
    grid[pll(1,2)] = {1,4,6};
    grid[pll(3,5)] = {3,7,2};
    grid[pll(1,4)] = {1,5};
    grid[pll(3,6)] = {3,2};
    grid[pll(7,1)] = {5,6};
    grid[pll(3,4)] = {5,1,2};
    grid[pll(5,1)] = {4,8};
    grid[pll(11,2)] = {4,9,3};
    grid[pll(12,5)] = {11,4,8};
    grid[pll(10,3)] = {2,7,6};
    grid[pll(1,2)].insert(1);
    grid[pll(1,2)].insert(4);
    grid[pll(1,2)].insert(6);
    grid[pll(3,5)].insert(3);
    grid[pll(3,5)].insert(7);
    grid[pll(3,5)].insert(2);
    grid[pll(1,4)].insert(1);
    grid[pll(1,4)].insert(5);
    grid[pll(3,6)].insert(3);
    grid[pll(3,6)].insert(2);
    grid[pll(7,1)].insert(5);
    grid[pll(7,1)].insert(8);
    grid[pll(7,1)].insert(6);
    grid[pll(2,8)].insert(5);
    grid[pll(2,8)].insert(12);
    grid[pll(3,8)].insert(2);
    grid[pll(5,10)].insert(4);
    grid[pll(5,10)].insert(10);
    grid[pll(7,8)].insert(11);
    grid[pll(7,8)].insert(6);
    grid[pll(1,6)].insert(10);
    grid[pll(1,6)].insert(1);
    grid[pll(1,6)].insert(2);
    grid[pll(5,9)].insert(4);
    grid[pll(5,9)].insert(9);

    ColorSpanningSets( 8, grid, {1,5,7,6,11,12});


return 0;
}
