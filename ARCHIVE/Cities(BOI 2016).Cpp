#include <bits/stdc++.h>

#include <iostream>
#include <vector>
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;
const int N = 2e5 + 10;
const long long INF = 1e17;
long long n, m, comp, k, s, t;
vector<pii> adj[N + 1];
vector<int> tadj[7][N + 1];
deque<int> S;
int pos[N + 1];
int timer = 1;
long long dp[(1 << 7)][N + 1];
bool vis[N + 1];
void dijsktra() {
  using T = pair<long long, int>;
  priority_queue<T> pq;
  memset(dp, 0x3f3f3f3f, sizeof(dp));
  for (int i = 0; i < k; i++) {
    dp[(1 << i)][pos[i]] = 0;
  }
  for (int mask = 0; mask < (1 << k); mask++) {
    for (int f = 0; f < mask; f++) {
      if ((mask | f) != mask) continue;
      int s = f xor mask;
      if (s > f) continue;
      for (int i = 1; i <= n; i++) {
        dp[mask][i] = min((long long)(dp[s][i] + dp[f][i]), dp[mask][i]);
      }
    }
    for (int i = 1; i <= n; i++) {
      if (dp[mask][i] == INF) continue;
      pq.push({-dp[mask][i], i});
    }
    while (pq.size()) {
      int node;
      long long weight;
      tie(weight, node) = pq.top();
      pq.pop();
      if (dp[mask][node] != -weight) continue;
      for (int i = 0; i < adj[node].size(); i++) {
        int v = adj[node][i].first;
        int weightx = adj[node][i].second;
        if (dp[mask][v] > dp[mask][node] + weightx) {
          dp[mask][v] = dp[mask][node] + weightx;
          pq.push({-dp[mask][v], v});
        }
      }
    }
  }
}
int main() {
  scanf("%d%d%d", &n, &k, &m);
  for (int i = 0; i < k; i++) scanf("%d", &pos[i]);
  for (int i = 0; i < m; i++) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
  }
  dijsktra();
  long long ans = INF;
  for (int i = 1; i <= n; i++) {
    ans = min(ans, dp[(1 << k) - 1][i]);
  }
  printf("%lld\n", ans);
  return 0; 
}