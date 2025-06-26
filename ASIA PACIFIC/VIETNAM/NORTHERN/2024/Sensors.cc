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
 int W, L, N; 
 cin >> L >> W >> N; 
 vector<array<int, 2>>arr(N); 
 for(int i = 0; i < N; i++) { 
  cin >> arr[i][0] >> arr[i][1]; 
 }
 int src = 2 * N, sink = 2 * N + 1; 
 MaxFlow dinic(2 * N + 2); 
 auto get_dist = [&](int x, int y) { 
  return 1LL * x * x + 1LL * y * y; 
 }; 
 for(int i = 0; i < N; i++) { 
  for(int j = i + 1; j < N; j++) { 
   int64_t dist = get_dist(arr[i][0] - arr[j][0], arr[i][1] - arr[j][1]); 
   if(dist <= 200LL * 200) {
    dinic.addEdge(N + j, i, 1); 
    dinic.addEdge(N + i, j, 1); 
   }
  }
 }
 for(int i = 0; i < N; i++) {
  dinic.addEdge(i, N + i, 1);  
  if(arr[i][1] <= 100) { 
    dinic.addEdge(src, i, 1); 
  }
  if(W - arr[i][1] <= 100) {
    dinic.addEdge(N + i, sink, 1); 
  }
 }
 cout << dinic.getMaxFlow(src, sink) << '\n'; 
 return 0; 
}