#include "bits/stdc++.h"
 
#pragma GCC optimize(" unroll-loops")
#pragma gcc optimize("Ofast")
#pragma GCC optimization("Ofast")
#pragma optimize(Ofast)
 
using namespace std;
 
#define sz(x) int(x.size())
 
const int maxf = 5e3 + 3;
const int LOG = 23;
 
vector<int> g[maxf];
int64_t height[maxf][3]; 
int dep[maxf], N;
vector<int>dp[maxf]; 
 
void dfs(int u, int p) {  
 dp[u].push_back(1); 
 for(auto v : g[u]) { 
  if(v == p) continue;
  dfs(v, u);
  dp[v].insert(dp[v].begin(), 0);  
  if(sz(dp[u]) < sz(dp[v])) swap(dp[u], dp[v]); 
  for(int j = 0; j < sz(dp[v]); j++) { 
   dp[u][j] += dp[v][j];  
  }  
 }
 return; 
}
 
int main(void) {  
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 cin >> N; 
 for(int i = 0, u, v; i < N - 1; i++) { 
  cin >> u >> v; 
  g[u].push_back(v); 
  g[v].push_back(u); 
 }
 int64_t ret = 0; 
 for(int rt = 1; rt <= N; rt++) {
  for(auto v : g[rt]) { 
   dfs(v, rt); 
   for(int j = 0; j < sz(dp[v]); j++) {
    height[j][2] += dp[v][j] * height[j][1]; 
    height[j][1] += dp[v][j] * height[j][0]; 
    height[j][0] += dp[v][j]; 
   }
  }
  for(int j = 1; j <= N; j++) { 
   ret += height[j - 1][2]; 
   height[j - 1][0] = height[j - 1][1] = height[j - 1][2] = 0; 
   dp[j].clear(); 
  }
 } 
 cout << ret << '\n'; 
 return 0; 
}