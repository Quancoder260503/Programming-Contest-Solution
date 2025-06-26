#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int MOD = 998244353; 

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N, Q, T; 
 for(cin >> T; T--; ) { 
  cin >> N >> Q; 
  vector<vector<int>>g(N); 
  for(int i = 0, u, v; i < N - 1; i++) { 
   cin >> u >> v; 
   --u, --v; 
   g[u].push_back(v); 
   g[v].push_back(u); 
  }
  vector<int>depth(N, 0), par(N, -1), dp(N); 
  function<void(int, int)> dfs = [&](int u, int p) { 
   if(depth[u] == 1) dp[u] = 1; 
   if(depth[u] >  1) dp[u] = dp[par[p]] + 2 * sz(g[p]); 
   par[u] = p; 
   for(auto v : g[u]) { 
    if(v == p) continue;
    depth[v] = depth[u] + 1; 
    dfs(v, u); 
   }
  }; 
  dfs(0, 0); 
  for(int i = 0; i < Q; i++) { 
    int v, p; 
    cin >> v >> p; 
    --v; 
    vector<int>cc; 
    for(int c = v; c != 0 && par[c] != 0; c = par[par[c]]) { 
     cc.push_back(sz(g[par[c]])); 
    }
    sort(cc.rbegin(), cc.rend()); 
    int64_t ret = dp[v]; 
    for(int j = 0; j < min(sz(cc), p); j++) { 
     (ret += MOD - 2 * (cc[j] - 1)) %= MOD; 
    }
    cout << ret << '\n'; 
  }
 }  
 return 0; 
}