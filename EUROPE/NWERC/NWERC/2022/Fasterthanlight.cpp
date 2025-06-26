#include "bits/stdc++.h"
using namespace std;
#define N 1500000
#define x first
#define y second
#define lint long long
typedef pair<long long, long long> Vec;
#define mp make_pair
typedef long double ldb;
using Point = Vec;
Point P[N];
int n, k;
Vec operator - (Point A, Point B)
{
    return Vec(A.x - B.x, A.y - B.y);
}
long long cross(Vec AB, Vec AC)
{
    return (1LL) * AB.x * AC.y - (1LL) * AB.y * AC.x;
}
long long ccw(Vec A, Vec B, Vec C)
{
    Vec X = B - A;
    Vec Y = C - A;
    return cross(X, Y);
}
vector<Point> ConvexHull(vector<Point> &Pset)
{
    sort(Pset.begin(), Pset.end());
    Pset.erase(unique(Pset.begin(), Pset.end()), Pset.end());
    int n = Pset.size();
    vector<Point> hull;
    for (int i = 0; i < n; i++)
    {
        while (hull.size() > 1 && ccw(hull[hull.size() - 2], hull.back(), Pset[i]) <= 0)
        {
            hull.pop_back();
        }
        hull.push_back(Pset[i]);
    }
    int lower_hull = hull.size();
    for (int i = n - 2; i >= 0; i--)
    {
        while (hull.size() > lower_hull && ccw(hull[hull.size() - 2], hull.back(), Pset[i]) <= 0)
        {
            hull.pop_back();
        }
        hull.push_back(Pset[i]);
    }
    hull.pop_back();
    return hull;
}
bool rotation(vector<Point>&a, vector<Point>&b)
{
   vector<Point>red = ConvexHull(a);
   vector<Point>blue = ConvexHull(b); 
   int n = red.size();
   int m = blue.size();
   int curr = 0;  
   int t = 0;
   for(int i = 0; i < m; i++)
   {
        if( cross(red[(t + 1) % n] - red[t], blue[i]) > cross(red[(t + 1) % n] - red[t], blue[curr]))
        {
             curr = i;
        }
   }     
   for(int i = 0; i < n; i++)
   {
      while(cross(red[(i + 1) % n] - red[i], blue[(curr + 1) % m]) > cross(red[(i + 1) % n] - red[i], blue[curr])) curr = (curr + 1) % m;
      if (cross(red[(i + 1) % n] - red[i], blue[curr]) <= cross(red[(i + 1) % n], red[i])) return true;
    } 
    curr = 0;
    for (int i = 0; i < n; i++)
    {
      if (cross(blue[(t + 1) % m] - blue[t], red[i]) > cross(blue[(t + 1) % m] - blue[t], red[curr]))
      {
             curr = i;
      }
    }
    for (int i = 0; i < m; i++)
    {
      while (cross(blue[(i + 1) % m] - blue[i], red[(curr + 1) % n]) > cross(blue[(i + 1) % m] - blue[i], red[curr])) curr = (curr + 1) % n;
      if (cross(blue[(i + 1) % m] - blue[i], red[curr]) <= cross(blue[(i + 1) % m], blue[i])) return true;
    }
    return 0;
}
struct rectangle
{
    lint xa, ya, xb, yb;
};
rectangle rec[N];
signed main(void)
{
    scanf("%d", &n);
    if(n <= 2)
    {
         puts("possible");
         return 0;
    }
    vector<Point>group[4]; 
    for(int i = 0; i < n; i++)
    { 
        scanf("%d %d %d %d", &rec[i].xa, &rec[i].ya, &rec[i].xb, &rec[i].yb); 
        group[0].push_back(mp(rec[i].xa, rec[i].ya));
        group[1].push_back(mp(rec[i].xb, rec[i].ya));
        group[2].push_back(mp(rec[i].xb, rec[i].yb));
        group[3].push_back(mp(rec[i].xa, rec[i].yb));   
    }
    bool ans = rotation(group[0], group[2]) | rotation(group[1], group[3]);
    if(ans)
    {
        puts("possible");
    }
    else 
    {
        puts("impossible"); 
    }
    return 0; 
}