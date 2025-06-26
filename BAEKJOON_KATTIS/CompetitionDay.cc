#include "bits/stdc++.h"

using namespace std;

const int64_t oo = LLONG_MAX / 1000;
const int maxf = 3e5 + 2; 

vector<pair<int, int>>g[maxf]; 

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int N, M, S, T;
  while (cin >> N >> M >> S >> T) {
    if(!N) break; 
    for(int i = 0; i < N; i++) { 
      g[i].clear(); 
    }
    for (int i = 0, u, v, w; i < M; i++) {
      cin >> u >> v >> w;
      --u, --v;
      g[u].push_back({v, w});
    }
    for(int i = 0; i < N; i++) { 
      sort(g[i].begin(), g[i].end()); 
    }
    using Type = pair<int64_t, int>;
    vector<int64_t> dist(N, oo);
    priority_queue<Type, vector<Type>, greater<Type>> pq;
    vector<int>par(N);
    --S, --T; 
    pq.push({0, S});
    dist[S] = 0;
    while (pq.size()) {
      auto [d, u] = pq.top();
      pq.pop();
      if (d != dist[u]) continue;
      for (auto [v, w] : g[u]) {
        if (dist[v] > dist[u] + w) {
          par[v] = u; 
          pq.push({dist[v] = dist[u] + w, v});
        }
      }
    }
    int node = T; 
    int64_t pdist = dist[T], ret = oo; 
    while(node != S) {
      pair<int, int>curr = {node, -1}; 
      auto itr = lower_bound(g[par[node]].begin(), g[par[node]].end(), curr); 
      curr = *itr; 
      g[par[node]].erase(itr); 
      fill(dist.begin(), dist.end(), oo); 
      pq.push({0, S});
      dist[S] = 0;
      while (pq.size()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) continue;
        for (auto [v, w] : g[u]) {
          if (dist[v] > dist[u] + w) {          
            pq.push({dist[v] = dist[u] + w, v});
          }
        }
      } 
      if(dist[T] < oo) { 
        ret = min(ret, dist[T] - pdist); 
      }
      g[par[node]].push_back(curr); 
      node = par[node]; 
    }
    if(ret == oo) { 
      cout << "Matt wins.\n"; 
    } 
    else { 
      cout << ret << '\n';     
    }
  }
  return 0;
}