#include "bits/stdc++.h"
using namespace std;
const double PI = acos(-1.0);
template <typename T>
struct P
{
    T x, y;
    P() { x = y = T(0); }
    P(T _x, T _y) : x(_x), y(_y) {}

    P operator+(const P &a) const { return P(x + a.x, y + a.y); }
    P operator-(const P &a) const { return P(x - a.x, y - a.y); }
    P operator*(T k) const { return P(x * k, y * k); }
    P<double> operator/(double k) const { return P(x / k, y / k); }
    T operator*(const P &a) const { return x * a.x + y * a.y; } // dot product
    T operator%(const P &a) const { return x * a.y - y * a.x; } // cross product
    double norm() { return x * x + y * y; }
    double len() { return hypot(x, y); }
};
using Point = P<double>;
double distToLine(Point p, Point a, Point b)
{
    Point ap = p - a, ab = b - a;
    double u = (ap * ab) / ab.norm();
    Point c = a + (ab * u);
    return (p - c).len();
}

double distToLineSegment(Point p, Point a, Point b)
{
    Point ap = p - a, ab = b - a;
    double u = (ap * ab) / ab.norm();
    if (u < 0.0)
    {
        Point c = Point(a.x, a.y);
        return (p - a).len();
    }
    if (u > 1.0)
    {
        Point c = Point(b.x, b.y);
        return (p - b).len();
    }
    return distToLine(p, a, b);
}
Point p[4];
Point s, e;
double R, h, w;
signed main(void)
{
    // cin >> n >> m;
    cin >> p[0].x >> p[0].y >> w >> h; 
    cin >> R >> s.x >> s.y >> e.x >> e.y;
    p[1].x = p[0].x + w;
    p[1].y = p[0].y;
    p[2].x = p[0].x + w;
    p[2].y = p[0].y + h;
    p[3].x = p[0].x; 
    p[3].y = p[0].y + h;
    double curr = 0;
    for (int i = 0; i < 4; i++)
    {
        curr = max(curr, distToLineSegment(p[i], s, e));
    }
    cout << (curr <= R ? "Oh no!" : "Safe") << '\n';
    return 0;
}