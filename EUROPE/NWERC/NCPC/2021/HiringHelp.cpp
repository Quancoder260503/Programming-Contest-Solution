#include "bits/stdc++.h"
using namespace std;
#define MAXN (int)1e6 + 10
#define x first
#define y second
typedef pair<double, double> Vec;
typedef long double ldb;
#define mp make_pair
const int mod = 1e9 + 7;
const double eps = 1e-10;
int n, k, q;
using Point = Vec;
Point P[MAXN];
bool vis[MAXN];
int sign(double x)
{
    if (x > eps)
        return 1;
    if (x < -eps)
        return -1;
    return 0;
}
Vec operator-(Vec AB, Vec AC)
{
    return Vec(AB.x - AC.x, AB.y - AC.y);
}
double cross(Vec AB, Vec AC)
{
    return AB.x * AC.y - AB.y * AC.x;
}
double ccw(Vec A, Vec B, Vec C)
{
    Vec X = B - A;
    Vec Y = C - A;
    return sign(cross(X, Y));
}
set<Point> upper;
bool below(Point a, Point b, Point c)
{
    if (b.x == c.x)
    {
        return 0 <= max(b.y, c.y) - a.y;
    }
    double ans = (a.x - c.x) * (a.y - b.y) - (a.x - b.x) * (a.y - c.y);
    return sign(ans) >= 0;
}
bool inside(Point a)
{
    auto it = upper.lower_bound(a);
    if (it == upper.end())
        return 0;
    if (it == upper.begin())
    {
        return a.y <= it->y;
    }
    else
    {
        if (below(a, *(prev(it)), *it))
            return 1;
    }
    return 0;
}
void add(const Point &a)
{
    upper.insert(a);
    auto it = upper.lower_bound(a);
    vector<Point>curr;
    if (it != upper.begin())
    {
        auto lef = prev(it);
        while (lef != upper.begin() && (ccw(*prev(lef), *lef, a) >= 0 || lef -> y <= a.y))
        {
            curr.push_back(*lef);
            lef--;
        }
        if(lef == upper.begin())
        {
            if(lef -> y <= a.y)
            {
                curr.push_back(*lef); 
            }
        }
    }
    if (it != upper.end())
    {
        auto rig = it;
        while(rig != upper.end() && ccw(*rig, *next(rig), a) >= 0)
        {
            curr.push_back(*rig);
            rig++;
        }
    }
    for (int i = 0; i < curr.size(); i++)
    {
        upper.erase(curr[i]);
    }
    upper.insert(a); 
}
vector<Point> query;
signed main(void)
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lf %lf", &P[i].x, &P[i].y);
    }
    scanf("%d", &q);
    for (int i = 0; i < q; i++)
    {
        char type;
        scanf(" %c", &type);
        if (type == 'c')
        {
            double t, l, f;
            scanf("%lf %lf %lf", &t, &l, &f);
            query.push_back(Point(l / t, f / t));
        }
        else
        {
            int pos;
            scanf("%d", &pos);
            vis[pos] = 1;
            query.push_back(Point(-1, pos));
        }
    }
    reverse(query.begin(), query.end());
    for (int i = 1; i <= n; i++)
    {
        if (vis[i])
            continue;
        if(!inside(P[i])) 
        {
            add(P[i]);
        }
    }
    vector<string> verdict;
    for (int i = 0; i < query.size(); i++)
    {
        if (query[i].x == -1)
        {
            int v = query[i].y;
            if (!inside(P[v]))
            {
                add(P[v]); 
            }
        }
        else
        {
            verdict.push_back(inside(query[i]) ? "no" : "yes");
        }
    }
    reverse(verdict.begin(), verdict.end());
    for (int i = 0; i < verdict.size(); i++)
    {
        cout << verdict[i] << '\n';
    }
    return 0;
}