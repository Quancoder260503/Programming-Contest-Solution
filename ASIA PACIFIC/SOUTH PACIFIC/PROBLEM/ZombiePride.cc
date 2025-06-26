#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

struct DirectedDfs {
  vector<vector<int>> g;
  int n;
  vector<int> num, low, current, S;
  int counter;
  vector<int> comp_ids;
  vector<vector<int>> scc;

  DirectedDfs(const vector<vector<int>>& _g)
      : g(_g),
        n(g.size()),
        num(n, -1),
        low(n, 0),
        current(n, 0),
        counter(0),
        comp_ids(n, -1) {
    for (int i = 0; i < n; i++) {
      if (num[i] == -1) dfs(i);
    }
  }

  void dfs(int u) {
    low[u] = num[u] = counter++;
    S.push_back(u);
    current[u] = 1;
    for (auto v : g[u]) {
      if (num[v] == -1) dfs(v);
      if (current[v]) low[u] = min(low[u], low[v]);
    }
    if (low[u] == num[u]) {
      scc.push_back(vector<int>());
      while (1) {
        int v = S.back();
        S.pop_back();
        current[v] = 0;
        scc.back().push_back(v);
        comp_ids[v] = ((int)scc.size()) - 1;
        if (u == v) break;
      }
    }
  } 
  std::vector<std::vector<int>> build_scc_dag() {
    std::vector<std::vector<int>> dag(scc.size());
    for (int u = 0; u < n; u++) {
      int x = comp_ids[u];
      for (int v : g[u]) {
        int y = comp_ids[v];
        if (x != y) {
          dag[x].push_back(y);
        }
      }
    }
    return dag;
  }
};

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
    int64_t qh = 0, qt = 0;
    q[qt++] = s;
    std::fill(d.begin(), d.end(), -1);
    d[s] = 0;

    while (qh < qt && d[t] == -1) {
      int64_t v = q[qh++];
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
 int N; 
 cin >> N; 
 map<string, int>mp; 
 int id = 0;  
 string line; 
 cin.ignore(); 
 vector<int>a(N); 
 vector<vector<int>>g(N); 
 for(int i = 0; i < N; i++) { 
  getline(cin, line); 
  stringstream ss(line); 
  string word, next, num; 
  ss >> word; 
  if(!mp.count(word)) { 
    mp[word] = id++; 
  }
  ss >> num; 
  a[mp[word]] = stoi(num); 
  while(ss >> next) { 
    if(!mp.count(next)) { 
      mp[next] = id++; 
    }
    g[mp[word]].push_back(mp[next]); 
  }
 }
 DirectedDfs Scc(g); 
 int M = sz(Scc.scc); 
 vector<int>b(M); 
 for(int i = 0; i < N; i++) { 
  b[Scc.comp_ids[i]] += a[i]; 
 }
 b[Scc.comp_ids[mp["graveyard"]]]++; 
 MaxFlow dinic(2 * M + 2); 
 vector<vector<int>>graph = Scc.build_scc_dag(); 
 vector<int>vis(M); 
 function<void(int)> dfs = [&](int u) { 
  if(vis[u]) return; 
  vis[u] = true; 
  for(auto v : graph[u]) { 
    dfs(v); 
  }
  return; 
 }; 
 int src = 2 * M; 
 int sink = 2 * M + 1; 
 for(int i = 0; i < M; i++) {
  dinic.addEdge(i + M, sink, 1, 0);    
  dinic.addEdge(src, i, b[i], 0); 
 }
 int cnt = 0; 
 for(int i = 0; i < M; i++) { 
  if(b[i] > 0) { 
   cnt++; 
   fill(vis.begin(), vis.end(), false); 
   dfs(i);  
   if(i == Scc.comp_ids[mp["graveyard"]]) { 
    for(int j = 0; j < M; j++) { 
     if(b[j] > 0 && !vis[j]) { 
      cout << "zombie outbreak..." << '\n'; 
      exit(0); 
     }
    }
   }
   for(int j = 0; j < M; j++) { 
    if(i == j || !vis[j] || b[j] == 0) continue; 
    dinic.addEdge(i, j + M, oo, 0); 
   }
  }
 }
 int ret = dinic.getMaxFlow(src, sink); 
 //cout << ret << " " << " " << cnt << '\n'; 
 cout << (ret + 1 == cnt ? "ZOMBIE APOCALYPSE!!!" : "zombie outbreak...") << '\n'; 
 return 0; 
}