#include "bits/stdc++.h"

using namespace std;

#define int64_t long long
const int64_t oo = LLONG_MAX / 2; 

template <class T>
int sgn(T x) { return (x > 0) - (x < 0); }
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

int64_t Area(vector<P>& pset) {
  int N = pset.size(); 
  int64_t ret = 0;
  for(int i = 0; i < N; i++)  {
    ret += pset[i].cross(pset[(i + 1) % N]); 
  }
  return ret; 
}

int sideof(P s, P e, P p) { return sgn(s.cross(e, p)); }

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N; 
  cin >> N; 
  vector<P>pts(N); 
  for(int i = 0; i < N; i++) { 
    cin >> pts[i].x >> pts[i].y; 
  } 
  int64_t area = Area(pts); 
  int64_t ret = 0, sum = 0; 
  for(int i = 0, j = 1; i < N; i++) {
    int64_t cc = (pts[j] - pts[i]).cross(pts[(j + 1) % N] - pts[i]); 
    while((j + 2) % N != i && (2 * (sum + cc) <= area || (i + 1) % N == j)) { 
      sum += cc; 
      j = (j + 1) % N; 
      cc = (pts[j] - pts[i]).cross(pts[(j + 1) % N] - pts[i]); 
    }
    if(2 * sum > area) { 
       ret = max(ret, area - sum); 
    }
    else {
       int64_t c = sum; 
       if((j + 2) % N != i) c = max(c, area - c - cc); 
       ret = max(ret, area - c); 
    }
    sum = sum + (pts[(i + 1) % N] - pts[j]).cross(pts[i] - pts[j]);
  }
  cout << ret << " " << area - ret << '\n';
  return 0; 
}