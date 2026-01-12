#include "bits/stdc++.h"

using namespace std;

const int maxn = 3e5 + 10;

int n, m, q;
int timeDfs = 0;
int low[maxn], num[maxn], tail[maxn];
int depth[maxn];
bool joint[maxn];
vector<pair<int, int>> g[maxn];
int marked[maxn]; 

void dfs(int u, int pre) {
  int child = 0;
  num[u] = low[u] = ++timeDfs;
  for (auto &[v, ind] : g[u]) {
    if (v == pre) continue;
    if (!num[v]) {
      child++;
      depth[v] = depth[u] + 1;
      dfs(v, u);
      low[u] = min(low[u], low[v]);
      if (u == pre) {
        if (child > 1) joint[u] = true;
      } else if (low[v] >= num[u])
        joint[u] = true;
    } else { 
      marked[ind] = 1; 
    //  cout << u << " " << v << " " << ind << '\n'; 
      low[u] = min(low[u], num[v]);
    } 
  }
  tail[u] = timeDfs;
  return; 
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> m;
  vector<pair<int, int>>edge; 
  for (int i = 1; i <= m; i++) {
    int u, v;
    cin >> u >> v;
    g[u].push_back({v, i});
    g[v].push_back({u, i});
    edge.push_back({u, v}); 
  }
  for(int i = 1; i <= n; i++) { 
   if(!num[i]) { 
    dfs(i, i);
   } 
  }  
  for(int i = 1; i <= m; i++) { 
   auto [u, v] = edge[i - 1];   
   if(!marked[i]) { 
    cout << (num[u] <= num[v] ? 0 : 1); 
   } else {
    cout << (num[u] >= num[v] ? 0 : 1); 
   }
  }
  cout << '\n'; 
  return 0; 
}
