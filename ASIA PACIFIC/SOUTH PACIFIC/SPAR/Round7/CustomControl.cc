#include "bits/stdc++.h"

using namespace std;

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#define sz(x) int(x.size())
#define int64_t long long

const int oo = 1e9; 

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int n, m, k; 
 cin >> n >> m >> k;  
 if(n == 2 && k == 1) { 
  cout << "impossible\n"; 
  return 0; 
 }
 vector<vector<int>>g(n), rg(n);
 vector<int>a(n); 
 for(auto &x : a) { 
  cin >> x; 
 }
 for(int i = 0, u, v; i < m; i++) { 
  cin >> u >> v;
  --u, --v; 
  g[u].push_back(v);
  g[v].push_back(u); 
 } 
 vector<vector<int>>par(n); 
 auto djsktra = [&](int src) {  
  using T = pair<int, int>; 
  priority_queue<T, vector<T>, greater<T>>pq; 
  vector<int>dist(n, oo); 
  dist[src] = a[src];
  pq.push({dist[src], src}); 
  while(pq.size()) {
   auto [d, u] = pq.top(); 
   //cout << u << " " << dist[u] << '\n'; 
   pq.pop(); 
   if(dist[u] != d) continue; 
   for(auto v : g[u]) { 
    if(dist[v] > dist[u] + a[v])  {
     dist[v] = dist[u] + a[v]; 
     par[v].clear(); 
     par[v].push_back(u); 
     pq.push({dist[v], v}); 
    } else if(dist[v] == dist[u] + a[v]) { 
     par[v].push_back(u); 
    } 
   }
  }
  return; 
 }; 
 vector<int>topo, vis(n); 
 function<void(int)> rec = [&](int u) { 
  if(!u) return;  
  for(auto v : par[u]) { 
   rg[v].push_back(u);
   rec(v);  
  }
  return; 
 }; 
 function<void(int)> dfs = [&](int u)  {
  vis[u] = 1; 
  for(auto v : rg[u]) { 
   if(vis[v]) continue;
   dfs(v); 
  }
  topo.push_back(u); 
 }; 
 djsktra(0); 
 rec(n - 1); 
 dfs(0); 
 string ans(n, ' '); 
 if(k < n - k) { 
  int amt = n - k; 
  for(int i = 0; i < sz(topo); i++) { 
   if(amt > 0) { 
    ans[topo[i]] = 'N'; 
    amt--; 
   } else { 
    ans[topo[i]] = 'A'; 
   }
  }
  for(int i = 0; i < n; i++) { 
   if(ans[i] == ' ') { 
    ans[i] = (amt > 0 ? 'N' : 'A'); 
    amt--; 
   }
  }
 } else { 
  int amt = k; 
  for(int i = 0; i < sz(topo); i++) { 
   if(amt > 0) { 
    ans[topo[i]] = 'A'; 
    amt--; 
   } else { 
    ans[topo[i]] = 'N'; 
   }
  }
  for(int i = 0; i < n; i++) { 
   if(ans[i] == ' ') { 
    ans[i] = (amt > 0 ? 'A' : 'N'); 
    amt--; 
   }
  }
 }
 cout << ans << '\n'; 
 return 0; 
} 
