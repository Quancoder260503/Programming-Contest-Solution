#include "bits/stdc++.h"

using namespace std; 


/* More powerful template credited by user Hos_Lyric */

using Double = long double;
constexpr Double INF = 1e+20;

// min (p x + q),  p: decr.
struct ConvexMin {
  vector<pair<Double, Double>> lines;
  vector<Double> xs;
  ConvexMin() : lines{}, xs{} {}
  /* 
  friend ostream &operator<<(ostream &os, const ConvexMin &f) {
    return os << "(" << f.lines << ", " << f.xs << ")";
  }
  */ 
  void add(Double p, Double q) {
    if (lines.size() >= 1 && lines.back().first == p && lines.back().second <= q) return;
    for (; lines.size() >= 1; lines.pop_back(), xs.pop_back()) {
      assert(lines.back().first >= p);
      if (lines.back().first == p) continue;
      const Double x = (q - lines.back().second) / (lines.back().first - p);
      if (xs.back() < x) {
        lines.emplace_back(p, q);
        xs.push_back(x);
        return;
      }
    }
    lines.emplace_back(p, q);
    xs.emplace_back(-INF);
  }
  void add(const pair<Double, Double> &line) {
    add(line.first, line.second);
  }
  Double operator()(Double x) const {
    if (!lines.size()) return -INF;
    const int pos = upper_bound(xs.begin(), xs.end(), x) - xs.begin() - 1;
    return lines[pos].first * x + lines[pos].second;
  }
};

// max (p x + q),  p: incr.
struct ConvexMax {
  vector<pair<Double, Double>> lines;
  vector<Double> xs;
  ConvexMax() : lines{}, xs{} {}
  /* 
  friend ostream &operator<<(ostream &os, const ConvexMax &f) {
    return os << "(" << f.lines << ", " << f.xs << ")";
  }
  */ 
  void add(Double p, Double q) {
    if (lines.size() >= 1 && lines.back().first == p && lines.back().second >= q) return;
    for (; lines.size() >= 1; lines.pop_back(), xs.pop_back()) {
      assert(lines.back().first <= p);
      if (lines.back().first == p) continue;
      const Double x = (q - lines.back().second) / (lines.back().first - p);
      if (xs.back() < x) {
        lines.emplace_back(p, q);
        xs.push_back(x);
        return;
      }
    }
    lines.emplace_back(p, q);
    xs.emplace_back(-INF);
  }
  void add(const pair<Double, Double> &line) {
    add(line.first, line.second);
  }
  Double operator()(Double x) const {
    if (!lines.size()) return -INF;
    const int pos = upper_bound(xs.begin(), xs.end(), x) - xs.begin() - 1;
    return lines[pos].first * x + lines[pos].second;
  }
};


int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    cout.tie(0); 
    int n; 
    cin >> n;    
    vector<pair<Double, Double>>a(n), b(n);
    for(int i = 0, x, y, u, v; i < n; i++) { 
        cin >> x >> y >> u >> v;
        a[i] = {u, x}; 
        b[i] = {v, y}; 
    }
    sort(a.begin(), a.end()); 
    sort(b.begin(), b.end());
    ConvexMax max_x, max_y; 
    ConvexMin min_x, min_y;  
    for(int i = 0; i < n; i++) {
        max_x.add(a[i]);
        max_y.add(b[i]);  
    }
    for(int i = n - 1; i >= 0; i--) { 
        min_x.add(a[i]); 
        min_y.add(b[i]); 
    }
    vector<double>c; 
    for(const auto &r : max_x.xs) if(r >= 0) c.push_back(r);
    for(const auto &r : max_y.xs) if(r >= 0) c.push_back(r);  
    for(const auto &r : min_x.xs) if(r >= 0) c.push_back(r); 
    for(const auto &r : min_y.xs) if(r >= 0) c.push_back(r); 
    c.push_back(INF); 
    c.push_back(0); 
    sort(c.begin(), c.end()); 
    Double ret = 1e100; 
    for(int iter = 0, i = 0, j = 0, k = 0, l = 0; iter + 1 < c.size(); iter++) { 
        Double lo = c[iter], hi = c[iter + 1]; 
        Double mid = (lo + hi) / 2; 
        for(; i + 1 < max_x.xs.size() && max_x.xs[i + 1] <= mid; i++); 
        for(; j + 1 < max_y.xs.size() && max_y.xs[j + 1] <= mid; j++); 
        for(; k + 1 < min_x.xs.size() && min_x.xs[k + 1] <= mid; k++); 
        for(; l + 1 < min_y.xs.size() && min_y.xs[l + 1] <= mid; l++); 
        Double u = max_x.lines[i].first  - min_x.lines[k].first;
        Double x = max_x.lines[i].second - min_x.lines[k].second; 
        Double v = max_y.lines[j].first  - min_y.lines[l].first; 
        Double y = max_y.lines[j].second - min_y.lines[l].second; 
        ret = min(ret, (lo * u + x) * (lo * v + y)); 
        if(fabsl(u) > 0 && fabsl(v) > 0) { 
            Double p = max(-(u * y + v * x) / (2 * u * v), lo);  
            p = min(p, hi); 
            ret = min(ret, (p * u + x) * (p * v + y)); 
        }
    }
    cout << fixed << setprecision(10) << ret << '\n'; 
    return 0;
}