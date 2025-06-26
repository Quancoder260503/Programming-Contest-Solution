#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int64_t oo = LLONG_MAX / 4; 

int main(void) {  
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N, M, src, sink;
  cin >> N >> M >> src >> sink; 
  --src, --sink; 
  vector<vector<pair<int, int>>>g(N); 
  int64_t ret = 0; 
  for(int i = 0, u, v, w; i < M; i++) { 
    cin >> u >> v >> w; 
    ret += w; 
    g[--u].push_back({--v, w}); 
    g[v].push_back({u, w}); 
  }
  vector<int64_t>dist(N, oo); 
  using T = pair<int64_t, int>; 
  priority_queue<T, vector<T>, greater<T>>pq; 
  dist[src] = 0;
  pq.push({0, src}); 
  vector<vector<pair<int, int>>>par(N); 
  while(sz(pq)) { 
    auto [dst, u] = pq.top();
    pq.pop();
    if(dist[u] != dst) continue; 
    for(auto [v, w] : g[u]) { 
      if(dist[v] == dist[u] + w) { 
        par[v].push_back({u, w}); 
      }
      else if(dist[v] > dist[u] + w) { 
        par[v].clear(); 
        par[v].push_back({u, w}); 
        dist[v] = dist[u] + w; 
        pq.push({dist[v], v}); 
      }
    }
  }
  vector<int>vis(N, false); 
  function<void(int)> trace = [&](int u) { 
    if(vis[u]) return; 
    vis[u] = true; 
    for(auto [v, w] : par[u]) { 
      ret = ret - w; 
      trace(v); 
    }
    return; 
  };
  trace(sink); 
  cout << ret << '\n'; 
  return 0; 
}