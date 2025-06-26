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
    T dist2() const { return 1LL * x * x + 1LL * y * y; }
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

template <class P>
int sideOf(const P &s, const P &e, const P &p)
{
    auto a = (e - s).cross(p - s);
    double l = (e - s).dist();
    return (a > l) - (a < -l);
}
typedef Point<int64_t> P;

template <class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2, int64_t &den)
{
    auto d = (e1 - s1).cross(e2 - s2);
    den = d;
    if (d == 0)
        return {-(s1.cross(e1, s2) == 0), P(0, 0)};
    auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
    return {1, s1 * p + e1 * q};
}

vector<int64_t> dist;
vector<P> point;

int calc(P a, int64_t den)
{
    dist.clear();
    for (int i = 0; i < point.size(); i++)
    {
        dist.push_back((a - point[i] * den).dist2());
    }
    sort(dist.begin(), dist.end());
    dist.erase(unique(dist.begin(), dist.end()), dist.end());
    return (int)dist.size();
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int N;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        P curr;
        cin >> curr.x >> curr.y;
        curr = curr * 2;
        point.push_back(curr);
    }
    int ret = N;
    for (int a = 0; a < point.size(); a++)
    {
        for (int b = 0; b < point.size(); b++)
        {
            ret = min(ret, calc(point[a] + point[b], 2));
            for (int c = 0; c < point.size(); c++)
            {
                for (int d = 0; d < point.size(); d++)
                {
                    P s1 = (point[a] + point[b]) / 2;
                    P s2 = (point[c] + point[d]) / 2;
                    P e1 = (point[a] - point[b]) / 2;
                    swap(e1.x, e1.y);
                    e1.x = -e1.x;
                    P e2 = (point[c] - point[d]) / 2;
                    swap(e2.x, e2.y);
                    e2.x = -e2.x;
                    int64_t den;
                    auto [p, center] = lineInter(s1, s1 + e1, s2, s2 + e2, den);
                    if (p && den != 0)
                    {
                        ret = min(ret, calc(center, den));
                    }
                }
            }
        }
    }
    cout << ret << '\n';
    return 0;
}