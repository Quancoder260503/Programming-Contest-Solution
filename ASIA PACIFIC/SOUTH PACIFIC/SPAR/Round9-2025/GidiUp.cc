#include "bits/stdc++.h"

using namespace std;

const int maxn = 3e5 + 10;

int dp[maxn][10][2][2];

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n, t, m, k;
  cin >> n >> t >> m >> k;
  vector<vector<int>> g(n);
  vector<int> marked(n);
  for (int i = 0, x; i < t; i++) {
    cin >> x;
    marked[--x] = 1;
  }
  vector<pair<int, int>>edge;
  for (int i = 0, u, v; i < m; i++) {
    cin >> u >> v;
    --u, --v;
    g[u].push_back(v);
    g[v].push_back(u);
    edge.push_back({u, v});
  }
  using T = array<int, 5>;
  memset(dp, 63, sizeof dp);
  priority_queue<T, vector<T>, greater<T>> pq;
  pq.push({0, 0, 0, marked[0], 0});
  dp[0][0][marked[0]][0] = 0;
  while (pq.size()) {
    auto [curr_d, curr_node, days, at_tav, status] = pq.top();
    pq.pop();
    if(dp[curr_node][days][at_tav][status] != curr_d) continue;
    if (at_tav) {
      if (!status) {
        if (dp[curr_node][0][at_tav][!status] > curr_d + 1) {
          dp[curr_node][0][at_tav][!status] = curr_d + 1;
          pq.push({curr_d + 1, curr_node, 0, at_tav, !status});
        }
      } else {
        for (auto v : g[curr_node]) {
          if (marked[v]) {
            if (dp[v][1][1][0] > curr_d + 1) {
              dp[v][1][1][0] = curr_d + 1;
              pq.push({curr_d + 1, v, 1, 1, 0});
            }
          } else {
            if (dp[v][1][0][0] > curr_d + 1) {
              dp[v][1][0][0] = curr_d + 1;
              pq.push({curr_d + 1, v, 1, 0, 0});
            }
          }
        }
      }
    } else {
      for (auto v : g[curr_node]) {
        if(days + 1 <= k) {  
         if (marked[v]) {
          if (dp[v][days + 1][1][0] > curr_d + 1) {
            dp[v][days + 1][1][0] = curr_d + 1;
            pq.push({curr_d + 1, v, days + 1, 1, 0});
          }
         } else if (dp[v][days + 1][0][0] > curr_d + 1) {
          dp[v][days + 1][0][0] = curr_d + 1;
          pq.push({curr_d + 1, v, days + 1, 0, 0});
        }
       }
      }
    }
  }
  int ans = maxn;
  for(int i = 0; i <= k; i++) {
   ans = min(ans, dp[n - 1][i][marked[n - 1]][marked[n - 1]]);
  }
  cout << (ans == maxn ? -1 : ans) << '\n'; 
  return 0;
}
