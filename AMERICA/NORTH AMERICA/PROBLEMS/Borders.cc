#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

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

template<class T>
ostream &operator << (ostream &out, vector<vector<T>>&d) { 
 for(int i = 0; i < sz(d); i++) { 
  for(int j = 0; j < sz(d[i]); j++) { 
    out << d[i][j] << " "; 
  }
  cout << '\n'; 
 }
 return out; 
}


int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int n, m; 
  cin >> n >> m; 
  // min-cut
  vector<vector<char>>g(n, vector<char>(m)); 
  for(int i = 0; i < n; i++) { 
   for(int j = 0; j < m; j++) { 
    cin >> g[i][j]; 
   }
  }
  const int dx[4] = {0, 0, -1, 1}; 
  const int dy[4] = {-1, 1, 0, 0}; 
  vector<vector<int>>ind(n, vector<int>(m, -1)); 
  int c = -1; 
  vector<int>on_border, colour; 
  for(int i = 0; i < n; i++) { 
   for(int j = 0; j < m; j++) if(ind[i][j] == -1) { 
    queue<pair<int, int>>q; 
    q.push({i, j}); 
    ind[i][j] = ++c; 
    on_border.push_back(0); 
    colour.push_back(g[i][j] - '0'); 
    while(sz(q)) { 
     auto [x, y] = q.front(); 
     q.pop(); 
     on_border.back() |= (x == 0 || y == 0 || x == n - 1 || y == m - 1); 
  //   (g[x][y] ? dinic.addEdge(src, c, 1) : dinic.addEdge(c, sink, 1));
     for(int k = 0; k < 4; k++) { 
      int nx = x + dx[k], ny = y + dy[k]; 
      if(0 <= nx && nx < n && 0 <= ny && ny < m && ind[nx][ny] == -1 && g[x][y] == g[nx][ny]) { 
       ind[nx][ny] = c; 
       q.push({nx, ny}); 
      }
     }
    } 
   }
  }
  int sum = 0; 
  MaxFlow dinic(c + 3); 
  set<pair<int, int>>edge;
  int src = c + 1, sink = src + 1; 
  for(int i = 0; i < n; i++) { 
   for(int j = 0; j < m; j++) { 
    if(g[i][j] == '1') { 
     for(int k = 0; k < 4; k++) { 
      int ni = i + dx[k], nj = j + dy[k]; 
      if(0 <= ni && ni < n && 0 <= nj && nj < m && g[i][j] != g[ni][nj]) { 
       edge.insert({ind[i][j], ind[ni][nj]}); 
      }
     }
    }
   }
  }
  for(int i = 0; i < sz(colour); i++) { 
   if(colour[i]) {
    dinic.addEdge(src, i, 1); 
    if(on_border[i]) { 
      dinic.addEdge(i, sink, 1); 
    }
   } else { 
    dinic.addEdge(i, sink, 1); 
    if(on_border[i]) { 
      dinic.addEdge(src, i, 1); 
    }
   }
  }
  for(auto &[u, v] : edge) { 
   dinic.addEdge(u, v, 1); 
  }
  cout << dinic.getMaxFlow(src, sink) << '\n'; 
  return 0; 
}