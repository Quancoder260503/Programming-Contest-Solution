#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N, M, K; 
 cin >> N >> M >> K; 
 vector<vector<pair<int, int>>>g(N); 
 vector<array<int, 3>>edges; 
 vector<int>par(N); 
 iota(par.begin(), par.end(), 0); 
 function<int(int)> F = [&](int u) { 
  return par[u] == u ? u : par[u] = F(par[u]); 
 }; 
 for(int i = 0, u, v, w; i < M; i++) { 
  cin >> u >> v >> w; 
  --u, --v; 
  g[u].push_back({v, w}); 
  g[v].push_back({u, w}); 
  edges.push_back({u, v, w}); 
  par[F(u)] = F(v);  
}

vector<int>weights; 
for(auto [u, v, w] : edges) { 
  if(F(u) == F(0)) { 
    weights.push_back(w);  
  } 
}
sort(weights.begin(), weights.end()); 
int64_t ans = 0; 
for(int i = 0; i < min(K, sz(weights)); i++) { 
  ans += weights[i];   
}
auto dijsktra = [&]() { 
  vector<int64_t>dp(N, LLONG_MAX / 4); 
  using T = pair<int64_t, int>; 
  priority_queue<T, vector<T>, greater<T>>pq;  
  pq.push({0, 0}); 
  dp[0] = 0; 
  vector<vector<pair<int, int>>>par(N); 
  while(sz(pq)) { 
   auto [d, u] = pq.top(); 
   pq.pop(); 
   if(dp[u] != d) continue; 
   for(auto [v, w] : g[u]) { 
    if(dp[v] > dp[u] + w) { 
     dp[v] = dp[u] + w; 
     par[v].clear(); 
     par[v].push_back({u, w}); 
     pq.push({dp[v], v}); 
    } else if(dp[v] == dp[u] + w) { 
     par[v].push_back({u, w}); 
    }
   }
  }
  return dp[N - 1]; 
 }; 
 ans = min(ans, dijsktra()); 
 cout << ans << '\n'; 
 return 0; 
}