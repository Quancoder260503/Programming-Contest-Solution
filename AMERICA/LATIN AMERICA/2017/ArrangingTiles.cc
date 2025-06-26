#include "bits/stdc++.h"

using namespace std;

#define sz(x) (int) x.size()

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

using pt = Point<double>; 

void reorder_polygon(vector<pt> &P)
{
    size_t pos = 0;
    for (size_t i = 1; i < P.size(); i++)
    {
        if (P[i].y < P[pos].y || (P[i].y == P[pos].y && P[i].x < P[pos].x))
            pos = i;
    }
    rotate(P.begin(), P.begin() + pos, P.end());
}

vector<pt> minkowski(vector<pt> P, vector<pt> Q)
{
    reorder_polygon(P);
    reorder_polygon(Q);
    P.push_back(P[0]);
    P.push_back(P[1]);
    Q.push_back(Q[0]);
    Q.push_back(Q[1]);
    vector<pt> result;
    size_t i = 0, j = 0;
    while (i < P.size() - 2 || j < Q.size() - 2)
    {
        result.push_back(P[i] + Q[j]);
        auto cross = (P[i + 1] - P[i]).cross(Q[j + 1] - Q[j]);
        if (cross >= 0 && i < P.size() - 2)
            ++i;
        if (cross <= 0 && j < Q.size() - 2)
            ++j;
    }
    return result;
}

vector<pt> convexHull(vector<pt> pts)
{
    if (sz(pts) <= 1) return pts;
    sort(pts.begin(), pts.end());
    vector<pt> h(sz(pts) + 1);
    int s = 0, t = 0;
    for (int it = 2; it--; s = --t, reverse(pts.begin(), pts.end()))
        for (pt p : pts)
        {
            while (t >= s + 2 && h[t - 2].cross(h[t - 1], p) <= 0) t--;
            h[t++] = p;
        }
    return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}

pair<int, pt>get_intersection(pt p, pt q, pt r, pt s) { 
    int c = (p.cross(q, r) * p.cross(q, s) <= 0 && r.cross(s, p) * r.cross(s, q) <= 0); 
    if(!c) return {c, pt(0, 0)}; 
    pt a = q - p, b = s - r, cc = pt(p.cross(q), r.cross(s)); 
    return {c, pt(pt(a.x, b.x).cross(cc), pt(a.y, b.y).cross(cc)) / (a.cross(b))}; 
}

double calc(vector<pt>&a, vector<pt>&b) { 
    vector<pt>ca = a, cb = b; 
    for(int i = 0; i < sz(cb); i++) { 
        cb[i].x = -cb[i].x; cb[i].y = -cb[i].y;  
    }
    auto mksum = minkowski(ca, cb); 
    int csz = sz(mksum); 
    for(int i = 0; i < csz; i++) { 
        auto cc = get_intersection(pt(0, 0), pt(1e9, 0), mksum[i], mksum[(i + 1) % csz]); 
        if(cc.first) return cc.second.x; 
    }
    return EXIT_FAILURE; 
}

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
    cout.tie(NULL); 
    int n; 
    cin >> n; 
    vector<vector<double>>w(n, vector<double>(n)); 
    vector<vector<pt>>poly(n);
    vector<double>l(n, 1e100), r(n, -1e100);  
    for(int i = 0, psz; i < n; i++) {
        cin >> psz;
        poly[i].resize(psz);  
        for(int j = 0; j < psz; j++) { 
            cin >> poly[i][j].x >> poly[i][j].y; 
            l[i] = min(l[i], poly[i][j].x);
            r[i] = max(r[i], poly[i][j].x); 
        }
    }
    for(int i = 0; i < n; i++) poly[i] = convexHull(poly[i]); 
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) if(i != j) { 
        w[i][j] = calc(poly[i], poly[j]); 
    }
    vector<vector<double>>dyn(n, vector<double>((1 << n), 1e100)); 
    for(int i = 0; i < n; i++) dyn[i][(1 << i)] = r[i]; 
    for(int mask = 0; mask < (1 << n); mask++) { 
        for(int i = 0; i < n; i++) if(mask & (1 << i)) {
            for(int j = 0; j < n; j++) if(i != j && mask & (1 << j)) { 
                dyn[i][mask] = min(dyn[i][mask], dyn[j][mask xor (1 << i)] + w[i][j]); 
            }
        }
    } 
    double ret = 1e100; 
    for(int i = 0; i < n; i++) { 
        ret = min(ret, dyn[i][(1 << n) - 1] - l[i]); 
    }
    cout << fixed << setprecision(3) << ret << '\n'; 
    return 0;
}