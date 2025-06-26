#include "bits/stdc++.h"

using namespace std; 

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N, T, M; 
 for(cin >> T; T--; ) { 
  cin >> N >> M; 
  vector<array<int, 3>>edges; 
  for(int i = 0, u, v, w; i < M; i++) { 
   cin >> u >> v >> w;
   --u, --v;  
   edges.push_back({u, v, w}); 
  }
  int ans = 0; 
  for(int b = 30; b >= 0; b--) { 
   vector<int>par(N), comp(N); 
   iota(par.begin(), par.end(), 0); 
   fill(comp.begin(), comp.end(), 1); 
   function<int(int)> F = [&](int x) { 
    return par[x] == x ? x : par[x] = F(par[x]); 
   };
   vector<array<int, 3>>n_edges;  
   for(auto [u, v, w] : edges) { 
    if(w >> b & 1) continue;
    int fu = F(u), fv = F(v); 
    if(fu != fv) {
     par[fu] = fv; 
     comp[fv] += comp[fu];  
    } 
    n_edges.push_back({u, v, w}); 
   }
   int mx = 0; 
   for(int i = 0; i < N; i++) { 
    mx = max(mx, comp[i]); 
   }
   if(mx < N) { 
    // have to take this bit 
    ans += (1 << b); 
   } else if (mx == N) { 
    edges.swap(n_edges); 
   }
  }
  cout << ans << '\n'; 
 }
 return 0; 
}