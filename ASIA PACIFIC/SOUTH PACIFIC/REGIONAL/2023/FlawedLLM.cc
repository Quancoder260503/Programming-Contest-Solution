#include "bits/stdc++.h"

using namespace std;

const int oo = 1e7;

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
  // returns point rotated 'a' radians ccw around the origin
  P rotate(double a) const {
    return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
  }
  friend ostream& operator<<(ostream& os, P p) {
    return os << "(" << p.x << "," << p.y << ")";
  }
};
template <class P>
int sideOf(P s, P e, P p) {
  return sgn(s.cross(e, p));
}

template<class P>
double segDist(P& s, P& e, P& p) {
  if (s == e) return (p - s).dist();
  auto d = (e - s).dist2(), t = min(d, max((double) 0.0, (p - s).dot(e - s)));
  return ((p - s) * d - (e - s) * t).dist() / d;
}

using P = Point<double>;

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int N;
  cin >> N;
  vector<P> pts(N);
  for (int i = 0; i < N; i++) {
    cin >> pts[i].x >> pts[i].y;
  }
  vector<vector<int>> g(N);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) if(i != j) {
      if (fabsl((pts[j] - pts[N - 1]).dist() - segDist(pts[j], pts[i], pts[N - 1])) < 1e-7) {
        g[j].push_back(i);
      }
    }
  }
  vector<int> dyn(N, -oo);
  dyn[0] = 1;
  function<int(int)> doit = [&](int u) {
    if (dyn[u] != -oo) return dyn[u];
    int& ret = dyn[u];
    for (auto v : g[u]) {
      ret = max(ret, doit(v) + 1);
    }
    return ret;
  };
  cout << doit(N - 1) - 2 << '\n';
  return 0;
}