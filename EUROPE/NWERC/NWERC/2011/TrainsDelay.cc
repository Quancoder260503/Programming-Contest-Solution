#include "bits/stdc++.h"

using namespace std;

const double eps = 1e-6;

void doit(void) {
  int m; 
  map<string, int> mp;
  string src, snk;
  cin >> src >> snk; 
  cin >> m;
  int idx = 0;
  mp[src] = idx++, mp[snk] = idx++;
  vector<array<int, 6>> edge;
  for (int i = 0, prob, dept, len, delay; i < m; i++) {
    string a, b;
    cin >> a >> b >> dept >> len >> prob >> delay;
    if (mp.count(a) == 0) mp[a] = idx++;
    if (mp.count(b) == 0) mp[b] = idx++;
    edge.push_back({mp[a], mp[b], dept, len, prob, delay});
  }
  vector<vector<array<int, 5>>> g(idx);
  for (const auto [from, to, dept, len, prob, delay] : edge) {
    g[to].push_back({from, dept, len, prob, delay});
  }
  vector<vector<double>> dyn(idx, vector<double>(60, 1e20));
  for (int i = 0; i < 60; i++) {
    dyn[mp[snk]][i] = 0;
  }
  using T = tuple<double, int, int>;
  priority_queue<T, vector<T>, greater<T>> pq;
  pq.push({dyn[mp[snk]][0], mp[snk], 0});
  while (pq.size()) {
    auto [opt, u, time] = pq.top();
    pq.pop();
    if (opt > dyn[u][time] + eps) continue;
    for (const auto [v, dept, len, prob, delay] : g[u]) {
      double expected_time =
          (1.0 - prob / 100.0) * (len + dyn[u][(dept + len) % 60]);
      for (int d = 1; d <= delay; d++) {
        expected_time += double(prob) / (100.0 * delay) *
                         (len + d + dyn[u][(dept + d + len) % 60]);
      }
      if (dyn[v][dept] > eps + expected_time) {
        dyn[v][dept] = expected_time;
        pq.push({dyn[v][dept], v, dept});
        for (int time = 0; time < 60; time++) {
          dyn[v][(dept - time + 60) % 60] =
              min(dyn[v][(dept - time + 60) % 60], dyn[v][dept] + time);
        }
      }
    }
  }
  double ret = 1e20;
  for (int i = 0; i < 60; i++) {
     ret = min(ret, dyn[mp[src]][i]); 
  }
  if (ret < 1e10) {
	cout << ret << '\n';
  } 
  else {
	//cout << src << " " << snk << " " << ret << '\n'; 
    cout << "IMPOSSIBLE\n"; 
  }
  return;
}

int main(void) {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int tc;
  cin >> tc;
  cout << fixed << setprecision(10);
  while (tc--) {
    doit(); 
  }
  return 0;
}