#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int oo = 1000000000;

struct Edge {
  int a, b, cap, flow, id;
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

  void addEdge(int a, int b, int cap, int id) {
    Edge e1 = {a, b, cap, 0, id};
    Edge e2 = {b, a, 0, 0, id};
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
  void getMinCut(int s, int t, vector<int>&left, vector<int>&right) {
    bfs();
    for(int i = 0; i < n; i++) { 
      if (d[i] >= 0) {
        left.push_back(i); 
      } 
      else { 
        right.push_back(i); 
      } 
    }
    return;
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
  int N, M, src, sink; 
  cin >> N >> M; 
  vector<array<int, 3>>edge;
  for(int i = 0, u, v, cost; i < M; i++) { 
    cin >> u >> v >> cost; 
    edge.push_back({u - 1, v - 1, cost}); 
  } 
  cin >> src >> sink;
  --src, --sink;
  auto func = [&](int del) { 
   int ret = 0; 
   MaxFlow dinic(N); 
   for(int ind = 0; ind < M; ind++) {
    auto [u, v, cost] = edge[ind]; 
    ret += cost; 
    if(ind == del) continue; 
    dinic.addEdge(u, v, cost, ind);
    dinic.addEdge(v, u, cost, ind); 
   }
   int flow = dinic.getMaxFlow(src, sink);
   vector<int>S, T; 
   dinic.getMinCut(src, sink, S, T); 
   bool s = find(S.begin(), S.end(), edge[del][0]) != S.end();
   bool e = find(S.begin(), S.end(), edge[del][1]) != S.end();
  // cout << s << " " << e << '\n'; 
   if(s == e) return -1; 
   return ret - flow; 
  }; 
  int ret = 0; 
  for(int i = 0; i < M; i++) { 
   ret = max(ret, func(i)); 
  // break; 
  } 
  cout << ret << '\n';
  return 0;
}
