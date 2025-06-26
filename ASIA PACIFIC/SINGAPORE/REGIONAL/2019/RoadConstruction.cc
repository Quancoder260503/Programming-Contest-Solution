#include "bits/stdc++.h"
 
using namespace std;
 
#define sz(x) int(x.size())
 
const int oo = 1000000000;
 
struct Edge {
  int a, b, cap, flow;
};
 
struct MaxFlow {
  int n, s, t;
  vector<int> d, ptr, q;
  vector<Edge> e;
  vector<vector<int>> g;
 
  MaxFlow(int _n) : n(_n), d(_n), ptr(_n), q(_n), g(_n) {
    e.clear();
    for (int i = 0; i < n; i++) {
      g[i].clear();
      ptr[i] = 0;
    }
  }
 
  void addEdge(int a, int b, int cap) {
    Edge e1 = {a, b, cap, 0};
    Edge e2 = {b, a, 0, 0};
    g[a].push_back((int)e.size());
    e.push_back(e1);
    g[b].push_back((int)e.size());
    e.push_back(e2);
  }
  int getMaxFlow(int _s, int _t) {
    s = _s;
    t = _t;
    int flow = 0;
    for (;;) {
      if (!bfs()) break;
      std::fill(ptr.begin(), ptr.end(), 0);
      while (int pushed = dfs(s, oo)) flow += pushed;
    }
    return flow;
  }
 
 private:
  bool bfs() {
    int qh = 0, qt = 0;
    q[qt++] = s;
    std::fill(d.begin(), d.end(), -1);
    d[s] = 0;
 
    while (qh < qt && d[t] == -1) {
      int v = q[qh++];
      for (int i = 0; i < (int)g[v].size(); i++) {
        int id = g[v][i], to = e[id].b;
        if (d[to] == -1 && e[id].flow < e[id].cap) {
          q[qt++] = to;
          d[to] = d[v] + 1;
        }
      }
    }
    return d[t] != -1;
  }
 
  int dfs(int v, int flow) {
    if (!flow) return 0;
    if (v == t) return flow;
    for (; ptr[v] < (int)g[v].size(); ++ptr[v]) {
      int id = g[v][ptr[v]], to = e[id].b;
      if (d[to] != d[v] + 1) continue;
      int pushed = dfs(to, min(flow, e[id].cap - e[id].flow));
      if (pushed) {
        e[id].flow += pushed;
        e[id ^ 1].flow -= pushed;
        return pushed;
      }
    }
    return 0;
  }
};
 
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
 
 
int main() {
 ios_base::sync_with_stdio(false); 
 int N, M; 
 cin >> N >> M; 
 vector<vector<int>>g(N); 
 vector<vector<int>>graph(N); 
 vector<int>coord, a(N); 
 for(int i = 0, _size; i < N; i++) { 
  cin >> a[i] >> _size; 
  --a[i]; 
  graph[i].push_back(a[i]); 
  graph[a[i]].push_back(i); 
  g[i].resize(_size); 
  for(auto &v : g[i]) { 
   cin >> v; 
   coord.push_back(v); 
  } 
 } 
 sort(coord.begin(), coord.end()); 
 coord.erase(unique(coord.begin(), coord.end()), coord.end());
 UndirectedDfs cc(graph); 
 vector<int>b(M); 
 vector<vector<int>> works(sz(coord)); 
 for(int i = 0; i < M; i++) { 
  cin >> b[i]; 
  auto it = lower_bound(coord.begin(), coord.end(), b[i]); 
  if(*it == b[i]) { 
   works[it - coord.begin()].push_back(i); 
  } 
 }
 set<pair<int, int>>bridges; 
 for(auto [u, v] : cc.bridges) { 
  bridges.insert({u, v}); 
  bridges.insert({v, u}); 
 }
 vector<int>par(N); 
 iota(par.begin(), par.end(), 0); 
 function<int(int)> F = [&](int u) { 
  return u == par[u] ? u : par[u] = F(par[u]); 
 };  
 for(int i = 0; i < N; i++) { 
  if(!bridges.count({i, a[i]}) && !bridges.count({a[i], i})) { 
   par[F(i)] = F(a[i]);  
  }
 }
 int ctr = 0; 
 vector<int>position; 
 for(int i = 0; i < N; i++) { 
  if(F(i) == i) { 
   position.push_back(i); 
  }
 }
 vector<vector<int>>comp(sz(position));
 for(int i = 0; i < N; i++) { 
  int pos = lower_bound(position.begin(), position.end(), F(i)) - position.begin(); 
  comp[pos].push_back(i); 
 }
 int P = sz(coord) + N + sz(position); 
 MaxFlow dinic(P + 2); 
 int src = P, sink = P + 1;
 for(int ind = 0; ind < sz(position); ind++) { 
  dinic.addEdge(src, ind , max(1, sz(comp[ind]) - 1));
 }
 for(int ptr = 0; ptr < sz(position); ptr++) { 
  set<int>distinct; 
  for(auto &x : comp[ptr]) { 
   dinic.addEdge(ptr, sz(position) + x, 1); 
   for(auto &col : g[x]) { 
    int pos = lower_bound(coord.begin(), coord.end(), col) - coord.begin(); 
    dinic.addEdge(sz(position) + x, sz(position) + N + pos, 1); 
   }  
  }
 }
 for(int pos = 0; pos < sz(coord); pos++) { 
  dinic.addEdge(sz(position) + N + pos, sink, sz(works[pos])); 
 }
 int flow = dinic.getMaxFlow(src, sink);  
 vector<pair<int, int>>ret(M, {-1, -1}); 
 for(int i = 0; i < N; i++) { 
  for(auto v : dinic.g[sz(position) + i]) { 
   auto ed = dinic.e[v]; 
   if(ed.a == sz(position) + i && ed.b >= sz(position) + N && ed.flow > 0) { 
    if(sz(works[ed.b - sz(position) - N])) { 
     int workers = works[ed.b - sz(position) - N].back(); 
     ret[workers] = {i, a[i]}; 
     works[ed.b - sz(position) - N].pop_back(); 
    } else { 
      cout << -1 << '\n'; 
      return 0; 
    } 
   }
  }
 }
  // Sanity check 
 iota(par.begin(), par.end(), 0); 
 for(int i = 0; i < M; i++) { 
  if(ret[i].first != -1) {
   par[F(ret[i].first)] = F(ret[i].second); 
  } 
 }
 int dist = 0; 
 for(int i = 0; i < N; i++) { 
  if(F(i) == i) { 
   dist++; 
  }
 }
 if(dist > 1) { 
  cout << "-1\n"; 
  exit(0); 
 }
 for(int i = 0; i < M; i++) { 
  cout << ret[i].first + 1 << " " << ret[i].second + 1 << '\n'; 
 }
 return 0;
}