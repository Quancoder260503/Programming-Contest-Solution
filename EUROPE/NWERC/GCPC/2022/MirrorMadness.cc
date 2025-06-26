#include "bits/stdc++.h"

using namespace std;

template <class T> 
int sgn(T x) {
    return (x > 0) - (x < 0);
}
template <class T> struct Point {
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
    double dist() const { return sqrt((double) dist2()); }
    // angle to x-axis in interval [-pi, pi]
    double angle() const { return atan2(y, x); }
    P unit() const { return *this / dist(); }   // makes dist()=1
    P perp() const { return P(-y, x); }         // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const { return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a)); }
    friend ostream &operator<<(ostream &os, P p) { return os << "(" << p.x << "," << p.y << ")"; }
};

using P = Point<int>; 

int
sideOf(P s, P e, P p) {
    return sgn(s.cross(e, p));
}

int 
main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<P> pts(n);
    P start; 
    for (int i = 0; i < n; i++) {
        cin >> pts[i].x >> pts[i].y;
    }
    vector<map<int, vector<int>>>g(2);
    for (int i = 0; i < n; i++) {
        for (int x = min(pts[i].x, pts[(i + 1) % n].x); x <= max(pts[i].x, pts[(i + 1) % n].x); x++) {
            for (int y = min(pts[i].y, pts[(i + 1) % n].y); y <= max(pts[i].y, pts[(i + 1) % n].y); y++) {
                g[0][x + y].push_back(x - y);
                g[1][x - y].push_back(x + y);
            }
        }
    }
    for (int i = 0; i < 2; i++) { 
       for(auto &[u, v] : g[i]) sort(v.begin(), v.end()); 
    }
    cin >> start.x >> start.y;
    for (int i = 0; i < m; i++) {
        int sum = start.x + start.y, diff = start.x - start.y; 
        if (i & 1) {
            int pos = lower_bound(g[0][sum].begin(), g[0][sum].end(), diff) - g[0][sum].begin();
            diff = g[0][sum][pos ^ 1];
        } 
        else {
            int pos = lower_bound(g[1][diff].begin(), g[1][diff].end(), sum) - g[1][diff].begin();
            sum = g[1][diff][pos ^ 1];
        }
        start.x = (sum + diff) / 2, start.y = (sum - diff) / 2;
        cout << start.x << " " << start.y << '\n';
    }
    return 0;
} 