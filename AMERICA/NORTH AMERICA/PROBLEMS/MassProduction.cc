#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int64_t oo = 1e9; 

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

  int addEdge(int from, int to, Flow cap, Cost cost) {
    edges.push_back(Edge(to, cap, cost, last[from]));
    last[from] = t++;
    edges.push_back(Edge(from, 0, -cost, last[to]));
    last[to] = t++;
    return t - 2;
  }

  pair<Flow, Cost> minCostFlow(int _S, int _T) {
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

void solve(void) { 
 int N, M, A, B; 
 cin >> M >> N >> A >> B;
 vector<int>a(N), b(N); 
 for(int i = 0, x; i < N; i++) { 
  cin >> a[i]; 
 }
 for(int i = 0, x; i < N; i++) { 
  cin >> b[i]; 
 }
 vector<vector<int>>cost(M, vector<int>(N)); 
 for(int i = 0; i < M; i++) { 
  for(int j = 0; j < N; j++) { 
   cin >> cost[i][j]; 
  }
 }
 MinCostFlow mcmf(2 * N + M + 2); 
 int src = M + 2 * N, sink = M + 2 * N + 1; 
 for(int i = 0; i < N; i++) { 
  mcmf.addEdge(src, i, a[i], 0); 
 }
 for(int i = 0; i < N; i++) { 
  mcmf.addEdge(M + N + i, sink, b[i], 0); 
 }
 for(int i = 0; i < N; i++) { 
  for(int j = 0; j < M; j++) { 
   mcmf.addEdge(i, N + j, oo, A * cost[j][i]); 
   mcmf.addEdge(N + j, M + N + i, oo, B * cost[j][i]);
  }
 }
 cout << mcmf.minCostFlow(src, sink).second << '\n'; 
 return; 
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  int T; 
  for(cin >> T; T--; ) { 
   solve(); 
  }
  return 0; 
} 
