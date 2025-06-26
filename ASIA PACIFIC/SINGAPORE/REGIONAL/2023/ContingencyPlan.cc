#include "bits/stdc++.h"

using namespace std; 

#define rep(i, j, k) for(int i = j; i < k; i++) 
#define all(x) x.begin(), x.end()
#define vi vector<int> 
#define sz(x) int(x.size())

bool dfs(int a, int L, vector<vi>& g, vi& btoa, vi& A, vi& B) {
  if (A[a] != L) return 0;
  A[a] = -1;
  for (int b : g[a])
    if (B[b] == L + 1) {
      B[b] = 0;
      if (btoa[b] == -1 || dfs(btoa[b], L + 1, g, btoa, A, B))
        return btoa[b] = a, 1;
    }
  return 0;
}

int hopcroftKarp(vector<vi>& g, vi& btoa) {
  int res = 0;
  vi A(g.size()), B(btoa.size()), cur, next;
  for (;;) {
    fill(all(A), 0);
    fill(all(B), 0);
    /// Find the starting nodes for BFS (i.e. layer 0).
    cur.clear();
    for (int a : btoa)
      if (a != -1) A[a] = -1;
    rep(a, 0, sz(g)) if (A[a] == 0) cur.push_back(a);
    /// Find all layers using bfs.
    for (int lay = 1;; lay++) {
      bool islast = 0;
      next.clear();
      for (int a : cur)
        for (int b : g[a]) {
          if (btoa[b] == -1) {
            B[b] = lay;
            islast = 1;
          } else if (btoa[b] != a && !B[b]) {
            B[b] = lay;
            next.push_back(btoa[b]);
          }
        }
      if (islast) break;
      if (next.empty()) return res;
      for (int a : next) A[a] = lay;
      cur.swap(next);
    }
    /// Use DFS to scan for augmenting paths.
    rep(a, 0, sz(g)) res += dfs(a, 0, g, btoa, A, B);
  }
  return res;
}

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N; 
 cin >> N; 
 vector<vector<int>>tree(N), tree2(N); 
 vector<int>btoa(N, -1); 
 vector<pair<int, int>>edge; 
 vector<int>deg(N);  
 for(int i = 0, u, v; i < N - 1; i++) { 
  cin >> u >> v; 
  tree[v - 1].push_back(u - 1);
  tree2[u - 1].push_back(v - 1); 
  edge.push_back({u - 1, v - 1}); 
  deg[v - 1]++; 
 }
 vector<int>topo;
 queue<int>q; 
 for(int i = 0; i < N; i++) { 
  if(deg[i] == 0) { 
   q.push(i); 
  }
 }
 while(sz(q)) { 
  int u = q.front(); 
  q.pop(); 
  topo.push_back(u);
  for(auto v : tree2[u]) { 
    deg[v]--;
    if(deg[v] == 0) {
     q.push(v); 
    }
  }
 } 
 int mvc = hopcroftKarp(tree, btoa);
 vector<int>visited(N), id(N); 
 vector<vector<int>>paths; 
 for(int i = 0; i < N; i++) {
  if(visited[topo[i]]) continue; 
  int c = topo[i]; 
  vector<int>path; 
  while(c != -1) { 
   visited[c] = true; 
   id[c] = sz(paths); 
   path.push_back(c); 
   c = btoa[c]; 
  }
  paths.push_back(path); 
 }
 vector<vector<int>>graph(sz(paths)); 
 for(auto [u, v] : edge) { 
  if(id[u] == id[v]) continue; 
  graph[id[u]].push_back(id[v]); 
 }
 vector<int>marked(sz(paths)); 
 vector<int>ord; 
 function<void(int)> dfs = [&](int u) { 
  if(marked[u]) return; 
  marked[u] = true; 
  for(auto v : graph[u]) { 
    dfs(v); 
  }
  ord.push_back(u); 
  return; 
 }; 
 for(int i = 0; i < sz(paths); i++) { 
  dfs(i); 
 }
 reverse(ord.begin(), ord.end()); 
 vector<pair<int, int>>ret; 
 for(int i = 0; i + 1 < sz(ord); i++) {
  //cout << ord[i] << " " << ord[i + 1] << '\n'; 
  ret.push_back({paths[ord[i]].back(), paths[ord[i + 1]][0]}); 
 }
 cout << N - mvc - 1 << '\n';
 for(int i = 0; i < sz(ret); i++) { 
  cout << ret[i].first + 1 << " " << ret[i].second + 1 << '\n'; 
 }
 return 0; 
}