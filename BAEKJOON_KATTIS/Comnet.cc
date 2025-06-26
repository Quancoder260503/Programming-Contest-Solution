#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

int64_t dp[2002][2002][5]; 
int n_edges[1002]; 

int main(void) {
 ios_base::sync_with_stdio(false);
 cin.tie(0);
 cout.tie(0);
 int N, K, A, B;
 cin >> N >> K >> A >> B;
 vector<vector<int>> g(N);
 for (int i = 0, u, v; i < N - 1; i++) {
  cin >> u >> v;
  --u, --v;
  g[u].push_back(v);
  g[v].push_back(u);
 }
 function<void(int, int)> dfs = [&](int u, int p) {
  dp[u][0][0] = dp[u][0][1] = 1;
  for(auto v : g[u]) { 
   if(v == p) continue; 
   dfs(v, u); 
   for(int curr_edge = n_edges[u]; curr_edge >= 0; curr_edge--) { 
    for(int sub_edge = n_edges[v]; sub_edge >= 0; sub_edge--) { 
     for(int nodes = K; nodes >= 0; nodes--) { 
      for(int add_nodes = 1; add_nodes + nodes <= K; add_nodes++) { 
        dp[u][curr_edge + sub_edge + (add_nodes < K)][nodes + add_nodes] += 1LL * dp[v][sub_edge][add_nodes] * 
                                                                              dp[u][curr_edge][nodes]; 
      }
     }
    }
   }
   n_edges[u] += n_edges[v] + 1; 
  }
 }; 
 dfs(0, -1); 
 int64_t ans = 0; 
 for(int j = A; j <= B; j++) { 
  ans += dp[0][j][K]; 
 }
 cout << ans << '\n'; 
 return 0;
}


/***

Solution with k = 2, 3


#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

int main(void) {
 ios_base::sync_with_stdio(false);
 cin.tie(0);
 cout.tie(0);
 int N, K, A, B;
 cin >> N >> K >> A >> B;
 vector<vector<int>> g(N);
 for (int i = 0, u, v; i < N - 1; i++) {
  cin >> u >> v;
  --u, --v;
  g[u].push_back(v);
  g[v].push_back(u);
 }
 if (K == 2) {
  vector<int> depth(N);
  function<void(int, int)> dfs = [&](int u, int p) {
   for (auto v : g[u]) {
    if (v == p) continue;
    depth[v] = depth[u] + 1;
    dfs(v, u);
   }
  };
  int ret = 0;
  for (int i = 0; i < N; i++) {
   depth[i] = 0;
   dfs(i, -1);
   for (int j = 0; j < N; j++) {
    ret += (A <= depth[j] && depth[j] <= B);
   }
  }
  cout << ret / 2 << '\n';
 } else {
  vector<vector<int64_t>> depth(N);
  function<void(int, int)> dfs = [&](int u, int p) {
   depth[u].push_back(1);
   for (auto v : g[u]) {
    if (v == p) continue;
    dfs(v, u);
    depth[v].insert(depth[v].begin(), 0);
    if (sz(depth[u]) < sz(depth[v])) swap(depth[u], depth[v]);
    for (int j = 0; j < sz(depth[v]); j++) {
     depth[u][j] += depth[v][j];
    }
   }
  };
  int64_t ans = 0;
  for (int i = 0; i < N; i++) {
   for (int j = 0; j < N; j++) {
    depth[j].clear();
   }
   vector<vector<int64_t>> dp(K + 1, vector<int64_t>(N + 1));
   dp[0][0] = 1;
   for (auto v : g[i]) {
    dfs(v, i);
    depth[v].insert(depth[v].begin(), 0);
    for (int j = K; j > 0; j--) {
     for (int k = 0; k < sz(depth[v]); k++) {
      for (int weight = N; weight >= k; weight--) {
       dp[j][weight] += 1LL * dp[j - 1][weight - k] * depth[v][k];
      }
     }
    }
   }
   for (int j = A; j <= B; j++) {
    (ans += dp[K - 1][j] + dp[K][j]);
   }
  }
  cout << ans << '\n';
 }
 return 0;
}
**/