#include "bits/stdc++.h"

using namespace std;

#define ll long long 

template <class T>
int sgn(T x) {
  return (x > 0) - (x < 0);
}

const double eps = 1e-6; 

template <class T>
struct Point {
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
  P unit() const { return *this / dist(); }  // makes dist()=1
  P perp() const { return P(-y, x); }        // rotates +90 degrees
  P normal() const { return perp().unit(); }


  friend ostream &operator<<(ostream &os, P p) {
    return os << "(" << p.x << "," << p.y << ")";
  }
};

using P = Point<double>;

int sideof(P s, P e, P p) { return sgn(s.cross(e, p)); }

template <class P>
bool onSegment(P s, P e, P p) {
  return fabsl(p.cross(s, e)) < eps && (s - p).dot(e - p) <= 0; 
}


template<class P>
pair<P, bool> circleLine(P c, double r, P a, P b) {
 P ab = b - a, p = a + ab * (c-a).dot(ab) / ab.dist2();
 double s = a.cross(b, c), h2 = r*r - s*s / ab.dist2();
 if (h2 == 0) return {p, true};
 P h = ab.unit() * sqrt(h2);
 return {p + h, true}; 
}

int main(void) { 
 int n; 
 double R; 
 cin >> n >> R; 
 vector<P>pts(n + 1); 
 cout << fixed << setprecision(7);  
 double ans = 0.; 
 for(int i = 1; i <= n; i++) cin >> pts[i].x >> pts[i].y; 
 P centre(0, 0); 
 int move = false; 
 for(int i = 1; i <= n; i++) { 
  if((centre - pts[i]).dist() <= R) { 
    continue;   
  }
  auto cc = circleLine(centre, R, pts[i - 1], pts[i]);
  if(cc.second) {  
   double d = (pts[i] - cc.first).dist(); 
   ans += d; 
   double t = d / (pts[i] - pts[i - 1]).dist(); 
   centre = centre + (pts[i] - pts[i - 1]) * t; 
//  cout << (centre - pts[i]).dist() << '\n'; 
  } 
 }
 cout << ans << '\n'; 
 return 0; 
}