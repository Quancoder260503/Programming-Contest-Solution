#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()

struct pt {
  int64_t x, y;
  explicit pt(int64_t x = 0, int64_t y = 0) : x(x), y(y) {}
  pt operator+(pt p) const { return pt(x + p.x, y + p.y); }
  pt operator-(pt p) const { return pt(x - p.x, y - p.y); }
  int64_t cross(pt p) const { return x * p.y - y * p.x; }
  int64_t dist2() { return 1LL * x * x + 1LL * y * y; }
};

int orientation(pt a, pt b, pt c) {
  int64_t v = a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
  if (v < 0) return -1;  // clockwise
  if (v > 0) return +1;  // counter-clockwise
  return 0;
}

bool cw(pt a, pt b, pt c, bool include_collinear) {
  int o = orientation(a, b, c);
  return o < 0 || (include_collinear && o == 0);
}
bool ccw(pt a, pt b, pt c, bool include_collinear) {
  int o = orientation(a, b, c);
  return o > 0 || (include_collinear && o == 0);
}

vector<pt> convex_hull(vector<pt>a, bool include_collinear = false) {
  if (a.size() == 1) return a;
  sort(a.begin(), a.end(),
       [](pt a, pt b) { return make_pair(a.x, a.y) < make_pair(b.x, b.y); });
  pt p1 = a[0], p2 = a.back();
  vector<pt> up, down;
  up.push_back(p1);
  down.push_back(p1);
  for (int i = 1; i < (int)a.size(); i++) {
    if (i == a.size() - 1 || cw(p1, a[i], p2, include_collinear)) {
      while (up.size() >= 2 &&
             !cw(up[up.size() - 2], up[up.size() - 1], a[i], include_collinear))
        up.pop_back();
      up.push_back(a[i]);
    }
    if (i == a.size() - 1 || ccw(p1, a[i], p2, include_collinear)) {
      while (down.size() >= 2 &&
             !ccw(down[down.size() - 2], down[down.size() - 1], a[i],
                  include_collinear))
        down.pop_back();
      down.push_back(a[i]);
    }
  }

  if (include_collinear && up.size() == a.size()) {
    reverse(a.begin(), a.end());
    return a;
  }
  a.clear();
  for (int i = 0; i < (int)up.size(); i++) a.push_back(up[i]);
  for (int i = down.size() - 2; i > 0; i--) a.push_back(down[i]);
  return a;
}

int64_t polygonArea2(vector<pt> v) {
  reverse(v.begin(), v.end());
  int64_t a = v.back().cross(v[0]);
  for (int i = 0; i < sz(v) - 1; i++) {
    a += v[i].cross(v[i + 1]);
  }
  return a;
}

int main(void) {
  int N;
  cin >> N;
  vector<pt> pts(N);
  for (int i = 0; i < N; i++) {
    int64_t x, y;
    cin >> x >> y;
    pts[i] = pt(x, y);
  }
  auto cc = pts;
  pts = convex_hull(cc, true);
  auto getArea = [&](int a, int b, int c, int d) {
    vector<pt> poly = {pts[a], pts[b], pts[c], pts[d]};
    return polygonArea2(poly);
  };
  auto func = [&](bool include_collinear) {
    int64_t area = 0;
    pts = convex_hull(cc, include_collinear);
    for (int i = 0, ptr = 1; i < sz(pts); i++) {
      //  cout << (int64_t) (pts[i] - pts[ptr]).dist2() << '\n';
      while ((ptr + 1) % sz(pts) != i &&
             (pts[i] - pts[ptr]).dist2() <=
                 (pts[i] - pts[(ptr + 1) % sz(pts)]).dist2()) {
        ptr = (ptr + 1) % sz(pts);
      }
      // vector<P> poly = {pts[(i - 1 + sz(pts)) % sz(pts)], pts[i], pts[(i + 1)
      // % sz(pts)], pts[ptr]};
      area = max(area, getArea((i - 1 + sz(pts)) % sz(pts), i,
                               (i + 1) % sz(pts), ptr));
      int maxBound = (include_collinear ? 100 : 2); 
      for (int dist = 1; dist < maxBound; dist++) {
        int prev = (ptr - dist + sz(pts)) % sz(pts);
        if (prev == (i + 1) % sz(pts)) break;
        area = max(area, getArea((i - 1 + sz(pts)) % sz(pts), i,
                                 (i + 1) % sz(pts), prev));
      }
      for (int dist = 1; dist < maxBound; dist++) {
        int next = (ptr + dist) % sz(pts);
        if (next == (i - 1 + sz(pts)) % sz(pts)) break;
        area = max(area, getArea((i - 1 + sz(pts)) % sz(pts), i,
                                 (i + 1) % sz(pts), next));
      }
    }
    int64_t ret = polygonArea2(pts) - area;
    return ret;
  };
  cout << min(func(true), func(false)) << '\n';
  return 0;
}