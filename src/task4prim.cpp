#include <bits/stdc++.h>
#include "point.h"
#define pll pair<long long,long long>
using namespace std;
vector<pll> key;
map<pll,set<int> > grid;
int number;
///position pos in key,vector of chose element,position of element in a,const number member of subset,number of unselected color,position list of my color,array of counting my color
void f(int pos,pll a[],int posa,int k,int cont,int collpos[],int contcol[]){
    if(((int)key.size())-pos+1<k){
        return;
    }
    //cout<<pos<<"\t"<<cont<<endl;
    if(k==0){

        //cout<<number<<endl;
        for(int i=0;i<posa;i++){
            cout<<"("<<a[i].first<<","<<a[i].second<<")"<<" , ";
        }
        cout<<endl;
        if(cont==0){
            number++;
            cout<<"color spanning"<<endl;
        }
        else{
            cout<<"not color spanning"<<endl;
        }
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
    pll a[k];
    //cout<<"dd"<<endl;
    f(0,a,0,k,sp_col_size,all_color,contcol);

}
int main(){

    int m = 12;//the number of all colors
    // just as an example for checking
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
    //grid[pll(7,1)].insert(8);
    grid[pll(7,1)].insert(6);
    grid[pll(3,4)].insert(5);
    grid[pll(3,4)].insert(1);
    grid[pll(3,4)].insert(2);
    grid[pll(5,1)].insert(4);
    grid[pll(5,1)].insert(8);
    /*grid[pll(1,2)] = {1,4,6};
    grid[pll(3,5)] = {3,7,2};
    grid[pll(1,4)] = {1,5};
    grid[pll(3,6)] = {3,2};
    grid[pll(7,1)] = {5,6};
    grid[pll(3,4)] = {5,1,2};
    grid[pll(5,1)] = {4,8};*/
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
    grid[pll(3,6)].insert(10);
    grid[pll(3,6)].insert(1);
    grid[pll(3,6)].insert(2);
    grid[pll(5,9)].insert(4);
    grid[pll(5,9)].insert(9);

    for (std::map<pll,set<int> >::iterator it=grid.begin(); it!=grid.end(); ++it)
        key.push_back(it->first);
    //key.pop_back();
    for(int i=0;i<key.size();i++){
        cout<<key[i].first<<"  "<<key[i].second<<endl;
    }
    int dd[6]={1,5,7,6,11,12};
    vector<int> d(dd,dd+6);
    ColorSpanningSets( m,6,d);
    cout<<"number of color spanning subset => "<<number<<endl;


return 0;
}
