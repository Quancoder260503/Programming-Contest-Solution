#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int maxf = 1e5 + 3;
const int LOG = 23;

vector<int> adj[maxf];
int up[LOG][maxf], dep[maxf], a[maxf], in[maxf], out[maxf], ret[maxf], N, Q, timer = 1;
vector<array<int, 3>>query[maxf]; 

void dfs(int u, int p) {
  in[u] = timer++; 
  for (int i = 1; i < LOG; i++) {
    up[i][u] = up[i - 1][up[i - 1][u]];
  }
  for (int i = 0; i < adj[u].size(); i++) {
    int v = adj[u][i];
    if (v == p) continue;
    dep[v] = dep[up[0][v] = u] + 1;
    dfs(v, u);
  }
  out[u] = timer - 1; 
  return;
}
int LCA(int u, int v) {
  if (dep[u] < dep[v]) swap(u, v);
  int d = dep[u] - dep[v];
  for (int i = 0; i < LOG; i++) {
    if (d & (1 << i)) {
      u = up[i][u];
    }
  }
  if (u == v) return u;
  for (int i = LOG - 1; i >= 0; i--) {
    int tu = up[i][u], tv = up[i][v];
    if (tu != tv) u = tu, v = tv;
  }
  return up[0][u];
}
int dist(int u, int v) { return dep[u] + dep[v] - 2 * dep[LCA(u, v)]; }

struct FT {
  int N;
  vector<int> bit;
  FT(int _N) {
    N = _N;
    bit.resize(N);
  }
  int sum(int i) {
    int c = 0;
    for (++i; i > 0; i -= (i & -i)) {
      c = c + bit[i];
    }
    return c;
  }
  void update(int i, int dif) {
    for (++i; i < N; i += (i & -i)) {
      bit[i] = dif + bit[i];
    }
  }
};

int main(void) {  
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 cin >> N >> Q; 
 for(int i = 1; i <= N; i++) { 
  cin >> a[i]; 
  query[a[i]].push_back({-1, -1, i}); 
 }
 for(int i = 0, u, v; i < N - 1; i++) { 
  cin >> u >> v; 
  adj[u].push_back(v); 
  adj[v].push_back(u); 
 }
 dfs(1, 0); 
 for(int i = 0, u, v, c; i < Q; i++) { 
  cin >> u >> v >> c; 
  query[c].push_back({i, u, v}); 
 }
 FT fenw(N + 7); 
 for(int i = 1; i <= N; i++) { 
  for(auto [ind, u, v] : query[i]) { 
   if(ind == -1) { 
    fenw.update(in[v], 1);
    fenw.update(out[v] + 1, -1); 
   } else { 
    int anc = LCA(u, v);
    ret[ind] = fenw.sum(in[u]) + fenw.sum(in[v]) - 2 * fenw.sum(in[anc]) + (a[anc] == i); 
   }
  }
  for(auto [ind, u, v] : query[i]) { 
   if(ind == -1) { 
    fenw.update(in[v], -1);
    fenw.update(out[v] + 1, 1); 
   }
  }
 }
 for(int i = 0; i < Q; i++) { 
  //cout << ret[i] << '\n'; 
  cout << (ret[i] > 0 ? 1 : 0); 
 }
 cout << '\n'; 
 return 0; 
}