#include "bits/stdc++.h"

using namespace std;

#define f first
#define s second
#define double long double

template <class T>
int sgn(T x) { return (x > 0) - (x < 0); }
template <class T>
struct Point
{
    typedef Point P;
    T x, y;
    explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
    P operator+(P p) const { return P(x + p.x, y + p.y); }
    P operator-(P p) const { return P(x - p.x, y - p.y); }
    P operator*(T d) const { return P(x * d, y * d); }
    P operator/(T d) const { return P(x / d, y / d); }
    T dot(P p) const { return x * p.x + y * p.y; }
    T cross(P p) const { return x * p.y - y * p.x; }
    T cross(P a, P b) const { return (a - *this).cross(b - *this); }
    T dist2() const { return x * x + y * y; }
    double dist() const { return sqrt((double)dist2()); }
    // angle to x-axis in interval [-pi, pi]
    double angle() const { return atan2(y, x); }
    P unit() const { return *this / dist(); } // makes dist()=1
    P perp() const { return P(-y, x); }       // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const
    {
        return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }
    friend ostream &operator<<(ostream &os, P p)
    {
        return os << "(" << p.x << "," << p.y << ")";
    }
};
template <class P>
int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }
/*
template <class P>
int sideOf(const P &s, const P &e, const P &p)
{
    auto a = (e - s).cross(p - s);
    double l = (e - s).dist();
    return (a > l) - (a < -l);
}
*/
typedef Point<double> P;

template <class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2)
{
    auto d = (e1 - s1).cross(e2 - s2);
    if (d == 0) // if parallel
        return {-(s1.cross(e1, s2) == 0), P(0, 0)};
    auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
    return {1, (s1 * p + e1 * q) / d};
}

const int maxf = 1e6 + 2; 

pair<P, P>line[maxf];

int main(void)
{
    int N; 
    cin >> N; 
    for(int i = 0; i < N; i++) cin >> line[i].f.x >> line[i].f.y >> line[i].s.x >> line[i].s.y; 
    double ret = 0; 
    for(int i = 0; i < N; i++) for(int j = i + 1; j < N; j++) for(int k = j + 1; k < N; k++)
    {
        auto [p1, c1] = lineInter(line[i].f, line[i].s, line[j].f, line[j].s); 
        auto [p2, c2] = lineInter(line[j].f, line[j].s, line[k].f, line[k].s); 
        auto [p3, c3] = lineInter(line[k].f, line[k].s, line[i].f, line[i].s); 
        if(p1 && p2 && p3)
        {
            ret = max(ret, (c1 - c2).dist() + (c2 - c3).dist() + (c3 - c1).dist()); 
        }
    }
    if(ret == 0) {cout << "no triangle" << '\n'; }
    else cout << fixed << setprecision(10) << ret << '\n'; 
    return 0;
}