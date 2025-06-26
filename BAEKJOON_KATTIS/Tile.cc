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
  vector<string>g; 
  string c; 
  while(getline(cin, c)) {
   if(c.empty()) break; 
   g.push_back(c);  
  }
  if(sz(g) == 0) { 
    exit(0); 
  }
  int N = sz(g), M = sz(g[0]); 
  const int dx[4] = {0, 0, -1, 1}; 
  const int dy[4] = {-1, 1, 0, 0};
  auto inBound = [&](int a, int b) { 
   return 0 <= a && a < N && 0 <= b && b < M; 
  }; 
  MaxFlow dinic(2 * N * M + 2); 
  int src = 2 * N * M, sink = 2 * N * M + 1; 
  for(int i = 0; i < N; i++) { 
   for(int j = 0; j < M; j++) { 
    dinic.addEdge(i * M + j, N * M + i * M + j, 1); 
    if(g[i][j] == 'W') {
     dinic.addEdge(src, i * M + j, 1); 
     for(int dir = 0; dir < 4; dir++) { 
      int fx = i + dx[dir], fy = j + dy[dir]; 
      if(inBound(fx, fy) && g[fx][fy] == 'I') { 
       dinic.addEdge(N * M + i * M + j, fx * M + fy, 1); 
      }
     }
    } else if(g[i][j] == 'I') { 
      for(int dir = 0; dir < 4; dir++) { 
      int fx = i + dx[dir], fy = j + dy[dir]; 
      if(inBound(fx, fy) && g[fx][fy] == 'N') { 
       dinic.addEdge(N * M + i * M + j, fx * M + fy, 1); 
      }
     }
    } else { 
      dinic.addEdge(i * M + j + N * M, sink, 1); 
    }
   }
  }
  cout << dinic.getMaxFlow(src, sink) << '\n'; 
  return; 
}

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);
 while(true) { 
  solve(); 
 }
 return 0; 
}