#include "bits/stdc++.h"

using namespace std;

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

using P = Point<int64_t>;

template <class P>
bool onSegment(P s, P e, P p)
{
    return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

template <class P>
int segInter(P a, P b, P c, P d)
{
    auto oa = c.cross(d, a), ob = c.cross(d, b),
         oc = a.cross(b, c), od = a.cross(b, d);
    // Checks if intersection is single non-endpoint point.
    if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0)
        return 1;
    set<P> s;
    if (onSegment(c, d, a))
        s.insert(a);
    if (onSegment(c, d, b))
        s.insert(b);
    if (onSegment(a, b, c))
        s.insert(c);
    if (onSegment(a, b, d))
        s.insert(d);
    return s.size() > 0;
}


int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL); 
    int N;
    while (cin >> N)
    {
        vector<pair<P, P>>lines(N); 
        for(int i = 0; i < N; i++) cin >> lines[i].first.x >> lines[i].first.y >> lines[i].second.x >> lines[i].second.y; 
        set<P>V;
        vector<int>fa(N); 
        iota(fa.begin(), fa.end(), 0);
        function<int(int)>find = [&](int u) -> int
        {
            return (fa[u] == u ? u : fa[u] = find(fa[u]));
        }; 
        int ctr = 0; 
        for(int i = 0; i < N; i++) for(int j = i + 1; j < N; j++)
        {
            int chk = segInter(lines[i].first, lines[i].second, lines[j].first, lines[j].second); 
            if(chk)
            {
                ctr++; 
                if(find(i) == find(j)) continue; 
                fa[find(i)] = find(j); 
            }
        }
        int ret = 0; 
        for(int i = 0; i < N; i++) ret += (fa[i] == i); 
        cout << ret - N + ctr << '\n'; 
    }
    return 0;
}