#include <bits/stdc++.h> 
 
using namespace std; 

#define sz(x) int(x.size()) 

const int64_t oo = 10000000000000;

struct Edge {
  int64_t a, b, cap, flow;
};

struct MaxFlow {
  int n, s, t;
  vector<int64_t> d, ptr, q;
  vector<Edge> e;
  vector<vector<int64_t>> g;

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
    int64_t qh = 0, qt = 0;
    q[qt++] = s;
    std::fill(d.begin(), d.end(), -1);
    d[s] = 0;

    while (qh < qt && d[t] == -1) {
      int64_t v = q[qh++];
      for (int64_t i = 0; i < (int64_t)g[v].size(); i++) {
        int64_t id = g[v][i], to = e[id].b;
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
    for (; ptr[v] < (int64_t)g[v].size(); ++ptr[v]) {
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

int main() { 
 int N; 
 cin >> N; 
 vector<string>s(N); 
 for(int i = 0; i < N; i++) { 
  cin >> s[i]; 
 } 
 MaxFlow dinic(2 * N + 2); 
 int src = 2 * N, sink = 2 * N + 1;
 vector<int>a(N); 
 int64_t ret = 0; 
 for(int i = 0; i < N; i++) { 
  cin >> a[i]; 
  ret += a[i]; 
 } 
 for(int i = 0; i < N; i++) { 
  dinic.addEdge(src, i, a[i]); 
  dinic.addEdge(i + N, sink, a[i]); 
 } 
 auto isSubstr = [&](string a, string b) { 
  for(int i = 0; i + sz(b) <= sz(a); i++) { 
    if(a.substr(i, sz(b)) == b) { 
     return true; 
    } 
  }
  return false; 
 }; 
 for(int i = 0; i < N; i++) { 
  for(int j = 0; j < N; j++) {  
   if(i == j) continue; 
   if(s[i] == s[j]) { 
    if(i > j) { 
     dinic.addEdge(i, j + N, oo); 
    } 
   }
   else if (isSubstr(s[i], s[j])) { 
    //cout << i << " " << j << '\n'; 
    dinic.addEdge(i, j + N, oo); 
   } 
  } 
 }
 int64_t flow = dinic.getMaxFlow(src, sink); 
 ret = ret - flow; 
 cout << ret << '\n'; 
 return 0;
}
 