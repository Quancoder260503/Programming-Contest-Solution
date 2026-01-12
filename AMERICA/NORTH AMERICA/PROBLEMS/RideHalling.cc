#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())
#define vi vector<int>
#define all(x) x.begin(), x.end()
#define rep(i, j, k) for (int i = j; i < k; i++)

const int oo = 1e9;

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
    rep(a, 0, sz(g)) { 
     res += dfs(a, 0, g, btoa, A, B);
    } 
  }
  return res; 
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int64_t n, m, k;
  cin >> n >> m >> k;
  vector<vector<int>> dp(n, vector<int>(m, oo));
  for (int i = 0, u, v, c; i < m; i++) {
    cin >> u >> v >> c;
    --u, --v;
    dp[u][v] = min(dp[u][v], c);
  }
  for (int i = 0; i < n; i++) {
    dp[i][i] = 0;
  }
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
      }
    }
  }
  vector<array<int, 3>> trips(k);
  for(int i = 0; i < k; i++) { 
   for(int j = 0; j < 3; j++) { 
    cin >> trips[i][j]; 
   }
   trips[i][0]--; trips[i][1]--; 
  }
  vector<vector<int>>g(k); 
  vector<int>btoa(k, -1); 
  for(int i = 0; i < k; i++) { 
   for(int j = 0; j < k; j++) { 
    if(i == j) continue; 
    if(trips[i][2] + dp[trips[i][0]][trips[i][1]] + dp[trips[i][1]][trips[j][0]] <= trips[j][2]) { 
     //cout << i << " " << j << '\n'; 
     g[i].push_back(j);    
    }
   }
  }
  cout << k - hopcroftKarp(g, btoa) << '\n'; 
  return 0;
}