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

template <class P>
int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }

const int maxf = 1e6 + 10; 

P pset[maxf]; 

int main(void)
{
    int N; 
    while(cin >> N)
    {
        for(int i = 0; i < N; i++)
        {
            cin >> pset[i].x >> pset[i].y; 
        }
        int64_t ret = 1LL * N * (N - 1) * (N - 2) / 6; 
        auto edge = [&](int i)
        {
            return pset[(i + 1) % N] - pset[i % N]; 
        }; 
        int ptr = 1; 
        for(int i = 0; i < N; i++)
        {
            while(edge(i).cross(edge(ptr)) >= 0) ptr++; 
            ret -= 1LL * (ptr - i - 1) * (ptr - i - 2) / 2; 
        }
        cout << ret << '\n'; 
    }
    return 0; 
}