#include "bits/stdc++.h"
 
using namespace std;
 
#define sz(x) int(x.size())
 
struct DirectedDfs {
  vector<vector<int>> g;
  int n;
  vector<int> num, low, current, S;
  int counter;
  vector<int> comp_ids;
  vector<vector<int>> scc;
 
  DirectedDfs(const vector<vector<int>> &_g)
      : g(_g),
        n(g.size()),
        num(n, -1),
        low(n, 0),
        current(n, 0),
        counter(0),
        comp_ids(n, -1) {
    for (int i = 0; i < n; i++) {
      if (num[i] == -1) dfs(i);
    }
  }
 
  void dfs(int u) {
    low[u] = num[u] = counter++;
    S.push_back(u);
    current[u] = 1;
    for (auto v : g[u]) {
      if (num[v] == -1) dfs(v);
      if (current[v]) low[u] = min(low[u], low[v]);
    }
    if (low[u] == num[u]) {
      scc.push_back(vector<int>());
      while (1) {
        int v = S.back();
        S.pop_back();
        current[v] = 0;
        scc.back().push_back(v);
        comp_ids[v] = ((int)scc.size()) - 1;
        if (u == v) break;
      }
    }
  }
};
 
 
int main(void) { 
  int N, M; 
  cin >> N >> M; 
  vector<vector<int>>g(N), rg(N); 
  for(int i = 0, u, v; i < M; i++) { 
    cin >> u >> v;
    g[u].push_back(v); 
    rg[v].push_back(u); 
  } 
  DirectedDfs a(g); 
  if(sz(a.scc) < N) { 
   cout << -1 << '\n'; 
   return 0; 
  } 
  vector<int>dp(N, -1); 
  int ret = 0; 
  function<int(int)> dfs = [&](int u) { 
   if(dp[u] != -1) return dp[u]; 
   dp[u] = 0; 
   for(auto v : rg[u]) { 
    dp[u] = max(dp[u], dfs(v)); 
   } 
   dp[u]++; 
   ret = max(ret, dp[u]); 
   return dp[u]; 
  }; 
  for(int i = 0; i < N; i++) { 
   dfs(i); 
  }
  cout << ret << '\n'; 
  return 0; 
} 