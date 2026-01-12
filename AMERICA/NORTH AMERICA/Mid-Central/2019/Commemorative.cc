#include "bits/stdc++.h"

using namespace std;

const int64_t oo = 1e14; 
const int maxn = 5e5 + 5; 

vector<int>g[maxn]; 
int n, m, ans[maxn], dp[maxn][2], vis[maxn], marked[maxn]; 

void memo(int u) { 
 if(vis[u] == 1) return; 
 vis[u] = 1; 
 for(auto v : g[u]) { 
  memo(v); 
  if(dp[u][0] < dp[v][0] + 1) {
   dp[u][1] = dp[u][0];  
   dp[u][0] = dp[v][0] + 1; 
  } else if(dp[u][1] < dp[v][0] + 1) {
   dp[u][1] = dp[v][0] + 1; 
  }
 }
 return; 
}

void dfs(int u, int len) { 
 if(vis[u] == 1) return; 
 vis[u] = 1; 
 for(auto v : g[u]) { 
  if(dp[u][0] == dp[v][0] + 1) { 
   dfs(v, len + 1); 
   marked[len]++; 
   ans[len] = dp[u][1] + len; 
  }
 }
}

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);
 cin >> n >> m; 
 for(int i = 1; i <= n; i++) { 
  g[0].push_back(i); 
 }
 for(int i = 0, u, v; i < m; i++) { 
  cin >> u >> v; 
  g[u].push_back(v); 
 }
 memo(0); 
 memset(vis, 0, sizeof(vis)); 
 dfs(0, 0); 
 int ret = dp[0][0]; 
 for(int i = 1; i <= n; i++) { 
  if(marked[i] == 1) { 
    ret = min(ret, ans[i]); 
  }
 }
 cout << ret << '\n'; 
 return 0; 
}