#include "bits/stdc++.h"

using namespace std;

const int oo = 1e9; 

struct Edge {
 int a, b, cap, flow;
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
 void addEdge(int a, int b, int cap) {
  Edge e1 = {a, b, cap, 0};
  Edge e2 = {b, a, 0, 0};
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
  int n, m, k; 
  cin >> n >> m >> k; 
  vector<pair<int, int>>edges;
  for(int i = 0, u, v, w; i < k; i++) { 
   cin >> u >> v; 
   --u, --v; 
   edges.push_back({u, v}); 
  }
  auto getFlow = [&](int capacity, int getResult) {
   MaxFlow dinic(n + m + k + 2);  
   int src = n + m + k, sink = src + 1; 
   for(int i = 0; i < n + m; i++) { 
    dinic.addEdge(src, i, capacity); 
   }
   for(int i = 0; i < edges.size(); i++) {
    auto [u, v] = edges[i]; 
    dinic.addEdge(u, n + m + i, 1); 
    dinic.addEdge(n + v, n + m + i, 1);
    dinic.addEdge(n + m + i, sink, 1);
   }
   int ret = dinic.getMaxFlow(src, sink); 
   if(getResult) { 
    for(int i = 0; i < edges.size(); i++) { 
     auto [u, v] = edges[i]; 
     for(auto ind : dinic.g[u]) { 
      auto ed = dinic.e[ind]; 
      //cout << ed.a << " " << ed.b << " " << ed.cap << " " << ed.flow << '\n'; 
      if(ed.b == n + m + i && ed.flow == ed.cap) { 
       cout << "INDV " << u + 1 << '\n'; 
       goto done;   
      }  
     }
     for(auto ind : dinic.g[n + v]) { 
      auto ed = dinic.e[ind]; 
      if(ed.b == n + m + i && ed.flow == ed.cap) { 
     //   cout << ed.a << " " << ed.b << " " << ed.cap << " " << ed.flow << '\n';   
       cout << "CORP " << v + 1 << '\n'; 
       goto done;   
      }
     }
    done:; 
    }
   }
   return ret == k; 
  };
  int lo = 0, hi = oo;    
  while(lo < hi) { 
   int mid = (lo + hi) / 2; 
   if(getFlow(mid, 0)) hi = mid;
   else lo = mid + 1;  
  }
  getFlow(lo, 1); 
  return 0;
}