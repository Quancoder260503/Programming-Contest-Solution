#include "bits/stdc++.h"

using namespace std;

vector<int>a, b, vis;   
vector<vector<int>>g, dyn; 
int N, M, R, B; 

void doit(int u, int sign, int &sz, int &cost) { 
   if(vis[u]) return; 
   vis[u] = true; 
   sz += sign; 
   cost += (u < N ? a[u] : b[u - N]); 
   for(auto v : g[u]) if(!vis[v]) { 
    doit(v, -sign, sz, cost); 
   }
   return; 
}

void solve(vector<pair<int, int>>&cc, int p) {
  int G = cc.size(); 
  dyn.resize(G + 1, vector<int>(B + 1, 0)); 
  for(int i = 0; i < cc.size(); i++) { 
    for(int j = 0; j <= B; j++) { 
      dyn[i + 1][j] = dyn[i][j]; 
      if(j - cc[i].second < 0) continue; 
      dyn[i + 1][j] = max(dyn[i + 1][j], dyn[i][j - cc[i].second] + cc[i].first); 
    }
  } 
  cout << p + dyn[G][B] << " "; 
  return; 
}

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  cin >> N >> M >> R >> B;
  a.resize(N);
  b.resize(M);  
  g.resize(N + M);
  vis.resize(N + M);  
  for(int i = 0; i < N; i++) { 
    cin >> a[i]; 
  } 
  for(int i = 0; i < M; i++) { 
    cin >> b[i]; 
  }
  for(int i = 0, u, v; i < R; i++) { 
    cin >> u >> v;
    --u, --v; 
    g[u].push_back(v + N); 
    g[v + N].push_back(u); 
  }
  vector<pair<int, int>>cc; 
  for(int i = 0; i < N + M; i++) { 
    if(vis[i]) continue; 
    int sz = 0, cost = 0; 
    doit(i, (i < N ? -1 : 1), sz, cost); 
    cc.push_back({sz, cost}); 
  }
  solve(cc, N); 
  for(int i = 0; i < cc.size(); i++) { 
    cc[i].first = -cc[i].first; 
  } 
  solve(cc, M); 
  return 0; 
}