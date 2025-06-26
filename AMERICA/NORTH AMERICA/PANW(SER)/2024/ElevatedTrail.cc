#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

int main() {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N, Q; 
 cin >> N >> Q;
 vector<vector<int>>g(N); 
 for(int i = 0, u, v; i < N - 3; i++) { 
  cin >> u >> v; 
  --u, --v; 
  g[u].push_back(v); 
  g[v].push_back(u); 
 } 
 vector<int>cc(N, -1), height(N), farthest(N); 
 function<void(int, int)> dfs = [&](int u, int comp_id) { 
  cc[u] = comp_id; 
  for(auto v : g[u]) { 
    if(cc[v] != -1) continue; 
    dfs(v, comp_id); 
    height[u] = max(height[u], height[v] + 1); 
  } 
  return; 
 }; 
 function<void(int, int, int)> dfs2 = [&](int u, int p, int maxOut) { 
  farthest[u] = max(maxOut, height[u]);
  vector<int>prefix, suffix; 
  for(auto v : g[u]) { 
   if(v == p) continue; 
   prefix.push_back(height[v] + 1); 
  } 
  suffix = prefix; 
  for(int i = 1; i < sz(prefix); i++) { 
    prefix[i] = max(prefix[i], prefix[i - 1]); 
  } 
  for(int i = sz(suffix) - 2; i >= 0; i--) {
    suffix[i] = max(suffix[i], suffix[i + 1]); 
  } 
  int ind = 0; 
  for(auto v : g[u]) { 
    if(v == p) continue; 
    int maxPath = maxOut; 
    if(ind) maxPath = max(maxPath, prefix[ind - 1]); 
    if(ind + 1 < sz(suffix)) maxPath = max(maxPath, suffix[ind + 1]);
    dfs2(v, u, maxPath + 1); 
    ind++; 
  } 
 }; 
 for(int i = 0, comp_id = 0; i < N; i++) { 
  if(cc[i] == -1) {
   dfs(i, comp_id++);
   dfs2(i, -1, 0); 
  }
 } 
 array<int, 3>opt = {0};
 for(int i = 0; i < N; i++) { 
  opt[cc[i]] = max(opt[cc[i]], farthest[i]); 
 } 
 for(int i = 0, u, v; i < Q; i++) { 
  cin >> u >> v; 
  --u, --v; 
  int ret = farthest[u] + farthest[v]; 
  for(int comp = 0; comp < 3; comp++) { 
   if(comp != cc[u] && comp != cc[v]) { 
     ret += opt[comp]; 
     break; 
   } 
  }
  cout << ret + 3 << '\n'; 
 } 
 return 0;
}