#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int64_t oo = 1000000000000000;

struct Edge {
  int a, b; 
  int64_t cap, flow;
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
  void addEdge(int a, int b, int64_t cap) {
  ///  cout << a << " " << b << " " << cap << '\n'; 
    Edge e1 = {a, b, cap, 0};
    Edge e2 = {b, a, 0, 0};
    g[a].push_back((int)e.size());
    e.push_back(e1);
    g[b].push_back((int)e.size());
    e.push_back(e2);
  }
  int64_t getMaxFlow(int _s, int _t) {
    s = _s;
    t = _t;
    int64_t flow = 0;
    for (;;) {
      if (!bfs()) break;
      std::fill(ptr.begin(), ptr.end(), 0);
      while (int64_t pushed = dfs(s, oo)) flow += pushed;
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

  int64_t dfs(int v, int64_t flow) {
    if (!flow) return 0;
    if (v == t) return flow;
    for (; ptr[v] < (int)g[v].size(); ++ptr[v]) {
      int id = g[v][ptr[v]], to = e[id].b;
      if (d[to] != d[v] + 1) continue;
      int64_t pushed = dfs(to, min(flow, e[id].cap - e[id].flow));
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
  int N, M, K;
  cin >> N; 
  vector<vector<int>>g(N);
  vector<int>v(N), c(N);  
  MaxFlow dinic(N + 2); 
  int src = N, sink = src + 1; 
  for(int i = 0, x; i < N; i++) { 
   cin >> v[i] >> c[i] >> x; 
   g[i].resize(x); 
   for(auto &y : g[i]) { 
    cin >> y; 
    --y; 
   }
  }
  int64_t ret = 0; 
  for(int i = 0; i < N; i++) { 
   if(v[i] >= c[i]) { 
    dinic.addEdge(src, i, v[i] - c[i]); 
    ret += v[i] - c[i]; 
   } else { 
    dinic.addEdge(i, sink, -v[i] + c[i]); 
   }
   for(auto &y : g[i]) { 
  //  cout << y << " " << i << '\n'; 
    dinic.addEdge(y, i, oo); 
   }
  }
  cout << ret - dinic.getMaxFlow(src, sink) << '\n'; 
  return 0; 
}
