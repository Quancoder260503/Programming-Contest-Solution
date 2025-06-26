/**
 * @file RoundTrip.cc
 * @author Minh Quan Le 
 * @brief 
 * @version 0.1
 * @date 2024-10-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "bits/stdc++.h"

using namespace std; 

#define int64_t long long 

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
  int build_scc_dag(vector<int>&cc) {
    vector<vector<int>> dag(scc.size());
    cc.resize(scc.size(), 0); 
    int ret = 0; 
    for (int u = 0; u < n; u++) {
      int x = comp_ids[u];
      cc[x]++; 
      for (int v : g[u]) {
        int y = comp_ids[v];
        if (x != y) {
          ret++; 
        }
      }
    }
    return ret;
  }
};

int main(void) {
  ios_base::sync_with_stdio(false);  
  cin.tie(0); 
  cout.tie(0); 
  int N, M; 
  cin >> N >> M; 
  vector<vector<int>>graph(N); 
  for(int i = 0, u, v; i < M; i++) { 
    cin >> u >> v; 
    graph[u].push_back(v); 
  }
  DirectedDfs _scc(graph); 
  vector<int>cc; 
  int bridge = _scc.build_scc_dag(cc); 
  int64_t ret = 0; 
  for(auto &x : cc) { 
    ret += x; 
  }
  ret = 1LL * ret * ret; 
  for(auto &x : cc) { 
    ret = ret - 1LL * x * x; 
  }
  ret = ret / 2; 
  ret = ret - bridge; 
  cout << ret << '\n'; 
  return 0; 
}

/**
 * @brief pruine the graph into an SCC DAG, note that we can not add edge between nodes in the same SCC (new round trip)
 * Thus add an edge from all node from a SCC to its sucessor in the SCC DAG (child -> parent) and also non-related (left -> right), 
 * then substracting out the bridge already in the graph. 
 */