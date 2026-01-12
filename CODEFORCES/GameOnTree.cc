#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

int main(void) {
 int n, k, x; 
 cin >> n >> k; 
 vector<vector<int>>g(n); 
 for(int i = 0, u, v; i < n - 1; i++) { 
  cin >> u >> v; 
  --u, --v; 
  g[u].push_back(v); 
  g[v].push_back(u); 
 }    
 vector<int>query(k); 
 for(auto &x : query) { 
  cin >> x; 
  --x; 
 }
 vector<int>win(n); 
 vector<set<int>>g_child(n); 
 function<int(int, int)> dfs = [&](int u, int p) -> int {
  int is_leaf = true, can_win = false;  
  for(auto v : g[u]) { 
   if(v == p) continue; 
   int child_win = dfs(v, u); 
   if(!child_win) { 
    can_win = true; 
    g_child[u].insert(v); 
   // cerr << u << " " << v << '\n';
   } 
   is_leaf = false; 
  }
  if(is_leaf) { 
   return win[u] = false; 
  } 
  return win[u] = can_win; 
 }; 
 vector<int>can_win(n); 
 dfs(0, -1); 
 function<void(int, int)> dfs_2 = [&](int u, int p) {
  if(u > 0) { 
   if(win[u]) {  
    can_win[u] = 1;   
    if(!can_win[p]) { 
      g_child[u].insert(p); 
    }
   } else {  
    if(can_win[p]) {
     //cerr << u << " " << p << " " << sz(g_child[p]) << '\n';  
     if(sz(g_child[p]) == 1 && g_child[p].count(u)) { 
      can_win[u] = 1; 
      g_child[u].insert(p); 
     }
    } else {   
     can_win[u] = 1; 
     g_child[u].insert(p);
    } 
   }
  } else { 
    can_win[u] = win[u]; 
  } 
  for(auto v : g[u]) { 
   if(v == p) continue; 
   dfs_2(v, u); 
  }
  return; 
 }; 
 dfs_2(0, -1); 
 for(auto &x : query) { 
  cout << (can_win[x] ? "Ron" : "Hermione") << '\n'; 
 // cout << can_win[x] << " " << dfs(x, -1) << '\n'; 
 }
 return 0; 
}