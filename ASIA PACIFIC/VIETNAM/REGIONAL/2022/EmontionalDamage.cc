#include "bits/stdc++.h"

using namespace std;

#define double long double 

template <class T>
int sgn(T x) {
  return (x > 0) - (x < 0);
}
template <class T>
struct Point {
  typedef Point P;
  T x, y;
  explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
  bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
  bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
  bool operator!=(P p) const { return x != p.x | y != p.y; }
  P operator+(P p) const { return P(x + p.x, y + p.y); }
  P operator-(P p) const { return P(x - p.x, y - p.y); }
  P operator*(T d) const { return P(x * d, y * d); }
  P operator/(T d) const { return P(x / d, y / d); }
  T dot(P p) const { return x * p.x + y * p.y; }
  T cross(P p) const { return x * p.y - y * p.x; }
  bool cross(P a, P b) const { return (a - *this).cross(b - *this) > 0; }
  T dist2() const { return x * x + y * y; }
  double dist() const { return sqrt((double)dist2()); }
  // angle to x-axis in interval [-pi, pi]
  double angle() const { return atan2(y, x); }
  P unit() const { return *this / dist(); }  // makes dist()=1
  P perp() const { return P(-y, x); }        // rotates +90 degrees
  P normal() const { return perp().unit(); }
  // returns point rotated 'a' radians ccw around the origin
  P rotate(double a) const {
    return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
  }
  friend ostream &operator<<(ostream &os, P p) {
    return os << "(" << p.x << "," << p.y << ")";
  }
};


template <class P>
int sideOf(P s, P e, P p) {
  return sgn(s.cross(e, p));
}

#define sz(x) int(x.size())

// center of the polygon
typedef Point<double> P;

P polygonCenter(const vector<P>& v) { 
 P res(0, 0); 
 double A = 0;
 for (int i = 0, j = sz(v) - 1; i < sz(v); j = i++) {
  res = res + (v[i] + v[j]) * v[j].cross(v[i]);
  A += v[j].cross(v[i]);
 }
 return res / A / 3; 
}

P lineProj(P a, P b, P p, bool refl=false) {
 P v = b - a;
 return p - v.perp()*(1+refl)*v.cross(p-a)/v.dist2();
}

double angle(P o, P a, P b) { 
 auto oa = o - a; 
 auto ob = o - b; 
 double ans = oa.dot(ob) / (oa.dist() * ob.dist()); 
 return acos(ans) / acos(-1) / 2; 
}


int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n; 
  vector<P>points(n); 
  for(auto &p : points) { 
   cin >> p.x >> p.y; 
  }
  vector<double>f(n), dp(n); 
  auto centroid = polygonCenter(points); 
  for(int i = 0; i < n; i++) { 
   f[i] = angle(centroid, points[i], points[(i + 1) % n]); 
  }
  vector<int>par(n); 
  iota(par.begin(), par.end(), 0); 
  function<int(int)> F = [&](int u) { 
   return u == par[u] ? u : par[u] = F(par[u]); 
  }; 

  for(int i = 0; i < n; i++) { 
   auto projected = lineProj(points[i], points[(i + 1) % n], centroid); 
   if(centroid.cross(projected, points[i]) && points[i] != projected) { 
    par[i] = (i + n - 1) % n; 
   }
   if(!centroid.cross(projected, points[(i + 1) % n]) && points[(i + 1) % n] != projected) { 
    par[i] = (i + 1) % n; 
   }
  }
  for(int i = 0; i < n; i++) { 
   dp[F(i)] += f[i]; 
  }
  cout << fixed << setprecision(10); 
  for(int i = 0; i < n; i++) { 
   cout << dp[i] << '\n'; 
  }
  return 0;
}