#include "bits/stdc++.h"
using namespace std;
const int N = 5e5 + 10;
#define double long double
typedef pair<int, int> pii;
int n;
int a[N + 1];
const double eps = 1e-9;
struct Vec
{
    double x, y;
    Vec(double _x = 0, double _y = 0) : x(_x), y(_y) {}
    double dot(const Vec &other)
    {
        return x * other.x + y * other.y;
    }
    double cross(const Vec &other)
    {
        return x * other.y - y * other.x;
    }
    double length() const
    {
        return sqrt(x * x + y * y);
    }
};
using Point = Vec;
Vec operator-(const Point &B, const Point &A)
{
    return Vec(B.x - A.x, B.y - A.y);
}
int sign(double x)
{
    if (x > eps)
        return 1;
    if (x < -eps)
        return -1;
    return 0;
}
double cross(Vec AB, Vec AC)
{
    return AB.x * AC.y - AC.x * AB.y;
}
double dot(Vec AB, Vec AC)
{
    return AB.x * AC.x + AB.y * AC.y;
}
bool intersect(Point A, Point B, Point C)
{
    int ABxAC = sign(cross(B - A, C - A));
    if (ABxAC == 0)
    {
        if (ABxAC == 0 && sign(dot(B - A, C - A)) >= 0)
            return true;
    }
    return false;
}
signed main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        Point A, B, C;
        cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y;
        int ABxAC = sign(cross(B - A, C - A));
        if (ABxAC == 0)
        {
            cout << "TOUCH" << endl;
        }
        else if (ABxAC < 0)
        {
            cout << "RIGHT" << endl;
        }
        else
        {
            cout << "LEFT" << endl;
        }
    }
    return 0;
}
