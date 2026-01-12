#include <iostream> 
#include <vector> 
#include <algorithm>
#include <cstring> 


using namespace std; 

#define ll long long 
#define sz(x) int(x.size())

const int maxn = 2e5 + 10; 
vector<pair<int, int>>adj[maxn]; 
ll dp[maxn][1 << 3]; 
array<ll, 3> a[maxn]; 
ll ret; 

void dfs(int u, int p) { 
 for(int mask = 0; mask < (1 << 3); mask++) {
  ll sum = 0;   
  for(int i = 0; i < 3; i++) { 
   if(mask >> i & 1) { 
    sum += a[u][i] ; 
   } else { 
    sum -= a[u][i]; 
   }
  }
  dp[u][mask] = sum; 
 }
 for(auto &[v, w] : adj[u]) { 
  if(v == p) continue; 
  dfs(v, u); 
  for(int mask = 0; mask < (1 << 3); mask++) { 
   ret = max(ret, dp[u][mask] + dp[v][7 ^ mask] + w); 
  }
  for(int mask = 0; mask < (1 << 3); mask++) { 
   dp[u][mask] = max(dp[u][mask], dp[v][mask] + w); 
  }
 }
 return; 
}

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int n; 
 cin >> n; 
 for(int i = 0, u, v, w; i < n - 1; i++) { 
  cin >> u >> v >> w; 
  adj[u].push_back({v, w}); 
  adj[v].push_back({u, w}); 
 }
 for(int i = 1; i <= n; i++) { 
  cin >> a[i][0] >> a[i][1] >> a[i][2]; 
 }
 memset(dp, -63, sizeof dp); 
 dfs(1, 0); 
 cout << ret << '\n'; 
 return 0; 
}