#include "bits/stdc++.h"

using namespace std;

const int64_t oo = LLONG_MAX / 2;
const int INF = 1e9;  
 
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
            while (int pushed = dfs(s, INF))
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
  int N, M, C; 
  cin >> N >> M >> C; 
  vector<int>client(C), marked(N); 
  vector<vector<int>>par(N); 
  vector<vector<pair<int, int>>>g(N);
  for(int i = 0; i < C; i++) { 
    cin >> client[i]; 
    marked[client[i]] = true; 
  }
  for(int i = 0, u, v, w; i < M; i++) {
    cin >> u >> v >> w; 
    g[u].push_back({v, w});
  } 
  vector<int64_t>dist(N, oo);
  dist[0] = 0; 
  using T = pair<int64_t, int>; 
  priority_queue<T, vector<T>, greater<T>>pq; 
  pq.push({0, 0}); 
  while(pq.size()) { 
    auto [dst, u] = pq.top(); 
    pq.pop(); 
    if(dist[u] != dst) continue;
    for(auto [v, w] : g[u]) { 
      if(dist[v] > dist[u] + w) {
        dist[v] = dist[u] + w;
        par[v].clear(); 
        par[v].push_back(u);  
        pq.push({dist[v], v}); 
      }
      else if(dist[v] == dist[u] + w) {
        par[v].push_back(u); 
      }
    }
  } 
  vector<vector<int>>reach(N, vector<int>(N));
  function<void(int, int)> doit = [&](int u, int snk) {
    reach[u][snk] = true; 
    for(auto v : par[u]) if(!reach[v][snk]) { 
        doit(v, snk); 
    }
  }; 
  for(int i = 0; i < N; i++) {
    doit(i, i); 
  }
  MaxFlow dinic(2 * N + 2); 
  int src = 2 * N, snk = 2 * N + 1; 
  for(int i = 0; i < N; i++) { 
    dinic.addEdge(N + i, snk, 1); 
    dinic.addEdge(src, i, 1); 
  }
  for(int i = 0; i < C; i++)
  for(int j = 0; j < C; j++) if(i != j && reach[client[i]][client[j]]) { 
    dinic.addEdge(client[i], N + client[j], 1); 
  } 
  cout << C - dinic.getMaxFlow(src, snk) << '\n'; 
  return 0; 
}