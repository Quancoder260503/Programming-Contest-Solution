#include <bits/stdc++.h>

using namespace std;

#define sz(x) int(x.size())

const int _N = 200001;

int up[_N], down[_N];

int main() {
  int N;
  cin >> N;
  vector<int> rx;
  fill(up, up + _N, _N);
  fill(down, down + _N, -_N);
  for (int i = 0; i < N; i++) {
    char dir;
    int x, y;
    cin >> dir >> x >> y;
    if (dir == 'U') up[x] = min(up[x], y);
    if (dir == 'D') down[x] = max(down[x], y);
  //  cout << up[x] << " " << down[x] << " " << x << '\n'; 
    rx.push_back(x);
  }
  sort(rx.begin(), rx.end());
  rx.erase(unique(rx.begin(), rx.end()), rx.end());
  int yMin = 0, yMax = 0;
  vector<pair<int, int>> range;
  // range.push_back({0, 0});
  for (int i = 0; i < sz(rx); i++) {
    int dist = rx[i] - (i ? rx[i - 1] : 0);
    int lo = max(down[rx[i]] + 1, yMin - dist),
        hi = min(yMax + dist, up[rx[i]] - 1);
    //cout << lo << " " << hi << '\n';
    if (lo > hi) {
      cout << "Impossible\n";
      return 0;
    }
    range.push_back({lo, hi});
    yMin = lo, yMax = hi;
    // cout << lo << " " << hi << '\n';
  }
  string ret; 
  auto func = [&]() {
    ret = "+";
    for (int i = sz(range) - 2; i >= 0; i--) {
      int dist = (rx[i + 1] - rx[i]);
      int hi = min(range[i].second, yMax + dist) - yMax;
      int lo = max(range[i].first, yMax - dist)  - yMax;
      int a, b;
      if (abs(lo - dist) & 1) {
        if(lo == hi) return false; 
        b = (lo + 1 + dist) / 2;
        a = dist - b;
      } else {
        b = (lo + dist) / 2;
        a = dist - b;
      }
      for (int j = 0; j < a; j++) {
        ret = "+" + ret;
      }
      for (int j = 0; j < b; j++) {
        ret = "-" + ret;
      }
      //cout << a << " " << b << '\n'; 
      yMax = yMax + b - a;
    }
    return true; 
  };
  yMax = range.back().second;
  if (func() && abs(yMax - rx[0]) % 2 == 0) {
    int a = (yMax + rx[0]) / 2, b = rx[0] - a;
    for (int i = 0; i < a; i++) {
      ret = "+" + ret;
    }
    for (int i = 0; i < b; i++) {
      ret = "-" + ret;
    }
    cout << "Possible\n" << ret << '\n';
    return 0;
  }
  if (range.back().second == range.back().first) {
    cout << "Impossible\n";
    return 0;
  }
  yMax = range.back().second - 1;
  if (func() && abs(yMax - rx[0]) % 2 == 0) {
    int a = abs(yMax + rx[0]) / 2, b = rx[0] - a;
    for (int i = 0; i < a; i++) {
      ret = "+" + ret;
    }
    for (int i = 0; i < b; i++) {
      ret = "-" + ret;
    }
   // cout << sz(ret) << '\n'; 
    cout << "Possible\n" << ret << '\n';
    return 0;
  }
  else { 
    cout << "Impossible\n";
    return 0;
  } 
  return 0;
}