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
  cin >> N >> M >> K; 
  vector<vector<int>>g(N, vector<int>(M)); 
  vector<vector<int>>tree(2 * N, vector<int>(2 * M));
  int ind = K; 
  for(int i = 0; i < 2 * N; i++) { 
   for(int j = 0; j < 2 * M; j++) { 
    tree[i][j] = ind++; 
   }
  }
  MaxFlow dinic(ind + 2); 
  int src = ind; 
  int sink = src + 1; 
  auto update = [&](int row, int b, int e, int ver) { 
    for (b += M, e += M; b < e; b /= 2, e /= 2) { 
			if (b % 2) { dinic.addEdge(ver, tree[row][b++], oo); }
			if (e % 2) { dinic.addEdge(ver, tree[row][--e], oo); }
		}
  }; 
  auto addSink = [&](int r, int c) {
   r += N, c += M;
   dinic.addEdge(tree[r][c], sink, g[r - N][c - M]); 
   for(int row = r; row > 0; row /= 2) { 
    for(int col = c; col > 0; col /= 2) { 
      dinic.addEdge(tree[row][col], tree[r][c], oo); 
    }
   }
  }; 
  for(int i = 0; i < N; i++) { 
   for(int j = 0; j < M; j++) { 
    cin >> g[i][j]; 
    addSink(i, j); 
   }  
  }
  for(int i = 0; i < K; i++) { 
   int r1, r2, c1, c2, cap;
   cin >> r1 >> r2 >> c1 >> c2 >> cap; 
   --r1, --c1; 
   dinic.addEdge(src, i, cap); 
   int b = r1, e = r2; 
   for (b += N , e += N; b < e; b /= 2, e /= 2) { 
		if (b % 2) { update(b++, c1, c2, i); }
		if (e % 2) { update(--e, c1, c2, i); }
	 }
  }
  cout << dinic.getMaxFlow(src, sink) << '\n'; 
  return 0; 
}
