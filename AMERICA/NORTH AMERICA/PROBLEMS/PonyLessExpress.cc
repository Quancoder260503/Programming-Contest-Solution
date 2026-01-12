#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())
#define ll long long 

const ll oo = 1e15; 

ll hungarian(const vector<vector<ll>> &a) { 
  if(a.empty()) return 0;  
  int n = sz(a) + 1, m = sz(a[0]) + 1; 
  vector<ll> u(n), v(m), p(m), ans(n - 1); 
  for(int i = 1; i < n; i++) { 
   p[0] = i; 
   int j0 = 0; 
   vector<ll>dist(m, LLONG_MAX), pre(m, -1); 
   vector<bool>done(m + 1); 
   do { 
    done[j0] = true; 
    ll i0 = p[j0], j1, delta = LLONG_MAX; 
    for(int j = 1; j < m; j++) if(!done[j]) {
     auto curr = a[i0 - 1][j - 1] - u[i0] - v[j]; 
     if(curr < dist[j]) dist[j] = curr, pre[j] = j0; 
     if(dist[j] < delta) delta = dist[j], j1 = j; 
    }
    for(int j = 0; j < m; j++) {  
      if(done[j]) u[p[j]] += delta, v[j] -= delta; 
      else dist[j] -= delta; 
    }
    j0 = j1; 
   } while(p[j0]);
   while(j0) { 
    int j1 = pre[j0]; 
    p[j0] = p[j1]; 
    j0 = j1; 
   } 
  }
  for(int j = 1; j < m; j++) ans[p[j] - 1] = j - 1; 
  return -v[0]; 
}

void dfs(int u, vector<vector<ll>>&cost, const vector<array<ll, 2>> &stats, const vector<vector<int>> &g) { 
  for(auto v : g[u]) { 
   if(cost[v][1] == oo) { 
    dfs(v, cost, stats, g);
   }  
  }
  if(sz(g[u]) == 0) { 
   for(int day = 0; day < sz(cost[u]); day++) { 
    cost[u][day] = 1LL * stats[u][0] * (stats[u][1] - day) * (stats[u][1] - day); 
   }
   return; 
  }
  for(int day = 0; day + sz(g[u]) < sz(cost); day++) { 
   vector<vector<ll>>hung_matrix(sz(g[u]), vector<ll>(sz(g[u]))); 
   for(int i = 0; i < sz(g[u]); i++) { 
    for(int j = 0; j < sz(g[u]); j++) { 
     hung_matrix[i][j] = cost[g[u][i]][day + j + 1]; 
    }
  }
   auto cost_val = hungarian(hung_matrix);
   cost[u][day] = 1LL * stats[u][0] * (stats[u][1] - day) * (stats[u][1] - day) + cost_val; 
  }
  return;  
} 

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int n; 
  cin >> n;
  vector<int>par(n + 1); 
  vector<vector<int>>g(n + 1); 
  vector<array<ll, 2>> stats(n + 1); 
  for(int i = 1; i <= n; i++) { 
   cin >> stats[i][0] >> stats[i][1] >> par[i]; 
   g[par[i]].push_back(i);   
  }
  vector<vector<ll>>cost(n + 1, vector<ll>(n + 1, oo)); 
  dfs(0, cost, stats, g); 
  cout << cost[0][0] << '\n'; 
  return 0;
}
