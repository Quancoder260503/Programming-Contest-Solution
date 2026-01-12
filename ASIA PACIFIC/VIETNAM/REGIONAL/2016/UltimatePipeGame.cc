#include "bits/stdc++.h"

using namespace std; 


#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#define int64_t long long

template <class Flow = int64_t, class Cost = int64_t>
struct MinCostFlow {
  const Flow INF_FLOW = 1000111000;
  const Cost INF_COST = 1000111000111000LL;

  int n, t, S, T;
  Flow totalFlow;
  Cost totalCost;
  vector<int> last, visited;
  vector<Cost> dis;
  struct Edge {
    int to;
    Flow cap;
    Cost cost;
    int next;
    Edge(int _to, Flow _cap, Cost _cost, int _next)
        : to(_to), cap(_cap), cost(_cost), next(_next) {}
  };
  vector<Edge> edges;

  MinCostFlow(int _n)
      : n(_n),
        t(0),
        totalFlow(0),
        totalCost(0),
        last(n, -1),
        visited(n, 0),
        dis(n, 0) {
    edges.clear();
  }

  int add_edge(int from, int to, Flow cap, Cost cost) {
    edges.push_back(Edge(to, cap, cost, last[from]));
    last[from] = t++;
    edges.push_back(Edge(from, 0, -cost, last[to]));
    last[to] = t++;
    return t - 2;
  }

  pair<Flow, Cost> solve(int _S, int _T) {
    S = _S;
    T = _T;
    SPFA();
    while (1) {
      while (1) {
        std::fill(visited.begin(), visited.end(), 0);
        if (!findFlow(S, INF_FLOW)) break;
      }
      if (!modifyLabel()) break;
    }
    return make_pair(totalFlow, totalCost);
  }
 private:
  void SPFA() {
    std::fill(dis.begin(), dis.end(), INF_COST);
    priority_queue<pair<Cost, int> > Q;
    Q.push(make_pair(dis[S] = 0, S));
    while (!Q.empty()) {
      int x = Q.top().second;
      Cost d = -Q.top().first;
      Q.pop();
      // For double: dis[x] > d + EPS
      if (dis[x] != d) continue;
      for (int it = last[x]; it >= 0; it = edges[it].next)
        if (edges[it].cap > 0 && dis[edges[it].to] > d + edges[it].cost)
          Q.push(make_pair(-(dis[edges[it].to] = d + edges[it].cost),
                           edges[it].to));
    }
    Cost disT = dis[T];
    for (int i = 0; i < n; i++) {
      dis[i] = disT - dis[i];
    }
  }

  Flow findFlow(int x, Flow flow) {
    if (x == T) {
      totalCost += dis[S] * flow;
      totalFlow += flow;
      return flow;
    }
    visited[x] = 1;
    Flow now = flow;
    for (int it = last[x]; it >= 0; it = edges[it].next)
      // For double: fabs(dis[edges[it].to] + edges[it].cost - dis[x]) < EPS
      if (edges[it].cap && !visited[edges[it].to] &&
          dis[edges[it].to] + edges[it].cost == dis[x]) {
        Flow tmp = findFlow(edges[it].to, min(now, edges[it].cap));
        edges[it].cap -= tmp;
        edges[it ^ 1].cap += tmp;
        now -= tmp;
        if (!now) break;
      }
    return flow - now;
  }

  bool modifyLabel() {
    Cost d = INF_COST;
    for (int i = 0; i < n; i++)
      if (visited[i])
        for (int it = last[i]; it >= 0; it = edges[it].next)
          if (edges[it].cap && !visited[edges[it].to])
            d = min(d, dis[edges[it].to] + edges[it].cost - dis[i]);

    // For double: if (d > INF_COST / 10)     INF_COST = 1e20
    if (d == INF_COST) return false;
    for (int i = 0; i < n; i++)
      if (visited[i]) dis[i] += d;
    return true;
  }
};


int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);
 int n, m, tc; 
 for(cin >> tc; tc--; ) {  
  cin >> n >> m; 
  vector<vector<int>>h(n, vector<int>(m)), v(n, vector<int>(m)); 
  vector<vector<char>>g(n, vector<char>(m)); 
  for(int i = 0; i < n; i++) { 
   for(int j = 0; j < m; j++) { 
    cin >> g[i][j]; 
   }
  }
  for(int i = 0; i < n; i++) { 
   for(int j = 0; j < m; j++) { 
    cin >> h[i][j];
   }
  }
  for(int i = 0; i < n; i++) { 
   for(int j = 0; j < m; j++) { 
    cin >> v[i][j]; 
   }
  }
  int sum = 0; 
  MinCostFlow mcmf(2 * n * m + 2);
  int src = 2 * n * m, sink = src + 1;  
  for(int i = 0; i < n; i++) { 
   for(int j = 0; j < m; j++) if(g[i][j] == '.') {
    if((i + j) % 2 == 0) { 
     sum += 2; 
     mcmf.add_edge(src, i * m + j, 1, 0);
     mcmf.add_edge(src, n * m + i * m + j, 1, 0);  
     mcmf.add_edge(i * m + j, n * m + i * m + j, 1, v[i][j]); 
     mcmf.add_edge(n * m + i * m + j, i * m + j, 1, h[i][j]); 
    // cout << i << " " << j << " " << h[i][j] << " " << v[i][j] << '\n';  
     if(j + 1 < m && g[i][j + 1] == '.') { 
      mcmf.add_edge(i * m + j, i * m + j + 1, 1, 0);   
     }
     if(j > 0 && g[i][j - 1] == '.') { 
      mcmf.add_edge(i * m + j, i * m + j - 1, 1, 0); 
     }  
     if(i + 1 < n && g[i + 1][j] == '.') { 
      mcmf.add_edge(n * m + i * m + j, n * m + (i + 1) * m + j, 1, 0);   
     }
     if(i > 0 && g[i - 1][j] == '.') { 
      mcmf.add_edge(n * m + i * m + j, n * m + (i - 1) * m + j, 1, 0);   
     }
    } else { 
     mcmf.add_edge(i * m + j, sink, 1, 0); 
     mcmf.add_edge(n * m + i * m + j, sink, 1, 0); 
     mcmf.add_edge(i * m + j, n * m + i * m + j, 1, h[i][j]); 
     mcmf.add_edge(n * m + i * m + j, i * m + j, 1, v[i][j]); 
    }
   }
  }
  auto res = mcmf.solve(src, sink); 
  //cout << sum << " " << res.first << " " << res.second << '\n'; 
  if(res.first == sum) cout << "YES " << res.second << '\n'; 
  else cout << "NO\n"; 
 } 
 return 0; 
}