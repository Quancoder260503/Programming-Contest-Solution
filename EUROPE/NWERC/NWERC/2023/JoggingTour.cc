#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

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

using pts = Point<double>; 
using vdb = vector<double>;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    cout << fixed << setprecision(10); 
    int n; 
    cin >> n; 
    vector<pts>p(n); 
    for(int i = 0; i < n; i++) { 
        cin >> p[i].x >> p[i].y; 
    }
    double ret = 1e100; 
    for(int i = 0; i < n; i++) for(int j = i + 1; j < n; j++) {
        double angle = -atan2(p[j].y - p[i].y, p[j].x - p[i].x); 
        double s = sin(angle), c = cos(angle);
        vector<vdb>d(n, vdb(n));
        for(int ni = 0; ni < n; ni++) for(int nj = 0; nj < n; nj++) { 
            double kx = p[nj].x - p[ni].x, ky = p[nj].y - p[ni].y; 
            d[ni][nj] = abs(c * kx - s * ky) + abs(c * ky + s * kx); 
        }
        vector<vdb>dyn(n, vdb(1 << n, 1e100)); 
        for(int ni = 0; ni < n; ni++) dyn[ni][(1 << ni)] = 0; 
        for(int mask = 0; mask < (1 << n); mask++) { 
            for(int ni = 0; ni < n; ni++) if(!(mask & (1 << ni))) { 
                for(int nj = 0; nj < n; nj++) if(mask & (1 << nj)) { 
                    dyn[ni][mask | (1 << ni)] = min(dyn[ni][mask | (1 << ni)], dyn[nj][mask] + d[nj][ni]); 
                }
            }
        }
        for(int ni = 0; ni < n; ni++) ret = min(ret, dyn[ni][(1 << n) - 1]); 
    } 
    cout << ret << '\n'; 
    return 0;  
}
