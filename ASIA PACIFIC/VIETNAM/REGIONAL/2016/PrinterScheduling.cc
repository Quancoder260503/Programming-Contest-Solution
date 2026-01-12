#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int oo = 1000000000;
const int maxf = 300; 

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

int l[maxf], r[maxf], d[maxf]; 

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int N, M, Q;
  cin >> Q;
  for (int iter = 0; iter < Q; iter++) {
    cin >> N >> M;
    int sumFlow = 0;
    vector<int>coord; 
    for (int i = 0; i < N; i++) {
      cin >> d[i] >> l[i] >> r[i];
      coord.push_back(l[i]); 
      coord.push_back(r[i]);
      sumFlow += d[i];
    }
    sort(coord.begin(), coord.end()); 
    coord.erase(unique(coord.begin(), coord.end()), coord.end()); 
    coord.push_back(coord.back() + 1); 
    // [L, R)
    int K = sz(coord); 
    MaxFlow dinic(N + K + 3);
    int src = N + K + 1;
    int sink = N + K + 2;
    for (int i = 0; i < N; i++) {
      dinic.addEdge(src, i, d[i]);
      int pos = lower_bound(coord.begin(), coord.end(), l[i]) - coord.begin(); 
      int j; 
      for(j = pos; coord[j] < r[i]; j++) { 
       dinic.addEdge(i, N + j, coord[j + 1] - coord[j]); 
      } 
      dinic.addEdge(i, N + j, 1); 
    }
    for (int i = 0; i + 1 < K; i++) {
      dinic.addEdge(N + i, sink, M * (coord[i + 1] - coord[i]));
    }
    int cc = dinic.getMaxFlow(src, sink);
   // cout << cc << " " << sumFlow << '\n'; 
    if (cc == sumFlow) {
      cout << "YES\n"; 
      vector<int>capacity(coord.back() + 1, M); 
      vector<vector<pair<int, int>>>group(K); 
      for (int i = 0; i < N; i++) {
       vector<pair<int, int>>ret; 
       for(auto id : dinic.g[i]) { 
        auto edge = dinic.e[id];
        if(edge.a == i && edge.b < src && edge.flow > 0) {
        // cout << i << " " << edge.b - N << " " << edge.flow << '\n'; 
         group[edge.b - N].push_back({edge.flow, i}); 
        }  
       }
      }
      vector<vector<array<int, 3>>>ret(N); 
      for(int interval = 0; interval + 1 < K; interval++) { 
       sort(group[interval].rbegin(), group[interval].rend()); 
       int end_pos = coord[interval + 1];
       int curr_pos = coord[interval];
       int curr_colour = 0; 
       for(auto [allocation, ind]: group[interval]) { 
        if(allocation < end_pos - curr_pos) { 
          ret[ind].push_back({curr_pos, curr_pos + allocation - 1, curr_colour}); 
          curr_pos = curr_pos + allocation; 
        } else { 
          if(curr_pos < end_pos) {
           ret[ind].push_back({curr_pos, end_pos - 1, curr_colour});
          } 
        // if(interval == 1) cout << curr_colour << " " << end_pos << '\n'; 
          allocation = allocation - (end_pos - curr_pos); 
          curr_colour++; 
          curr_pos = coord[interval]; 
          if(allocation > 0) { 
           ret[ind].push_back({curr_pos, curr_pos + allocation - 1, curr_colour}); 
           curr_pos = curr_pos + allocation; 
          }
        }
       }
      }
      for(int i = 0; i < N; i++) { 
        cout << sz(ret[i]) << '\n'; 
       for(auto [from, to, machine] : ret[i]) { 
        cout << from << " " << to << " " << machine + 1 << '\n'; 
       }
      } 
    } 
    else {
      cout << "NO\n";
    }
    cout << '\n'; 
  }
  return 0;
}