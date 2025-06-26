#include "bits/stdc++.h"
using namespace std;
#define N 1500000
#define x first
#define y second
#define lint long long
typedef pair<long long, long long> Vec;
typedef long double ldb;
const int mod = 1e9 + 7;
int n, k;
using Point = Vec;
vector<Point> lower, upper;
Point P[N];
Vec operator-(Vec AB, Vec AC)
{
    return Vec(AB.x - AC.x, AB.y - AC.y);
}
long long cross(Vec AB, Vec AC)
{
    return (1LL) * AB.x * AC.y - (1LL) * AB.y * AC.x;
}
long long ccw(Point A, Point B, Point C)
{
    Vec X = B - A;
    Vec Y = C - A;
    return cross(X, Y);
}
void ConvexHull(vector<Point> &Pset)
{
    sort(Pset.begin(), Pset.end());
    Pset.erase(unique(Pset.begin(), Pset.end()), Pset.end());
    int n = Pset.size();
    // lower hull
    vector<Point> hull;
    for (int i = 0; i < n; i++)
    {
        while (hull.size() > 1 && ccw(hull[hull.size() - 2], hull.back(), Pset[i]) <= 0)
        {
            hull.pop_back();
        }
        hull.push_back(Pset[i]);
    }
    // upper hull
    int lower_hull = hull.size();
    lower.resize(0);
    lower = hull;
    for (int i = n - 2; i >= 0; i--)
    {
        while (hull.size() > lower_hull && ccw(hull[hull.size() - 2], hull.back(), Pset[i]) <= 0)
        {
            hull.pop_back();
        }
        hull.push_back(Pset[i]);
    }
    upper.resize(0);
    for (int i = lower_hull - 1; i < hull.size(); i++)
    {
        upper.push_back(hull[i]);
    }
    reverse(upper.begin(), upper.end());
    return;
}
lint f[N]; 
signed main(void)
{
     scanf("%d", &n);
     vector<Point>pset;
     pset.push_back(Point(0, 0));
     pset.push_back(Point(n + 1, 0)); 
     for(int i = 1; i <= n; i++)
     {
          scanf("%lld", &f[i]); 
          f[i] = 1LL * f[i] * 100000; 
          pset.push_back(Point(i, f[i])); 
     } 
     ConvexHull(pset); 
     for(int i = 1; i <= n; i++)
     {
         int pos = lower_bound(upper.begin(), upper.end(), Point(i, -1)) - upper.begin(); 
         if(upper[pos].x == i)
         {
            printf("%lld\n", f[i]);
         }
         else 
         {
             double xa = upper[pos].x - upper[pos - 1].x;
             double ya = upper[pos].y - upper[pos - 1].y; 
             double curr = (1.0 * ya * (i - upper[pos].x)) / (1.0 * xa) + 1.0 * upper[pos].y;
             printf("%lld\n", (long long) curr);
         }
     }
}
/*  
   Let P[i] be the optimal solution we can get
   --> P[i] = max(f[i], 0.5 * (P[i + 1], P[i - 1])
   --> P is a concave function 
   --> We need to plot point (i, f[i]) on the plane 
   --> find the upper hull of these point 
*/ 