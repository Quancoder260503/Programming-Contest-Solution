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

void solve() {
  vector<int>a(8), b(8); 
  for(int i = 0; i < 8; i++) { 
   cin >> b[i]; 
  }
  for(int i = 0; i < 8; i++) { 
   cin >> a[i]; 
  }
  MaxFlow dinic(2 * 8 + 2); 
  int src = 16, sink = 17; 
  for(int i = 0; i < 8; i++) { 
   dinic.addEdge(src, i, a[i]); 
   dinic.addEdge(i + 8, sink, b[i]); 
  }
  dinic.addEdge(0, 8, oo); // O negative
  dinic.addEdge(1, 8, oo); // O positve
  dinic.addEdge(1, 9, oo); 
  dinic.addEdge(2, 8, oo);  // A negative
  dinic.addEdge(2, 10, oo); 
  dinic.addEdge(3, 8,  oo); // A positve
  dinic.addEdge(3, 9,  oo); 
  dinic.addEdge(3, 10, oo); 
  dinic.addEdge(3, 11, oo); 
  dinic.addEdge(4, 8, oo); // B negative
  dinic.addEdge(4, 12, oo); 
  dinic.addEdge(5, 8, oo); // B positive
  dinic.addEdge(5, 9, oo);    
  dinic.addEdge(5, 12, oo); 
  dinic.addEdge(5, 13, oo); 
// AB negative
  for(int i = 8; i < 16; i += 2) { 
   dinic.addEdge(6, i, oo); 
  }
// AB positive
  for(int i = 8; i < 16; i++) { 
    dinic.addEdge(7, i, oo); 
  }
  cout << dinic.getMaxFlow(src, sink); 
  return; 
}

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);
 solve(); 
 return 0; 
}