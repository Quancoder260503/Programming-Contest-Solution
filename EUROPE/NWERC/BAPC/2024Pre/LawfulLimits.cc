#include "bits/stdc++.h"
using namespace std; 

#define sz(x) int(x.size())

class LawfulLimits { 
public: 
  void solve() { 
   int N, M, T; 
   cin >> N >> M >> T; 
   vector<vector<array<int, 4>>>g(N); 
   for(int ind = 0; ind < M; ind++) { 
    int x, y, l, v, w; 
    cin >> x >> y >> l >> v >> w;
    x--, y--;  
    g[x].push_back({y, l, v, w}); 
    g[y].push_back({x, l, v, w});  
   }
   vector<double>dist(N, 1e50); 
   using C = pair<double, int>; 
   priority_queue<C, vector<C>, greater<C>>pq; 
   pq.push({0, 0}); 
   dist[0] = 0; 
   while(sz(pq)) { 
    auto [curr_dist, u] = pq.top(); 
    pq.pop(); 
    if(dist[u] < curr_dist) continue;
    for(auto [v, road_length, speed_pre, speed_aft] : g[u]) { 
     if(dist[u] < T) { 
      double time_dist = T - dist[u]; 
      if(time_dist * speed_pre <= road_length) { 
        if(dist[v] > dist[u] + time_dist + (road_length - time_dist * speed_pre) / speed_aft) { 
          dist[v] = dist[u] + time_dist + (road_length - time_dist * speed_pre) / speed_aft; 
          pq.push({dist[v], v}); 
        }
      } else { 
        if(dist[v] > dist[u] + 1. * road_length / speed_pre) { 
          dist[v] = dist[u] + 1. * road_length / speed_pre; 
          pq.push({dist[v], v}); 
        }
      }
     } else { 
      if(dist[v] > dist[u] + 1. * road_length / speed_aft) { 
        dist[v] = dist[u] + 1. * road_length / speed_aft; 
        pq.push({dist[v], v}); 
      }
     }
    }
   }
   cout << dist[N - 1] << '\n'; 
   return;  
  }
}; 

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 cout << fixed << setprecision(10); 
 LawfulLimits law; 
 law.solve(); 
 return 0; 
}