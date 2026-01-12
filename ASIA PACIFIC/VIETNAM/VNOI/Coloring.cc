#include "bits/stdc++.h"

using namespace std;

#define int64_t long long

const int oo = 1e8;

int dp[5002][5002];
vector<int>g[5002];  
int N, tree_sz[5002]; 

void dfs(int u, int p) { 
 tree_sz[u] = 1; 
 dp[u][0] = 0; 
 int total = 0; 
 for(auto v : g[u]) { 
  if(v == p) continue;
  dfs(v, u);  
  for(int sz_u = tree_sz[u]; sz_u >= 0; sz_u--) { 
   for(int sz_v = tree_sz[v]; sz_v >= 0; sz_v--) { 
    if(sz_u + sz_v <= N) { 
     dp[u][sz_u + sz_v] = max(dp[u][sz_u + sz_v], dp[u][sz_u] + dp[v][sz_v] + sz_u * sz_v); 
    } 
   }
  }
  tree_sz[u] += tree_sz[v]; 
  int opt = 0; 
  for(int i = 0; i <= tree_sz[v]; i++) { 
   opt = max(opt, dp[v][i] + i); 
  }
  total += opt; 
 }
 dp[u][1] = max(dp[u][1], total); 
 return; 
};

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int T; 
  for(cin >> T; T--; ) { 
   cin >> N; 
   for(int i = 0; i < N; i++) { 
    g[i].clear(); 
    for(int j = 0; j <= N; j++) { 
     dp[i][j] = -oo; 
    }
   }
   for(int i = 0, u, v; i < N - 1; i++) { 
    cin >> u >> v; 
    --u, --v; 
    g[u].push_back(v); 
    g[v].push_back(u); 
   }
   dfs(0, -1);
   int ans = -oo; 
   for(int i = 0; i <= N; i++) { 
    ans = max(ans, dp[0][i]); 
   } 
   cout << ans << '\n';   
  }      
  return 0; 
}