#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const double oo = 1e50; 

int main(void) { 
 int N, M, K; 
 cin >> N >> M >> K;  
 vector<vector<array<int, 2>>>g(N); 
 for(int i = 0, u, v, L; i < M; i++) { 
  cin >> u >> v >> L; 
  --u, --v; 
  g[u].push_back({v, L}); 
  g[v].push_back({u, L}); 
 }
 vector<pair<double, int>>store; 
 int sure = false; 
 double prob; 
 for(int i = 0, x; i < K; i++) { 
  cin >> x >> prob;
  store.push_back({prob, x - 1}); 
  sure |= (prob == 1); 
 }
 if(!sure) { 
  cout << "impossible\n"; 
  return 0; 
 }
 auto dijsktra = [&](int src) { 
  using T = pair<double, int>; 
  priority_queue<T, vector<T>, greater<T>>pq; 
  vector<double>dist(N, oo); 
  dist[src] = 0;   
  pq.push({dist[src], src}); 
  while(sz(pq)) { 
   auto [dd, u] = pq.top(); 
   pq.pop(); 
   if(dist[u] != dd) continue; 
   for(auto [v, L] : g[u]) { 
    if(dist[v] > dist[u] + L) { 
        dist[v] = dist[u] + L; 
        pq.push({dist[v], v});   
    }
   }
  }
  return dist; 
 };  
 auto dist = dijsktra(0); 
 auto dist_2 = dijsktra(N - 1); 
 vector<int>ord(K); 
 iota(ord.begin(), ord.end(), 0); 
 sort(ord.begin(), ord.end(), [&](int u, int v) { 
  int node_u = store[u].second; 
  int node_v = store[v].second; 
  return dist[node_u] + dist_2[node_u] < dist[node_v] + dist_2[node_v]; 
 });
 double curr = 1.0, ans = 0; 
 for(auto ind : ord) {
  auto [prob, x] = store[ind]; 
 // cout << dist[x] << " " << dist_2[x] << " " << x << '\n'; 
  ans += prob * curr * (dist[x] + dist_2[x]);
  curr = curr * (1 - prob);  
 } 
 cout << fixed << setprecision(10) << ans << '\n'; 
 return 0; 
}