#include "bits/stdc++.h"

using namespace std;

const double oo = 1e20;

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
  T dot(P p) const { return 1LL * x * p.x + 1LL * y * p.y; }
  T cross(P p) const { return 1LL * x * p.y - 1LL * y * p.x; }
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
  friend ostream &operator<<(ostream &os, P p) {
    return os << "(" << p.x << "," << p.y << ")";
  }
};
template <class P>
int sideOf(P s, P e, P p) {
  return sgn(s.cross(e, p));
}

template <class P>
bool onSegment(P s, P e, P p) {
  return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

template <class P>
int segInter(P a, P b, P c, P d) {
  auto oa = c.cross(d, a), ob = c.cross(d, b), oc = a.cross(b, c),
       od = a.cross(b, d);
  // Checks if intersection is single non-endpoint point.
  if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0) return true; 
  if (onSegment(c, d, a)) return true; 
  if (onSegment(c, d, b)) return true; 
  if (onSegment(a, b, c)) return true; 
  if (onSegment(a, b, d)) return true; 
  return false; 
}

using P = Point<int64_t>;

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
  vector<vector<double>> dist(N, vector<double>(N, oo));
  for (int i = 0; i < N; i++) {
    dist[i][i] = 0;
    dist[i][(i + 1) % N] = dist[(i + 1) % N][i] =
        (pts[i] - pts[(i + 1) % N]).dist();
    for (int j = i + 2; j < N; j++) {
      int checkInter = true;
      for (int k = i + 1; k + 1 < j; k++) {
        checkInter &= (!segInter(pts[i], pts[j], pts[k], pts[k + 1]));
      }
      for(int k = (j + 1) % N; (k + 1) % N != i; k = (k + 1) % N) { 
        checkInter &= (!segInter(pts[i], pts[j], pts[k], pts[(k + 1) % N])); 
      }
      int a = i, b = j, in = false; 
      for(int iter = 0; iter < 2; iter++) { 
        P v1 = (pts[(a + 1) % N] - pts[a]);
        P v2 = (pts[(a - 1 + N) % N] - pts[a]); 
        P v3 = (pts[b] - pts[a]);
        int64_t ccwA = v1.cross(v2), ccwB = v1.cross(v3), ccwC = v3.cross(v2); 
        in |= (ccwA >= 0 && ccwB >= 0 && ccwC >= 0) || (ccwA < 0 && !(max(ccwB, ccwC) < 0));
        swap(a, b); 
      }
      if(in && checkInter) { 
        dist[i][j] = dist[j][i] = (pts[i] - pts[j]).dist(); 
      }
    }
  }
  for (int k = 0; k < N; k++) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }
  cout << fixed << setprecision(9);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cout << dist[i][j] << " ";
    }
    cout << '\n';
  } 
  return 0;
}