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

using P = Point<double>;

const int N = 2600;

double Comb[N][N]; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int n, k; 
    cin >> n >> k;
    cout << fixed << setprecision(10); 
    Comb[0][0] = 1;
    for(int i = 1; i <  N; i++)
    for(int j = 0; j <= i; j++) { 
        Comb[i][j] = Comb[i - 1][j] + (j ? Comb[i - 1][j - 1] : 0); 
    }
    vector<P>pts(n); 
    for(int i = 0; i < n; i++) { 
        cin >> pts[i].x >> pts[i].y; 
    }
    double ret = 0; 
    for(int i = 0; i < n; i++) { 
        int left_pts = n - 2, right_pts = 0; 
        for(int j = i + 1; j < n; j++) { 
            ret +=  pts[j].cross(pts[i]) * Comb[left_pts-- ][k - 2] / 2.0;
            ret +=  pts[i].cross(pts[j]) * Comb[right_pts++][k - 2] / 2.0; 
        }
    }
    ret = ret / Comb[n][k];
    cout << ret << '\n';  
    return 0;
}

/*
  Note: this is a correct solution but can not dealt with precision
*/ 