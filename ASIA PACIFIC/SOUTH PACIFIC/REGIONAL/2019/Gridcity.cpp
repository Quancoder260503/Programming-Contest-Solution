#include "bits/stdc++.h"
using namespace std;
#define N 1500000
#define x first
#define y second
#define lint long long
typedef pair<lint, lint> Vec;
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
long long cross3(Point A, Point B, Point C)
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
        while (hull.size() > 1 && cross3(hull[hull.size() - 2], hull.back(), Pset[i]) <= 0)
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
        while (hull.size() > lower_hull && cross3(hull[hull.size() - 2], hull.back(), Pset[i]) <= 0)
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
// height + width - gcd(height, width)
lint gcd(lint a, lint b)
{
    if(a == 0) return b; 
    return gcd(b % a, a); 
}
signed main(void)
{
   cin >> n; 
   vector<Point>pset;
   lint hmax = 0, wmax = 0; 
   lint hmin = 1e9, wmin = 1e9;
   for(int i = 1; i <= n; i++)
   {
      cin >> P[i].x >> P[i].y; 
      hmax = max(hmax, P[i].x);
      hmin = min(hmin, P[i].x); 
      wmax = max(wmax, P[i].y);
      wmin = min(wmin, P[i].y); 
      pset.push_back(P[i]); 
   }
   ConvexHull(pset);
   lint ans = 0; 
   for(int i = 0; i + 1 < upper.size(); i++)
   {
      lint width  = abs(upper[i + 1].x - upper[i].x); 
      lint height = abs(upper[i + 1].y - upper[i].y); 
      lint area = 1LL * height * width; 
      lint crss = height + width - gcd(height, width); 
      lint addy = wmax - max(upper[i + 1].y, upper[i].y);
      lint addx = abs(upper[i + 1].x - upper[i].x); 
      ans += crss + (area - crss) / 2 + 1LL * addx * addy; 
   }
   for (int i = 0; i + 1 < lower.size(); i++)
   {
      lint width  = abs(lower[i + 1].x - lower[i].x);
      lint height = abs(lower[i + 1].y - lower[i].y);
      lint area = 1LL * height * width;
      lint addy = min(lower[i + 1].y, lower[i].y) - wmin;
      lint addx = abs(lower[i + 1].x - lower[i].x);
      lint crss = height + width - gcd(height, width);
      ans += crss + (area - crss) / 2 + 1LL * addx * addy;
   }
   ans = 1LL * (hmax - hmin) * (wmax - wmin) - ans; 
   cout << ans << '\n'; 
   return 0; 
}