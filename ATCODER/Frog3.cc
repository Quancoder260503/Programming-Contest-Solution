#include "bits/stdc++.h"

using namespace std;

#define int64_t long long

const long long oo = 1e18 + 11;

struct Line {
  long long a, b;
  long long f(long long x) { return a * x + b; }
};
bool operator<(const Line& f, const Line& g) {
  if (f.a != g.a) return f.a < g.a;
  return f.b > g.b;
}

struct Hull {
  vector<double> x;
  vector<Line> segs;

  void insert(Line l) {
    if (segs.empty()) {
      x.push_back(-oo);
      segs.push_back(l);
      return;
    }
    double xNew = -oo;
    while (!segs.empty()) {
      if (segs.back().a == l.a) {
        assert(segs.back().b >= l.b);
        return;
      }
      xNew = intersection(segs.back(), l);
      if (xNew < x.back()) {
        remove();
      } else
        break;
    }

    segs.push_back(l);
    x.push_back(xNew);
  }

  long long get(long long x0) {
    if (segs.empty()) {
      return -oo;
    }
    auto i = upper_bound(x.begin(), x.end(), x0) - x.begin() - 1;
    return segs[i].f(x0);
  }

 private:
  void remove() {
    segs.pop_back();
    x.pop_back();
  }
  double intersection(const Line& f, const Line& g) {
    return 1.0 * (f.b - g.b) / (g.a - f.a);
  }
};

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int N;
  int64_t C;
  cin >> N >> C;
  vector<int64_t> h(N), dyn(N);
  for (int i = 0; i < N; i++) {
    cin >> h[i];
  }
  Hull convex_hull;
  convex_hull.insert({2 * h[0], -h[0] * h[0]});
  for (int i = 1; i < N; i++) {
    dyn[i] = h[i] * h[i] + C - convex_hull.get(h[i]);
    convex_hull.insert({2 * h[i], -h[i] * h[i] - dyn[i]});
  }
  cout << dyn[N - 1] << '\n';
  return 0;
}
/*
  dyn[i] = dyn[j] + h[i] * h[i] - 2 * h[i] * h[j] + h[j] * h[j] + C;
*/