#include "bits/stdc++.h"

using namespace std;

const int oo = 1e7; 
const int maxf = 3e5 + 2; 
const int LOG = 18; 

#define sz(x) int(x.size())
#define rep(i, j, k) for (int i = j; i < k; i++)

vector<vector<int>>graph;  
int dep[maxf], up[LOG][maxf], jmp[LOG][maxf], vis[maxf], par[maxf], comp_sz[maxf]; 

struct DirectedDfs {
  vector<vector<int>> g;
  int n;
  vector<int> num, low, current, S;
  int counter;
  vector<int> comp_ids;
  vector<vector<int>> scc;

  DirectedDfs(const vector<vector<int>>& _g)
      : g(_g),
        n(g.size()),
        num(n, -1),
        low(n, 0),
        current(n, 0),
        counter(0),
        comp_ids(n, -1) {
    for (int i = 0; i < n; i++) {
      if (num[i] == -1) dfs(i);
    }
  }

  void dfs(int u) {
    low[u] = num[u] = counter++;
    S.push_back(u);
    current[u] = 1;
    for (auto v : g[u]) {
      if (num[v] == -1) dfs(v);
      if (current[v]) low[u] = min(low[u], low[v]);
    }
    if (low[u] == num[u]) {
      scc.push_back(vector<int>());
      while (1) {
        int v = S.back();
        S.pop_back();
        current[v] = 0;
        scc.back().push_back(v);
        comp_ids[v] = ((int)scc.size()) - 1;
        if (u == v) break;
      }
    }
  }

  // build DAG of strongly connected components
  // Returns: adjacency list of DAG
  std::vector<std::vector<int>> build_scc_dag() {
    std::vector<std::vector<int>> dag(scc.size());
    for (int u = 0; u < n; u++) {
      int x = comp_ids[u];
      for (int v : g[u]) {
        int y = comp_ids[v];
        if (x != y) {
          dag[y].push_back(x);
        }
      }
    }
    return dag;
  }
};

void dfs(int u, int p) {
  vis[u] = true;
  for (int i = 1; i < LOG; i++) {
    up[i][u] = up[i - 1][up[i - 1][u]];
  }
  for (auto v : graph[u]) {
    if (v == p) continue;
    dep[v] = dep[up[0][v] = u] + 1;
    dfs(v, u);
  }
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
int getDist(int u, int v) { return dep[u] + dep[v] - 2 * dep[LCA(u, v)]; }

int find(int u) { 
  return u == par[u] ? u : par[u] = find(par[u]); 
}

void unite(int u, int v) { 
  int ku = find(u), kv = find(v); 
  if(ku == kv) return;
  if(comp_sz[ku] < comp_sz[kv]) swap(ku, kv); 
  comp_sz[ku] += comp_sz[kv]; 
  par[kv] = ku; 
  return; 
}

int jump(int x, int d) {
  for(int i = 0; i < LOG; i++) { 
    if(d & (1 << i)) { 
      x = jmp[i][x]; 
    }
  } 
  return x; 
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int N, Q; 
  cin >> N >> Q; 
  vector<vector<int>>g(N); 
  iota(par, par + N, 0); 
  fill(comp_sz, comp_sz + N, 1); 
  for(int i = 0, x; i < N; i++) { 
    cin >> x; 
    jmp[0][i] = x; 
    g[i].push_back(x); 
    unite(i, x); 
  }
  for(int j = 1; j < LOG; j++) { 
    for(int i = 0; i < N; i++) { 
      jmp[j][i] = jmp[j - 1][jmp[j - 1][i]]; 
    }
  }
  vector<int>dist(N); 
  DirectedDfs Scc(g);
  graph = Scc.build_scc_dag(); 
  for(int i = 0; i < sz(Scc.scc); i++) { 
    for(int j = 1; j < sz(Scc.scc[i]); j++) { 
      int u = Scc.scc[i][j], v = Scc.scc[i][j - 1]; 
      dist[u] = dist[v] + 1; 
    }
  }
  for(int i = 0; i < sz(graph); i++) { 
    if(vis[i]) continue; 
    dfs(i, -1); 
  } 
  for(int i = 0, u, v; i < Q; i++) { 
    cin >> u >> v; 
    if(find(u) != find(v)) { 
      cout << -1 << '\n'; 
      continue; 
    }
    int id_u = Scc.comp_ids[u], id_v = Scc.comp_ids[v]; 
    if(sz(Scc.scc[id_u]) > 1) { 
      if(id_u == id_v) { 
        cout << (dist[u] - dist[v] + sz(Scc.scc[id_u])) % sz(Scc.scc[id_u])<< '\n'; 
      }
      else { 
        cout << -1 << '\n'; 
      }
    }
    else { 
      if(sz(Scc.scc[id_v]) > 1) { 
        int c = LCA(id_u, id_v); 
        if(c == id_v) {
          int cc = getDist(id_u, id_v); 
          int start = jump(u, cc); 
          if(Scc.comp_ids[start] == Scc.comp_ids[v]){ 
            cout << cc + (dist[start] - dist[v] + sz(Scc.scc[id_v])) % sz(Scc.scc[id_v])<< '\n';
          } 
          else cout << -1 << '\n';  
        }
        else { 
          cout << -1 << '\n'; 
        }
      }
      else { 
        int c = LCA(id_u, id_v); 
        cout << (c == id_v ? getDist(c, id_u) : -1) << '\n'; 
      }
    }
  } 
  return 0;
}