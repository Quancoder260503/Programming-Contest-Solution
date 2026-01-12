#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int n, m; 
  cin >> n >> m;
  if(m >= 2) { 
   int64_t cost = 0; 
   for(int i = 0, u, v, c; i < n - 1; i++) { 
    cin >> u >> v >> c; 
    cost += c; 
   }
   cout << cost << '\n'; 
  } else { 
   vector<vector<pair<int, int>>>g(n); 
   for(int i = 0, u, v, c; i < n - 1; i++) { 
    cin >> u >> v >> c; 
    --u, --v; 
    g[u].push_back({v, c}); 
    g[v].push_back({u, c}); 
   }
   vector<int64_t>depth(n); 
   function<void(int, int)> dfs = [&](int u, int p) { 
    for(auto [v, cost] : g[u]) { 
     if(v == p) continue; 
     depth[v] = depth[u] + cost; 
     dfs(v, u); 
    }
    return; 
   };  
   dfs(0, -1); 
   int ind = 0; 
   for(int i = 0; i < n; i++) { 
    if(depth[i] > depth[ind]) { 
     ind = i; 
    }
   }
   depth[ind] = 0; 
   dfs(ind, -1); 
   cout << *max_element(depth.begin(), depth.end()) << '\n'; 
  }
  return 0;
}