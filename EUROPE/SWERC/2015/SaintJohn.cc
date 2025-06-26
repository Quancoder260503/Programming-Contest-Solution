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

using P = Point<int64_t>;

int sideof(P s, P e, P p) { return sgn(s.cross(e, p)); }


void solve(vector<P> &Pset, vector<P>&p)
{
    sort(Pset.begin(), Pset.end());
    Pset.erase(unique(Pset.begin(), Pset.end()), Pset.end());
    int n = Pset.size();
    // lower - hull
    vector<P> hull, lower, upper;
    for (int i = 0; i < n; i++) {
        while (hull.size() > 1 && hull[hull.size() - 2].cross(hull.back(), Pset[i]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(Pset[i]);
    }
    int lower_hull = hull.size(); 
    lower = hull; 
    for (int i = n - 2; i >= 0; i--) {
        while (hull.size() > lower_hull && hull[hull.size() - 2].cross(hull.back(), Pset[i]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(Pset[i]);
    }
    for(int i = lower_hull - 1; i < hull.size(); i++) upper.push_back(hull[i]); 
    reverse(upper.begin(), upper.end()); 
    int ret = 0; 
    for(int i = 0; i < p.size(); i++) {
        auto uptr = lower_bound(upper.begin(), upper.end(), p[i]);
        auto lptr = lower_bound(lower.begin(), lower.end(), p[i]);
        if(uptr == upper.begin() || uptr == upper.end()) continue; 
        if(lptr == lower.begin() || lptr == lower.end()) continue; 
        int x = sideof(p[i],  *(uptr - 1), *(uptr));
        int y = sideof(p[i],  *(lptr - 1), *(lptr));
        ret += (x == 0 || y == 0 || (x == -1 && y == 1)); 
    }
    cout << ret << '\n'; 
    return;
}

int main(void) {
    int n, m; 
    cin >> n; 
    vector<P>a(n); 
    for(int i = 0; i < n; i++) {
        cin >> a[i].x >> a[i].y; 
    }
    cin >> m; 
    vector<P>b(m); 
    for(int i = 0; i < m; i++) { 
        cin >> b[i].x >> b[i].y; 
    }
    solve(a, b); 
    return 0; 
}