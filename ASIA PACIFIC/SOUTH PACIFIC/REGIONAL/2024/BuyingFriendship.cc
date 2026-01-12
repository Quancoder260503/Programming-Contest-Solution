#include "bits/stdc++.h"


#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,tune=native")

using namespace std; 

#define sz(x) int (x.size())

const int maxn = 1e5 + 10; 

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

  void build_scc_dag(vector<int>&cost) {
    vector<vector<int>> dag(scc.size());
    vector<int>indeg(scc.size(), 0), sub_comp_cost(scc.size(), -1);
    vector<pair<int, int>> comp_cost(scc.size());  
    vector<vector<int>>grp(sz(scc)); 
    for (int u = 0; u < n; u++) {
      int x = comp_ids[u];
      grp[x].push_back(u); 
      if(comp_cost[x].first < cost[u]) { 
       comp_cost[x].second = comp_cost[x].first; 
       comp_cost[x].first = cost[u]; 
      } else if(comp_cost[x].second < cost[u]) { 
       comp_cost[x].second = cost[u]; 
      }
      for (int v : g[u]) {
        int y = comp_ids[v];
        if (x != y) {
          dag[x].push_back(y);
          indeg[y]++; 
        }
      }
    }
    function<int(int)> dfs2 = [&](int u) { 
     if(sub_comp_cost[u] != -1) return sub_comp_cost[u]; 
     int &res = sub_comp_cost[u]; 
     res = comp_cost[u].first; 
     for(auto v : dag[u]) { 
      res = max(res, dfs2(v)); 
     }
     return res; 
    }; 
    for(int i = 0; i < sz(scc); i++) { 
      if(indeg[i] == 0) { 
        dfs2(i); 
      }
    }
    vector<int>ans(sz(cost)); 
    for(int i = 0; i < sz(scc); i++) { 
      int max_child_cost = 0;
      for(auto v : dag[i]) { 
        max_child_cost = max(max_child_cost, sub_comp_cost[v]); 
      }
      for(auto v : grp[i]) { 
       if(cost[v] == comp_cost[i].first) { 
        ans[v] = max(max_child_cost, comp_cost[i].second); 
       } else { 
        ans[v] = max(max_child_cost, comp_cost[i].first); 
       }
      }
    }
    for(auto &x : ans) cout << x << '\n'; 
    return; 
  }
}; 


int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  int n, m; 
  cin >> n >> m; 
  vector<vector<int>>g(n); 
  vector<int>cost(n); 
  for(int i = 0; i < n; i++) { 
   cin >> cost[i]; 
  } 
  for(int i = 0; i < m; i++) { 
   int u, v; 
   cin >> u >> v; 
   --u, --v; 
   g[u].push_back(v); 
  }
  DirectedDfs scc(g); 
  scc.build_scc_dag(cost); 
  return 0; 
}