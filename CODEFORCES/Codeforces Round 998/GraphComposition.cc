#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define int64_t long long

const int MOD = 998244353; 

class GraphComposition { 
  public:   
   void solve() { 
    int N, M1, M2;
    cin >> N >> M1 >> M2; 
    vector<int>par(N); 
    iota(par.begin(), par.end(), 0); 
    function<int(int)> F = [&](int u) { 
     return par[u] == u ? u : par[u] = F(par[u]); 
    }; 
    vector<pair<int, int>>edges, edges2; 
    for(int i = 0, u, v; i < M1; i++) { 
     cin >> u >> v; 
     --u, --v; 
     edges.push_back({u, v}); 
    }
    for(int i = 0, u, v; i < M2; i++) { 
     cin >> u >> v;
     --u, --v; 
     if(F(u) == F(v)) continue; 
     par[F(u)] = F(v); 
    }
    int ans = 0, cc_1 = 0, cc_2 = 0; 
    for(int i = 0; i < N; i++) { 
     cc_1 += (F(i) == i); 
    } 
    for(int i = 0; i < M1; i++) {
     if(F(edges[i].first) != F(edges[i].second)) { 
      ans++; 
     } else { 
       edges2.push_back(edges[i]); 
     }
    }
    iota(par.begin(), par.end(), 0); 
    for(auto [u, v] : edges2) { 
     if(F(u) == F(v)) continue; 
     par[F(u)] = F(v); 
    }
    for(int i = 0; i < N; i++) { 
     cc_2 += (F(i) == i); 
    }
    cout << ans + abs(cc_1 - cc_2) << '\n'; 
    return; 
   }
 private: 
};


int main(void) {  
 int T; 
 GraphComposition problem; 
 for(cin >> T; T--; ) { problem.solve(); }
 return 0; 
}