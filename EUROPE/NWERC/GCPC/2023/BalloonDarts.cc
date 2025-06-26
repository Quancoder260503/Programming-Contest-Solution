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
    T cross(P p) const { return 1LL * x * p.y - 1LL * y * p.x; }
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

int f(vector<P>pset, int K)
{
    if(sz(pset) <= K) return true; 
    if(K == 0) return (pset.size() == 0); 
    for(int i = 0; i < K + 1; i++) for(int j = i + 1; j < K + 1; j++)
    {
        vector<P>s;
        for(int k = 0; k < pset.size(); k++) if(pset[i].cross(pset[j], pset[k]) != 0)
        {
            //cout << pset[i] << " " << pset[j] << " " << pset[k] << '\n'; 
            s.push_back(pset[k]); 
        }
        if(f(s, K - 1)) return true;
    }
    return false; 
}

int main(void)
{
    int N; 
    cin >> N; 
    vector<P>pset(N); 
    for(int i = 0; i < N; i++) cin >> pset[i].x >> pset[i].y; 
    cout << (f(pset, 3) ? "" : "im") << "possible" << '\n'; 
    return 0; 
}