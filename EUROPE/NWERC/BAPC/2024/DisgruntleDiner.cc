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
 int N, M; 
 cin >> N >> M; 
 vector<string>deck(N); 
 for(int i = 0; i < N; i++) { 
  cin >> deck[i]; 
 }
 vector<char>table(M); 
 for(int i = 0; i < M; i++) { 
  cin >> table[i]; 
 }
 char L, D; 
 cin >> D >> L; 
 vector<int>illegal, legal; 
 for(int i = 0; i < N; i++) { 
  (L != deck[i][0] && D == deck[i][1] ? illegal : legal).push_back(i); 
 }
 if(sz(illegal) == 0) { 
  cout << "true\n"; 
  return 0; 
 }
 MaxFlow dinic(sz(legal) + sz(table) + 2);
 int src = sz(legal) + sz(table), sink = src + 1; 
 for(int i = 0; i < sz(legal); i++) { 
  dinic.addEdge(src, i, 1);
  string c = deck[legal[i]]; 
  for(int j = 0; j < sz(table); j++) { 
   if(c[0] == table[j] || c[1] == table[j]) { 
    dinic.addEdge(i, j + sz(legal), 1); 
   }
  }
 } 
 for(int i = 0; i < sz(table); i++) { 
  dinic.addEdge(sz(legal) + i, sink, 1); 
 }
 int max_flow = dinic.getMaxFlow(src, sink); 
 if(max_flow != sz(table)) { 
  cout << "false\n"; 
  return 0;
 }
 vector<int>ans, marked(26); 
 for(int i = 0; i < sz(illegal); i++) { 
  string c = deck[illegal[i]]; 
  marked[c[0] - 'A'] = true; 
 }
 for(int j = 0; j < M; j++) { 
  if(D == table[j]) ans.push_back(j); 
  if(table[j] >= 'A' && marked[table[j] - 'A']) ans.push_back(j); 
 }
 if(sz(ans) == 0) { 
  cout << "true\n"; 
  return 0; 
 }
 cout << sz(ans) << '\n'; 
 for(auto &x : ans) cout << x + 1 << " "; 
 cout << '\n'; 
 return 0; 
}