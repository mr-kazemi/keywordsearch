#include<iostream>
#include <vector>
using namespace std;
struct Point
{
    long double x, y;
    int color;
    Point(long double x1 = 0, long double y1 = 0, int color1 = 0)
    {
        x = x1;
        y = y1;
        color = color1;
    }
};
vector <vector<Point>> listforSaving;


void combine(vector<Point> point, int i, int k, int n, int index, vector<Point> data)
	{


		if (index == k)
		{
            vector<Point> g;
			for (int j = 0; j < k; j++)
			{
                            cout <<"("<< data[j].x << ", ";
			    cout << data[j].y << " ,";
				cout << data[j].color << ") ";
                g.push_back(data[j]);

			}
            listforSaving.push_back(g);
			cout << "" << endl;
			return ;
		}
		if (i >= n)
		{
			return;
		}

		data[index].x = point[i].x;
		data[index].y = point[i].y;
		data[index].color = point[i].color;


		combine(point, i + 1, k, n, index + 1, data);
		combine(point, i + 1, k, n, index, data);
	}

vector<vector<Point>> print(vector<Point> point, int k, int n)
{

		vector<Point> data;
		for (int j = 0; j < k; j++)
		{
			data.push_back((0,0,0));
		}
		for (int j = 1; j <= k; j++)
		{
			combine(point, 0, j, n, 0, data);
		}

		return listforSaving;
}


int main(){
        vector<Point> c;
		Point d = Point(0.49, 0.001, 0);
		Point k = Point(2, -5, 0);
		c.push_back(d);
		c.push_back(k);


		int n = c.size();
		print(c, 3, n);
        cout<<listforSaving.size();

return 0;
}
