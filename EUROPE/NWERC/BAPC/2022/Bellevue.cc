#include "bits/stdc++.h"

using namespace std;

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

typedef Point<int64_t> P;

#define sz(x) x.size()

vector<P> convexHull(vector<P> pts)
{
    if (sz(pts) <= 1) return pts;
    sort(pts.begin(), pts.end());
    vector<P> h(sz(pts) + 1);
    int s = 0, t = 0;
    for (int it = 2; it--; s = --t, reverse(pts.begin(), pts.end()))
        for (P p : pts)
        {
            while (t >= s + 2 && h[t - 2].cross(h[t - 1], p) <= 0) t--;
            h[t++] = p;
        }
    return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}

int main(void)
{
    int N; 
    cin >> N;
    vector<P>pts(N);
    for(int i = 0; i < N; i++) cin >> pts[i].x >> pts[i].y; 
    auto cv = convexHull(pts); 
    double ret = 0; 
    sort(cv.begin(), cv.end()); 
    for(int i = 0; i < cv.size(); i++)
    {
        double dx = abs(cv[i + 1].x - cv[i].x); 
        double dy = abs(cv[i + 1].y - cv[i].y);
        ret = max(ret, atan2(dy, dx) * 180 / acos(-1)); 
    }
    cout << fixed << setprecision(10) << ret << '\n'; 
    return 0; 
}