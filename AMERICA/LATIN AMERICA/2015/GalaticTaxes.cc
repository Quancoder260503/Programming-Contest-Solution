#include "bits/stdc++.h"

using namespace std;

const double oo = 1e50;

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N, M; 
  cin >> N >> M; 
  vector<vector<tuple<int, double, double>>>g(N);
  double a, b;
  for(int i = 0, u, v; i < M; i++) {
    cin >> u >> v >> a >> b;
    --u, --v;  
    g[u].push_back({v, a, b});
    g[v].push_back({u, a, b}); 
  } 
  auto dijsktra = [&](double x) { 
    vector<double>dist(N, oo);
    dist[0] = 0; 
    using T = pair<double, int>; 
    priority_queue<T, vector<T>, greater<T>>pq; 
    pq.push({0, 0}); 
    while(pq.size()) { 
      auto [dst, u] = pq.top(); 
      pq.pop(); 
    //  if(dist[u] != dst) continue;
      for(auto [v, a, b] : g[u]) { 
        if(dist[v] > dist[u] + a * x + b) {
           dist[v] = dist[u] + a * x + b;
           pq.push({dist[v], v}); 
        }
      }
    } 
    return dist[N - 1]; 
  };
  double lo = 0, hi = 24 * 60; 
  for(int iter = 0; iter < 100; iter++) { 
    double x1 = (2 * lo + hi) / 3; 
    double x2 = (lo + 2 * hi) / 3; 
    if(dijsktra(x1) < dijsktra(x2)) { 
       lo = x1; 
    }
    else {
       hi = x2; 
    }
  }
  cout << fixed << setprecision(5) << dijsktra(lo) << '\n'; 
  return 0; 
}