#include "bits/stdc++.h"

using namespace std;

const int oo = 1000000000;
 
struct Edge {
    int a, b, cap, flow;
};

struct MaxFlow {
    int n, s, t;
    vector<int> d, ptr, q;
    vector< Edge > e;
    vector< vector<int> > g;

    MaxFlow(int _n) : n(_n), d(_n), ptr(_n), q(_n), g(_n) {
        e.clear();
        for (int i = 0; i < n; i++) {
            g[i].clear();
            ptr[i] = 0;
        }
    }

    void addEdge(int a, int b, int cap) {
        Edge e1 = { a, b, cap, 0 };
        Edge e2 = { b, a, 0, 0 };
        g[a].push_back( (int) e.size() );
        e.push_back(e1);
        g[b].push_back( (int) e.size() );
        e.push_back(e2);
    }
    int getMaxFlow(int _s, int _t) {
        s = _s; t = _t;
        int flow = 0;
        for (;;) {
            if (!bfs()) break;
            std::fill(ptr.begin(), ptr.end(), 0);
            while (int pushed = dfs(s, oo))
                flow += pushed;
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
            for (int i = 0; i < (int) g[v].size(); i++) {
                int id = g[v][i], to = e[id].b;
                if (d[to] == -1 && e[id].flow < e[id].cap) {
                    q[qt++] = to;
                    d[to] = d[v] + 1;
                }
            }
        }
        return d[t] != -1;
    }

    int dfs (int v, int flow) {
        if (!flow) return 0;
        if (v == t) return flow;
        for (; ptr[v] < (int)g[v].size(); ++ptr[v]) {
            int id = g[v][ptr[v]],
                to = e[id].b;
            if (d[to] != d[v] + 1) continue;
            int pushed = dfs(to, min(flow, e[id].cap - e[id].flow));
            if (pushed) {
                e[id].flow += pushed;
                e[id^1].flow -= pushed;
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
  int N, Q; 
  cin >> N >> Q; 
  vector<vector<int>>par(N); 
  for(int i = 0, x; i < N; i++) { 
    cin >> x; 
    par[i].resize(x); 
    for(int j = 0; j < x; j++) { 
      cin >> par[i][j]; 
    }
  }
  auto solve = [&](vector<int>cc, int type) { 
    MaxFlow dinic(2 * N + 4); 
    int src = 2 * N + 2, sink = 2 * N + 3;
    for(int i = 0; i < N; i++) { 
      dinic.addEdge(src, i + 1, 1); 
      for(auto v : par[i]) { 
        dinic.addEdge(i + 1, v + N + 1, 1); 
      }
      if(!type && par[i].size() < N) { 
        dinic.addEdge(i + 1, N + 1, 1); 
      }
    } 
    for(auto v : cc) { 
       dinic.addEdge(v + N + 1, sink, type ? 1 : N); 
    }
    dinic.addEdge(N + 1, sink, N); 
    return dinic.getMaxFlow(src, sink); 
  }; 
  for(int iter = 0, x; iter < Q; iter++) { 
    vector<int>cc; 
    cin >> x; 
    cc.resize(x); 
    for(int j = 0; j < x; j++) {
       cin >> cc[j]; 
    } 
    if(solve(cc, false) == N && solve(cc, true) == x) { puts("Y"); }
    else { puts("N"); }
  }
  return 0; 
}