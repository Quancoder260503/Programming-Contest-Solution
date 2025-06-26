#include "bits/stdc++.h"

using namespace std;

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
  vector<int> getMinCut(int s, int t) {
    bfs();
    vector<int> res;
    for(int i = 0; i < n; i++) if (d[i] >= 0) {
      for (auto e_id : g[i]) {
        int j = e[e_id].b;
        if (d[j] < 0 && e[e_id].cap > 0) {
          res.push_back(e[e_id].id);
        }
      }
    }
    return res;
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
  int N, F;
  cin >> N >> F;
  vector<vector<int>> g(N, vector<int>(N));
  MaxFlow dinic(N);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> g[i][j];
      if (g[i][j] > 0) {
        dinic.addEdge(i, j, g[i][j], i * N + j);
      }
    }
  }
  int src = 0, sink = N - 1;
  dinic.getMaxFlow(src, sink);
  vector<int>ret = dinic.getMinCut(src, sink); 
  vector<vector<int>>res(N, vector<int>(N)); 
  for(int i = 0; i < N; i++) { 
    res[i] = g[i]; 
  }
  for(auto e_id : ret) { 
    int u = e_id / N, v = e_id % N; 
    res[u][v] = 0; 
  }
  int flag = true; 
  for(int u = 0; u < N; u++) { 
    for(int v = 0; v < N; v++) { 
      if(res[u][v] < g[u][v]) {
        int c = res[u][v]; 
        res[u][v] += min(F, g[u][v] - res[u][v]); 
        F = F - g[u][v] + c;
        if(F <= 0) { flag = false; break; } 
      }
    }
    if(!flag) break; 
  }
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) { 
      cout << res[i][j] << " "; 
    }
    cout << '\n'; 
  }
  return 0;
}
