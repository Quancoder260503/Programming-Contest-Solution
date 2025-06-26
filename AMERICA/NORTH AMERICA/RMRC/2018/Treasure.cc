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
template <class P>
int sideOf(P s, P e, P p) { return sgn(s.cross(e, p)); }

using P = Point<int64_t>; 

template<class P> bool onSegment(P s, P e, P p) {
	return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

bool segInter(P a, P b, P c, P d) {
	auto oa = c.cross(d, a), ob = c.cross(d, b), oc = a.cross(b, c), od = a.cross(b, d);
	if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0) return true; 
	return (onSegment(c, d, a) || onSegment(c, d, b) || onSegment(a, b, c) || onSegment(a, b, d)); 
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    cout.tie(0);
    int w, p; 
    P treasure; 
    cin >> w >> p >> treasure.x >> treasure.y;
    vector<array<P, 2>>walls(w), people(p); 
    for(int i = 0; i < w; i++) { 
        for(int j = 0; j < 2; j++) { 
            cin >> walls[i][j].x >> walls[i][j].y; 
        }
    } 
    for(int i = 0; i < p; i++) { 
        for(int j = 0; j < 2; j++) { 
            cin >> people[i][j].x >> people[i][j].y;
        }
    }
    auto check_visible = [&](int idx) {
        P centre = people[idx][0], to = people[idx][1]; 
        if((centre - to).dist2() < (centre - treasure).dist2()) return false;
        if((treasure - centre).dot(to - centre) < 0) return false; 
        for(auto [X, Y] : walls) { 
            if(segInter(treasure, centre, X, Y)) return false; 
        }
        for(auto x : people) { 
            if(!(x[0] == centre) && x[0].cross(centre, treasure) == 0) { 
                if((centre - x[0]).dist2() < (centre - treasure).dist2() && (x[0] - treasure).dist2() < (centre - treasure).dist2()) { 
                    return false; 
                }
            }
        }
        return true; 
    }; 
    for(int i = 0; i < p; i++) { 
        cout << (check_visible(i) ? "" : "not ") << "visible\n"; 
    }
    return 0;
}