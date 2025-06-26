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
 
 // build DAG of strongly connected components
 // Returns: adjacency list of DAG
 void solve(vector<double>&prob) {
  std::vector<std::vector<int>> dag(sz(scc));
  vector<double>dp(sz(scc), 0); 
  for (int u = 0; u < n; u++) {
   int x = comp_ids[u];
   dp[x] += log(1 - prob[u]); 
   for (int v : g[u]) {
    int y = comp_ids[v];
    if (x != y) {
     dag[x].push_back(y);
    }
   }
  } 
  vector<int>vis(sz(scc)); 
  function<double(int)> doit = [&](int u) { 
   if(vis[u]) return dp[u];
   vis[u] = true; 
   for(auto v : dag[u]) { 
    dp[u] += doit(v); 
   }
   return dp[u]; 
  };
  double ret = -1e100;  
  for(int i = 0; i < sz(scc); i++) { 
   if(sz(dag[i]) == 0) ret = max(ret, doit(i)); 
  }
  cout << exp(ret) << '\n'; 
  return; 
 }
};
 
int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N, M; 
  cout << setprecision(20); 
  cin >> N >> M;
  vector<double>prob(N); 
  for(int i = 0; i < N; i++) {
   cin >> prob[i]; 
  }
  vector<vector<int>>g(N); 
  for(int i = 0, U, V; i < M; i++) { 
   cin >> U >> V; 
   --U, --V; 
   g[U].push_back(V); 
  }
  DirectedDfs scc(g);
  scc.solve(prob); 
  return 0; 
}
 