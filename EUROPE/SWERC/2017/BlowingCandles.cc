#include "bits/stdc++.h"
#include <stdio.h>
#include <algorithm>
using namespace std;
#define N 1500000
#define x first
#define y second
typedef pair<long long, long long> Vec;
typedef long double ldb;
const int mod = 1e9 + 7;
long long finv[N];
long long fac[N];
long long inv[N];
int n, k;
Vec operator-(Vec AB, Vec AC)
{
    return Vec(AB.x - AC.x, AB.y - AC.y);
}
long long cross(Vec AB, Vec AC)
{
    return (1ll) * AB.x * AC.y - (1ll) * AB.y * AC.x;
}
long long cross3(Vec AB, Vec AC, Vec BC)
{
    Vec X = AC - AB;
    Vec Y = BC - AB;
    return cross(X, Y);
}
using Point = Vec;
Point P[N];
vector<Point> ConvexHull(vector<Point> &Pset)
{
    sort(Pset.begin(), Pset.end());
    Pset.erase(unique(Pset.begin(), Pset.end()), Pset.end());
    int n = Pset.size();
    // lower - hull
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
    for (int i = n - 2; i >= 0; i--)
    {
        while (hull.size() > lower_hull && cross3(hull[hull.size() - 2], hull.back(), Pset[i]) <= 0)
        {
            hull.pop_back();
        }
        hull.push_back(Pset[i]);
    }
    hull.pop_back();
    return hull;
}
ldb dist(long long a, long long b, long long c, int x0, int y0)
{
    ldb upper = fabsl((ldb)((1ll) * a * x0 + (1ll) * b * y0 + c));
    ldb lower = (ldb)((1ll) * (a * a) + (1ll) * (b * b));
    return upper * upper / lower;
}
void solve()
{
    scanf("%d %d", &n, &k);
    vector<Point> Pset;
    for (int i = 0; i < n; i++)
    {
        scanf("%lld %lld", &P[i].x, &P[i].y);
        Pset.push_back(P[i]);
    }
    vector<Point> cvhull = ConvexHull(Pset);
    // cout << (int) cvhull.size() << endl;
    // for(int i = 0; i < cvhull.size(); i++){
    //      cout << cvhull[i].x << ' ' << cvhull[i].y << endl;
    // }
    if (cvhull.size() < 3)
    {
        cout << setprecision(15) << (ldb)0 << endl;
        return;
    }
    // point in the convex hull should be sorted by clockwise order
    long long a = -cvhull[0].y + cvhull[1].y;
    long long b = cvhull[0].x - cvhull[1].x;
    long long c = -(1ll) * a * cvhull[0].x - (1ll) * cvhull[0].y * b;
    ldb ans = (ldb)1e17;
    int pos = -1;
    n = cvhull.size();
    int d = 1;
    for (int i = 0; i < n; i++)
    {
        a = -cvhull[i].y + cvhull[(i + 1) % n].y;
        b = cvhull[i].x - cvhull[(i + 1) % n].x;
        c = -(1ll) * a * cvhull[i].x - (1ll) * cvhull[i].y * b;
        int nxtd = (d + 1) % n;
        ldb d0 = dist(a, b, c, cvhull[d].x, cvhull[d].y);
        ldb d1 = dist(a, b, c, cvhull[nxtd].x, cvhull[nxtd].y);
        while (d0 < d1)
        {
            d0 = d1;
            d = nxtd;
            nxtd = (nxtd + 1) % n;
            d1 = dist(a, b, c, cvhull[nxtd].x, cvhull[nxtd].y);
        }

        ans = min(ans, d0);
    }
    ans = (ldb)sqrt(ans);
    cout << setprecision(17) << ans << endl;
    return;
}
signed main(void)
{
    solve();
    return 0;
}