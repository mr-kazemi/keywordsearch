#include<iostream>
#include <vector>
#include "point.h"
using namespace std;
vector<vector<int>> listforsaving;

//This is not a recursive method
vector<vector<int>> subsetWithOutDividing(int n, int k){
    int a[n];
    int i, j;
    vector<vector<int>> listForSaving;
    vector<int> data;
    for(i = 0; i < n; i++)
        a[i] = i+1;
    while(i != 0){
        for(i = 0; i < k; i++){
                data.push_back(a[i]);
        }
        listForSaving.push_back(data);
        data.clear();
        i = k;
        while(i > 0 && a[i-1] == n-k+i)
            i -= 1;
        if(i > 0){
            a[i-1] += 1;
            for(j = i; j < n; j++)
                a[j] = a[j-1] + 1;
        }
    }
    return listForSaving;
}

//It is for inserting subsets which are less or equal than k
vector<vector<int>> show(int n, int k){
     vector<vector<int>> listForSaving, swaping;
     for(int l = k; l > 0; l--){
        swaping = subsetWithOutDividing(n, l);
        listForSaving.insert(listForSaving.end(), swaping.begin(), swaping.end());
    }
    return listForSaving;
}

//This is recursive method
void combine(int a[],int i, int j, int k, int n){
    vector<int> data;
    if(j == k){
        for(int i = 0; i < k; i++){
            data.push_back(a[i]);
        }
        listforsaving.push_back(data);
    }
    else{
        if(i <= n){
            if(n-i >= k-j)
                combine(a, i+1, j, k, n);
            j = j+1;
            a[j-1] = i;
            combine(a, i+1, j, k, n);
        }
    }
}
//It is for inserting subsets which are less or equal than k
vector<vector<int>> subsetWithDividing(int n, int k){
    int a[n];
    for(int i = 0; i < n; i++)
        a[i] = i+1;
    for(int i = k; i > 0; i--){
        combine(a, 1, 0, i, n);
    }
    return listforsaving;
}



int main(){


return 0;
}
