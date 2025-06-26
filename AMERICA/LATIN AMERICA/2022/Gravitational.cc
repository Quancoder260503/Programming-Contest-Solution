#include "bits/stdc++.h"

using namespace std;

#define sz(x) (int)x.size()

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

using pt = Point<int64_t>;

int sideof(pt s, pt e, pt p) { return sgn(s.cross(e, p)); }

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

void solve(vector<pt> &Pset, vector<pt>&p, vector<int>&ret)
{
    sort(Pset.begin(), Pset.end());
    Pset.erase(unique(Pset.begin(), Pset.end()), Pset.end());
    int n = Pset.size(); 
    vector<pt> hull, lower, upper;
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
    for(int i = 0; i < p.size(); i++) { 
        auto uptr = lower_bound(upper.begin(), upper.end(), p[i]);
        auto lptr = lower_bound(lower.begin(), lower.end(), p[i]);
        ret[i] |= (p[i] == (*lptr)) || (p[i] == (*prev(uptr)));
        if(uptr == upper.begin() || uptr == upper.end()) { continue; }
        if(lptr == lower.begin() || lptr == lower.end()) { continue; }
        int x = sideof(p[i],  *(uptr - 1), *(uptr));
        int y = sideof(p[i],  *(lptr - 1), *(lptr));
        int res = (x == 0 || y == 0 || (x == -1 && y == 1)); 
        ret[i] |= res; 
    }
    return;
}

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL); 
    int m1, m2, q; 
    cin >> m1; 
    vector<pt>ptsa(m1), ptsc(m1), ptse(m1); 
    for(int i = 0; i < m1; i++) {
        cin >> ptsa[i].x >> ptsa[i].y; 
    }
    //reverse(ptsa.begin(), ptsa.end()); 
    for(int i = 0; i < m1; i++) { 
        ptsc[i] = ptsa[i] * 2; 
        ptse[i] = ptsa[i] * (-1); 
    }
    cin >> m2;
    vector<pt>ptsb(m2), ptsd(m2), ptsf(m2);
    for (int i = 0; i < m2; i++) {
        cin >> ptsb[i].x >> ptsb[i].y;
    }
    //reverse(ptsb.begin(), ptsb.end()); 
    for (int i = 0; i < m2; i++) { 
        ptsd[i] = ptsb[i] * (-1);
        ptsf[i] = ptsb[i] * 2;
    } 
    auto ptsm  = minkowski(ptsa, ptsb); 
    auto ptsm1 = minkowski(ptsc, ptsd); 
    auto ptsm2 = minkowski(ptse, ptsf); 
    cin >> q; 
    vector<pt>query(q), query2(q);
    vector<int>ret(q, false); 
    for(int i = 0; i < q; i++) { 
        cin >> query[i].x >> query[i].y; 
        query2[i] = query[i] * 2; 
    }
    solve(ptsm, query2, ret); 
    solve(ptsm1, query, ret);
    solve(ptsm2, query, ret);
    for(int i = 0; i < ret.size(); i++) cout << (ret[i] ? 'Y' : 'N');
    return 0; 
}