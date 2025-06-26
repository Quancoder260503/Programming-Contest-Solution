#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int MOD = 1e9 + 7;

int solve(void) { 
 int N; 
 cin >> N; 
 vector<vector<int>>graph(N); 
 for(int i = 0, u, v; i < N - 1; i++) { 
  cin >> u >> v; 
  --u, --v; 
  graph[u].push_back(v); 
  graph[v].push_back(u); 
 }
 vector<int>dp(N); 
 function<int(int, int)> dfs = [&](int u, int p) -> int { 
  int ans = 0; 
  for(auto v : graph[u]) { 
   if(v == p) continue; 
   ans = max(ans, 1 + dfs(v, u)); 
  }
  dp[u] = ans; 
  return ans; 
 }; 
 dfs(0, -1); 
 int64_t ans = 0; 
 for(int i = 0; i < N; i++) { 
  ans += (dp[i] + 1); 
 }
 for(int i = 0; i < N - 1; i++) { 
  ans = (ans * 2) % MOD; 
 }
 cout << ans << '\n'; 
 return 0; 
}

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int T; 
 for(cin >> T; T--; ) { solve(); }
 return 0; 
} 
