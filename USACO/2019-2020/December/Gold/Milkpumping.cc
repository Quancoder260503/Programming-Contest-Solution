#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int maxf = 2e5 + 1; 
const int oo = 1e9; 

vector<array<int, 3>>g[maxf]; 
int N, M; 

int dijsktra(int thres) { 
 vector<int>dist(N, oo); 
 using T = pair<int, int>; 
 priority_queue<T, vector<T>, greater<T>>pq; 
 dist[0] = 0; 
 pq.push({dist[0], 0}); 
 while(sz(pq)) { 
  auto [d, u] = pq.top(); 
  pq.pop(); 
  if(dist[u] != d) continue; 
  for(auto [v, cost, flow] : g[u]) { 
   if(flow < thres) continue; 
   if(dist[v] > dist[u] + cost) { 
    dist[v] = dist[u] + cost; 
    pq.push({dist[v], v}); 
   }
  }
 }
 return dist[N - 1];  
}

int main(void) {  
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 cin >> N >> M; 
 vector<int>flow; 
 for(int i = 0, u, v, c, f; i < M; i++) { 
  cin >> u >> v >> c >> f; 
  --u, --v; 
  g[u].push_back({v, c, f}); 
  g[v].push_back({u, c, f}); 
  flow.push_back(f); 
 }
 double ret = 0; 
 for(auto f : flow) { 
  int dist = dijsktra(f); 
  if(dist == oo) continue; 
  ret = max(ret, 1. * f / dist); 
 }
 ret = ret * 1e6; 
 cout << int(ret) << '\n'; 
 return 0; 
}