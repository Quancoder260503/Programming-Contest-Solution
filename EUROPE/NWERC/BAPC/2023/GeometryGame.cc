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

using P = Point<int64_t>; 

int main(void)
{
    vector<P>p(4); 
    for(int i = 0; i < 4; i++) cin >> p[i].x >> p[i].y; 
    int equal = 1; 
    int64_t d = (p[1] - p[0]).dist2(); 
    for(int i = 0; i < 4; i++)
    {
       equal = equal & (d == (p[(i + 1) % 4] - p[i]).dist2()); 
    }
    int para = 0; 
    int right = 1; 
    for(int i = 0; i < 4; i++)
    {
        int64_t ang = (p[(i + 1) % 4] - p[i]).dot(p[(i + 2) % 4] - p[(i + 1) % 4]); 
        right = right & (ang == 0); 
    }
    para += ((p[0] - p[1]).cross(p[2] - p[3]) == 0);
    para += ((p[3] - p[0]).cross(p[2] - p[1]) == 0);
    if(equal)
    {
        if(right)
        {
            cout << "square" << '\n';
            return 0;  
        }
        else 
        {
            cout << "rhombus" << '\n'; 
            return 0; 
        }
    }
    else 
    {
        if(right)
        {
            cout << "rectangle" << '\n'; 
            return 0; 
        }
        else if(para == 2) 
        {
            cout << "parallelogram " << '\n';
            return 0; 
        }
        else if(para == 1) 
        {
            cout << "trapezium" << '\n'; 
            return 0; 
        }
    } 
    int d1 = 0;
    d1 = d1 | ((p[0] - p[1]).dist2() == (p[2] - p[1]).dist2()); 
    d1 = d1 | ((p[1] - p[0]).dist2() == (p[3] - p[0]).dist2()); 
    if((p[0] - p[2]).dot(p[1] - p[3]) == 0 && d1)
    {
        cout << "kite\n";
        return 0; 
    }
    cout << "none" << '\n';
    return 0;
}