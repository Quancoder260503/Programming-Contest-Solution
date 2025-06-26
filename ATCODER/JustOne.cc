#include "bits/stdc++.h"

using namespace std;

#define int64_t long long
#define sz(x) int(x.size())

const int MOD = 998244353; 

struct UndirectedDfs {
  vector<vector<int>> g;
  int n;
  vector<int> low, num, parent;
  vector<bool> is_articulation;
  int counter, root, children;
 
  vector<pair<int, int>> bridges;
  vector<int> articulation_points;
  map<pair<int, int>, int> cnt_edges;
 
  UndirectedDfs(const vector<vector<int>>& _g)
      : g(_g),
        n(g.size()),
        low(n, 0),
        num(n, -1),
        parent(n, 0),
        is_articulation(n, false),
        counter(0),
        children(0) {
    for (int u = 0; u < n; u++) {
      for (int v : g[u]) {
        cnt_edges[{u, v}] += 1;
      }
    }
    for (int i = 0; i < n; ++i)
      if (num[i] == -1) {
        root = i;
        children = 0;
        dfs(i);
        is_articulation[root] = (children > 1);
      }
    for (int i = 0; i < n; ++i)
      if (is_articulation[i]) articulation_points.push_back(i);
  }
 
 private:
  void dfs(int u) {
    low[u] = num[u] = counter++;
    for (int v : g[u]) {
      if (num[v] == -1) {
        parent[v] = u;
        if (u == root) children++;
        dfs(v);
        if (low[v] >= num[u]) is_articulation[u] = true;
        if (low[v] > num[u]) {
          if (cnt_edges[{u, v}] == 1) {
            bridges.push_back(make_pair(u, v));
          }
        }
        low[u] = min(low[u], low[v]);
      } else if (v != parent[u])
        low[u] = min(low[u], num[v]);
    }
  }
};
// }}}

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N, M; 
 cin >> N >> M; 
 vector<vector<int>>graph(N); 
 vector<pair<int, int>>edge; 
 vector<int>par(N);
 iota(par.begin(), par.end(), 0); 
 function<int(int)> F = [&](int x) { 
  return x == par[x] ? x : par[x] = F(par[x]); 
 }; 
 vector<int>deg(N), comp_sz(N, 1);  
 for(int i = 0, u, v; i < M; i++) {
  cin >> u >> v; 
  --u, --v; 
  graph[u].push_back(v); 
  graph[v].push_back(u); 
  edge.push_back({u, v});
  deg[u]++, deg[v]++; 
 }
 for(int i = 0; i < N; i++) { 
  if(deg[i] == 0) { 
   cout << 0 << '\n'; 
   return 0; 
  }
 }
 fill(deg.begin(), deg.end(), 0); 
 UndirectedDfs cc(graph); 
 set<pair<int, int>>bridges(cc.bridges.begin(), cc.bridges.end()); 
 for(auto [u, v] : edge) { 
  if(!bridges.count({u, v}) && !bridges.count({v, u})) { 
   deg[u]++; 
   deg[v]++; 
   if(F(u) == F(v)) continue; 
   comp_sz[F(v)] += comp_sz[F(u)]; 
   par[F(u)] = F(v); 
  }
 }
 int cnt = 0; 
 for(int i = 0; i < N; i++) { 
  cnt += (deg[i] > 2); 
 }
 if(cnt > 0) { 
  cout << 0 << '\n'; 
  return 0; 
 }
 int cycles = 0; 
 set<int>root; 
 for(int i = 0; i < N; i++) { 
  if(comp_sz[F(i)] > 1) { 
   root.insert(F(i));
  }
 }
 if(!sz(root)) { 
  cout << 0 << '\n'; 
  return 0; 
 }
 vector<int>visited(N); 
 function<void(int)> dfs = [&](int u) { 
  visited[u] = true; 
  for(auto v : graph[u]) { 
    if(!visited[v]) { 
     dfs(v); 
    }
  }
  return; 
 }; 
 for(auto rt : root) {
  if(visited[rt]) { 
    cout << 0 << '\n'; 
    return 0; 
  } else { 
    dfs(rt);    
  }
 }
 int64_t ret = 1; 
 for(int i = 0; i < sz(root); i++) { 
  ret = ret * 2 % MOD; 
 }
 cout << ret << '\n'; 
 return 0; 
}