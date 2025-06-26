#include "bits/stdc++.h"
using namespace std;
#define N 1500000
#define x first
#define y second
#define lint long long
#define ldb long double
typedef pair<lint, lint> Vec;
using Point = Vec;
Point P[N];
const int M = 100;
const lint eps = 1e-9;
int n, k;
Vec operator-(Vec AB, Vec AC)
{
    return Vec(AB.x - AC.x, AB.y - AC.y);
}
lint cross(Vec AB, Vec AC)
{
    return AB.x * AC.y - AB.y * AC.x;
}
lint cross3(Point C, Point B, Point A)
{
    Vec X = B - C;
    Vec Y = A - C;
    return cross(X, Y);
}
signed main(void)
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> P[i].x >> P[i].y;
    }
    lint area = 0;
    for (int i = 1; i + 1 < n; i++)
    {
        area += cross3(P[0], P[i], P[i + 1]);
    }
    lint curarea = 0;
    for (int i = 1; i + 1 < n; i++)
    {
        lint narea = cross3(P[0], P[i], P[i + 1]) + curarea;
        if (narea * 2 >= area)
        {
            ldb slope = (area / 2.0 - curarea) / cross3(P[0], P[i], P[i + 1]);
            cout << fixed << setprecision(10) << P[i].x + slope * (P[i + 1].x - P[i].x) << " " << P[i].y + slope * (P[i + 1].y - P[i].y) << endl;
            return 0;
        }
        curarea = narea;
    }
    return 0;
}