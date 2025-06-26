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

int main(void) {
 ios_base::sync_with_stdio(false);  
 cin.tie(0); 
 cout.tie(0); 
 int N, M; 
 cin >> N >> M; 
 vector<vector<int>>g(N); 
 auto bfs = [&](int src) { 
  vector<int>dist(N, oo);
  queue<int>q;  
  dist[src] = 0;
  q.push(src); 
  while(sz(q)) { 
   int u = q.front(); 
   q.pop(); 
   for(auto v : g[u]) { 
    if(dist[v] < oo) continue; 
    dist[v] = dist[u] + 1; 
    q.push(v); 
   }
  }
  return dist; 
 }; 
 vector<int>a(N), b(N); 
 vector<int>cities, shelters; 
 for(int i = 0; i < N; i++) { 
  cin >> a[i]; 
 }
 for(int i = 0; i < N; i++) {
  cin >> b[i];
 }
 for(int i = 0, u, v; i < M; i++) { 
  cin >> u >> v; 
  g[u].push_back(v); 
  g[v].push_back(u); 
 }
 queue<int>q; 
 vector<int>dp(N, oo); 
 for(int i = 0; i < N; i++) { 
  if(b[i] == -1) { 
    dp[i] = 0; 
    q.push(i); 
  }
 }
 while(sz(q)) { 
  int u = q.front(); 
  q.pop();
  for(auto v : g[u]) { 
   if(dp[v] > dp[u] + 1) { 
    dp[v] = dp[u] + 1; 
    q.push(v); 
   }
  }
 }
 int ans = 0; 
 for(int i = 0; i < N; i++) { 
  if(dp[i] == oo) { 
   ans += a[i]; 
  }
 }
 for(int i = 0; i < N; i++) { 
  if(dp[i] < oo && a[i] > 0) cities.push_back(i); 
 }
 for(int i = 0; i < N; i++) {
  if(dp[i] < oo && b[i] > 0) shelters.push_back(i);  
 }
 MaxFlow dinic(sz(cities) + sz(shelters) + 2); 
 int src = sz(cities) + sz(shelters); 
 int sink = src + 1;
 for(int j = 0; j < sz(cities); j++) { 
  int u = cities[j]; 
  dinic.addEdge(src, j, a[u]); 
 }
 for(int i = 0; i < sz(shelters); i++) { 
  int u = shelters[i]; 
  vector<int>dist = bfs(u);
  dinic.addEdge(sz(cities) + i, sink, b[u]);  
  for(int j = 0; j < sz(cities); j++) { 
   int v = cities[j]; 
   if(dist[v] < dp[u]) { 
    dinic.addEdge(j, sz(cities) + i, oo); 
   }
  }
 }
 
 ans += dinic.getMaxFlow(src, sink); 
 cout << ans << '\n'; 
 return 0; 
}