#include "bits/stdc++.h"
using namespace std;
#define N (int) 3e5 + 10 
#define x first
#define y second
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
long long cross3(Vec A, Vec B, Vec C)
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
    vector<Point> hull;
    for (int i = 0; i < n; i++)
    {
        while (hull.size() > 1 && cross3(hull[hull.size() - 2], hull.back(), Pset[i]) <= 0)
        {
            hull.pop_back();
        }
        hull.push_back(Pset[i]);
    }
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
bool above(Point a, Point b, Point c)
{
    if (b.x == c.x)
    {
        return a.y >= min(b.y, c.y);
    }
    return 1LL * (a.x - c.x) * (a.y - b.y) - 1LL * (a.x - b.x) * (a.y - c.y) <= 0;
}
bool below(Point a, Point b, Point c)
{
    if (b.x == c.x)
    {
        return a.y <= max(b.y, c.y);
    }
    return 1LL * (a.x - c.x) * (a.y - b.y) - 1LL * (a.x - b.x) * (a.y - c.y) >= 0;
}
signed main(void)
{
    cin >> n;
    vector<Point> pset;
    for (int i = 1; i <= n; i++)
    {
        cin >> P[i].x >> P[i].y;
        pset.push_back(P[i]);
    }
    ConvexHull(pset);
    string ans;
    for (int i = 1; i <= n; i++)
    {
        auto it  = lower_bound(lower.begin(), lower.end(), P[i]);
        auto it2 = lower_bound(upper.begin(), upper.end(), P[i]); 
        if (*it == P[i] || *it2 == P[i])
        {
            ans += "N";
        }
        else 
        {
            ans += "Y"; 
        }
    }
    cout << ans << endl;
    cout << '\n';
    return 0;
}