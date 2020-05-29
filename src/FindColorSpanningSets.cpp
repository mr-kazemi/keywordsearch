#include <bits/stdc++.h>
//#include<iostream>
//#include <vector>
//#include <set>
//#include "point.h"
using namespace std;
#define pll pair<int,int>




//A recursive method to generate subsets
void combine(int a[],int i, int j, int k, int n, set<int> AbsColors, map<int,int> ColorFreq, map<pll,set<int> > points){
    vector<int> data;
    set<int> SetOfColors;
    map<pll,set<int> >::iterator itr;
    set<int>::iterator itrset;
    if(j == k){
        for(int i = 0; i < k; i++){
            cout<<  a[i] << "," ;
        }
        if(AbsColors.empty())
            cout<< " color-spanning" <<"\n" ;
        else
            cout<< " not color-spanning" <<"\n";
    }
    else{
        if(i <= n){
            if(n-i >= k-j)
                combine(a, i+1, j, k, n, AbsColors, ColorFreq, points);
            //Replace j-th element of currently selected set by i
            itr = points.begin() + a[j]-1;
            for (itrset = (itr->second).begin(); itrset != (itr->second).end(); ++itrset)
                if ( ColorFreq.find(*itrset) != ColorFreq.end() ) {
                    ColorFreq[*itrset]--;
                    if ( ColorFreq[*itrset] == 0)
                        AbsColors.insert( *itrset );
                }
            itr = points.begin() + i-1;
            for (itrset = (itr->second).begin(); itrset != (itr->second).end(); ++itrset)
                if ( ColorFreq.find(*itrset) != ColorFreq.end() ) {
                    ColorFreq[*itrset]++;
                    AbsColors.erase(*itrset);
                }
            
            a[j] = i;  
            j++;
            //End of replacement
            
            combine(a, i+1, j, k, n, AbsColors, ColorFreq, points);
        }
    }
}


//finding color-spanning sets of size k
void ColorSpanningSets( int k, map<pll,set<int> > points, vector<int> colors){
    int n = points.size();
    int m = colors.size();
    int a[n];
    for(int i = 0; i < n; i++)
        a[i] = i+1;
    map<int,int> ColorFreq;   //Maintain the frequency of each color in user specified set
    int AbsentColorsNum = m;
    for(int l = 0; l < m; l++) //Initiate ColorFreq
        ColorFreq[colors[l]] = 0;
    for(int i = k; i > 0; i--)
        combine(a, 1, 0, i, n, AbsColors, ColorFreq, points);   //Recursive set generator
        
}





int main(){

    int m = 10;//the number of all colors
    map<pll,set<int> > c;// just as an example for checking
    c[(1,2)] = {1,4,6};
    c[(3,5)] = {3,7,2};
    c[(1,4)] = {1,5};
    c[(3,6)] = {3,2};
    c[(7,1)] = {5,8,6};
    c[(3,4)] = {5,1,2};
    c[(5,1)] = {4,8};
    
    ColorSpanningSets( 4, c, {1,5,7,8});
    
    
return 0;
}
