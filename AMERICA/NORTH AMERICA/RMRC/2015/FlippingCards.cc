#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int maxf = 2e5 + 10; 
vector<int>g[maxf];
int vis[maxf], id[maxf];  

void dfs(int u, int comp_num) { 
   vis[u] = true; 
   id[u] = comp_num; 
   for(auto v : g[u]) if(!vis[v]){ 
    dfs(v, comp_num); 
   }
   return; 
}

int main(void) { 
  ios_base::sync_with_stdio(0); 
  cin.tie(0); 
  cout.tie(0); 
  int Q; 
  cin >> Q; 
  for(int iter = 0, N; iter < Q; iter++) { 
    cin >> N; 
    for(int i = 0; i < 2 * N; i++) { 
      g[i].clear(); 
      vis[i] = id[i] = 0; 
    }
    vector<pair<int, int>>edge; 
    for(int i = 0, x, y; i < N; i++) {
      cin >> x >> y; 
      --x, --y; 
      g[x].push_back(y); 
      g[y].push_back(x);
      edge.push_back({x, y});  
    } 
    int ret = true, comp_num = 0; 
    for(int i = 0; i < 2 * N; i++) if(!vis[i]) { 
      dfs(i, comp_num++); 
    }
    vector<int>par(2 * N), ctr(comp_num);
    iota(par.begin(), par.end(), 0);  
    function<int(int)> F = [&](int u) { return par[u] == u ? u : par[u] = F(par[u]); }; 
    for(int i = 0; i < N; i++) { 
      auto [u, v] = edge[i]; 
      if(F(u) == F(v)) { 
        ctr[id[u]]++; 
        if(ctr[id[u]] > 1) { ret = false; break; }
      }
      else { 
        par[F(u)] = F(v); 
      }
    }
    cout << (ret ? "possible" : "impossible") << '\n'; 
  }
  return 0; 
}

