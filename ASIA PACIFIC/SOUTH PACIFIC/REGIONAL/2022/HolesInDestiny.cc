#include "bits/stdc++.h"

using namespace std; 

#include "bits/stdc++.h"

using namespace std; 

#define x first
#define y second 
#define int64_t long long
#define double long double


const int64_t L = 500; 
const double eps = 1e-7;

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

P euclid(int64_t A, int64_t B) { 
    if (!B) return P(1, 0);
    P p = euclid(B, A % B);
    return P(p.y, p.x - A / B * p.y);
}

double angle(P a, P b, P c) {
    return acos((c - a).dot(c - b) / ((c - a).dist() * (c - b).dist())); 
}

P func(P a, P b, int64_t s) {
    int64_t pa = a.y - b.y, pb = b.x - a.x, g = gcd(abs(pa), abs(pb));
    int64_t pc = s - (1LL * a.x * b.y - 1LL * a.y * b.x); 
    pa = pa / g;
    pb = pb / g; 
    pc = pc / g; 
    P p = euclid(abs(pa), abs(pb)); 
    if(abs(pb)) {
        p.x = p.x * (pc % abs(pb)) % abs(pb); 
        p.y = (pc - abs(pa) * p.x) / abs(pb); 
    } 
    else {
        p.y = p.y * (pc % abs(pa)) % abs(pa); 
        p.x = (pc - abs(pb) * p.y) / abs(pa); 
    }
    if(pa < 0) p.x = -p.x; 
    if(pb < 0) p.y = -p.y; 
    int64_t sx = (b.x - a.x) / g, sy = (b.y - a.y) / g;
    P middle = P((a.x + b.x) / 2, (a.y + b.y) / 2);
    if(abs(sx) > 0) { 
        int64_t dist = middle.x - p.x; 
        middle = P(p.x + 1LL * (dist > 0 ? 1 : -1) * abs(dist) / sx * sx, p.y + 1LL * (dist > 0 ? 1 : -1) * abs(dist) / sx * sy); 
    }
    else { 
        int64_t dist = middle.y - p.y; 
        middle = P(p.x + 1LL * (dist > 0 ? 1 : -1) * abs(dist) / sy * sx, p.y + 1LL * (dist > 0 ? 1 : -1) * abs(dist) / sy * sy); 
    }
    pair<double, P> ret = {angle(a, b, middle), middle};
    for(int64_t x = middle.x + sx, y = middle.y + sy, iter = 0; iter < L; iter++, x += sx, y += sy) { 
        ret = max(ret, {angle(a, b, P(x, y)), P(x, y)});
    } 
    for(int64_t x = middle.x - sx, y = middle.y - sy, iter = 0; iter < L; iter++, x -= sx, y -= sy) { 
        ret = max(ret, {angle(a, b, P(x, y)), P(x, y)});
    } 
    return ret.second; 
}

int main(void) {
    ios_base::sync_with_stdio(0); 
    cin.tie(0); 
    cout << fixed << setprecision(10); 
    int tc; 
    cin >> tc;
    while(tc--) { 
        P a, b;  
        cin >> a.x >> a.y >> b.x >> b.y; 
        auto ret = func(a, b, -gcd(abs(a.x - b.x), abs(a.y - b.y))); 
        cout << ret.x << " " << ret.y << '\n'; 
    }
    return 0; 
}

/*
   Note the prog4fun site doesnt allow multiple solutions juding, hence 
   the solution is not completely judged. 
*/