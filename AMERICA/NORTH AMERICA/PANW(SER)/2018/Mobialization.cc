#include "bits/stdc++.h"
using namespace std;
#define double long double
#define x first
#define y second
typedef pair<double, double> Vec;
Vec operator-(Vec AB, Vec AC)
{
    return Vec(AB.x - AC.x, AB.y - AC.y);
}
double cross(Vec AB, Vec AC)
{
    return AB.x * AC.y - AB.y * AC.x;
}
double ccw(Vec AB, Vec AC, Vec BC)
{
    Vec X = AC - AB;
    Vec Y = BC - AB;
    return cross(X, Y);
}
using Point = Vec;
vector<Point> Convexhull(vector<Point> &Pset)
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
signed main(void)
{
    int N, B; 
    while(cin >> N >> B)
    {
        vector<Point>pset; 
        for(int i = 0; i < N; i++)
        {
            double cost, hea, pot;
            cin >> cost >> hea >> pot; 
            pset.push_back({hea * B / cost, pot * B / cost});  
        }
        auto hull = Convexhull(pset); 
        double ret = 0; 
        for(int i = 0; i < hull.size(); i++)
        {
            ret = max(ret, hull[i].x * hull[i].y); 
            double lx = hull[i].x; 
            double rx = hull[(i + 1) % hull.size()].x;
            double a = hull[(i + 1) % hull.size()].y - hull[i].y;
            double b = hull[(i + 1) % hull.size()].x - hull[i].x;
            if(a != 0)
            {
                double xret = (a * hull[i].x - b * hull[i].y) / (2 * a); 
                if(min(lx, rx) < xret && xret < max(lx, rx))
                {
                    double yret = a / b * (xret - hull[i].x) + hull[i].y; 
                    ret = max(ret, xret * yret);
                }
            }
        }
        cout << fixed << setprecision(7) << ret << '\n'; 
    }
    return 0; 
}