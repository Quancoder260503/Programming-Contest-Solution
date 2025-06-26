#include "bits/stdc++.h" 

using namespace std; 

int main(void) {
 int N, M; 
 cin >> N >> M; 
 vector<vector<int>>g(N); 
 for(int i = 0, u, v; i < M; i++) { 
  cin >> u >> v; 
  --u, --v; 
  g[u].push_back(v); 
  g[v].push_back(u); 
 } 
 vector<int>vis(N); 
 int cc = 0; 
 function<void(int)> dfs = [&](int u) { 
  cc++; 
  vis[u] = true; 
  for(auto v : g[u]) { 
   if(vis[v]) continue; 
   dfs(v); 
  } 
  return; 
 }; 
 int ans = 0; 
 for(int i = 0; i < N; i++) { 
  if(vis[i]) continue; 
  cc = 0; 
  dfs(i); 
  ans = max(ans, cc);  
 } 
 cout << ans << '\n'; 
 return 0; 
} 