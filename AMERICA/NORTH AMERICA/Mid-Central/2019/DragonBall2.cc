#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")
#pragma GCC target("avx2") 

using namespace std;

const int64_t oo = 1e14; 
const int maxn = 5e5 + 5;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

vector<pair<int, int>>g[maxn]; 
vector<int>col[maxn]; 
int ind[maxn]; 
int64_t dp[maxn][1 << 8]; 
int n, m, k;

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);
 cin >> n >> m >> k; 
 for(int i = 0, u, v, w; i < m; i++) { 
  cin >> u >> v >> w; 
  --u, --v; 
  g[u].push_back({v, w}); 
  g[v].push_back({u, w}); 
 }
 for(int i = 0, u, v; i < k; i++) { 
  cin >> u >> v; 
  --u, --v; 
  col[u].push_back(v); 
 }
 vector<int>ind(n); 
 int64_t ret = oo; 
 for(int step = 0; step < 1000; step++) { 
  for(int i = 0; i < n; i++) { 
   ind[i] = rng() % 7; 
   for(int j = 0; j < (1 << 7); j++) { 
    dp[i][j] = oo; 
   }
  }
  using T = tuple<int64_t, int, int>;
  priority_queue<T, vector<T>, greater<T>>pq; 
  int cmask = 0, src = 0; 
  for(auto c : col[src]) { 
   cmask |= (1 << ind[c]); 
  }
  dp[src][cmask] = 0; 
  pq.push({dp[src][cmask], src, cmask}); 
  int64_t ans = oo; 
  while(pq.size()) { 
   auto [d, u, mask] = pq.top(); 
   pq.pop(); 
   if(d != dp[u][mask]) continue; 
   if(mask == (1 << 7) - 1) { 
    ret = min(ret, dp[u][mask]); 
    goto done; 
   }
   for(auto [v, w] : g[u]) {
    int nmask = mask; 
    for(auto c : col[v]) { 
     nmask |= (1 << ind[c]); 
    }
    if(dp[v][nmask] > dp[u][mask] + w) { 
     dp[v][nmask] = dp[u][mask] + w; 
     pq.push({dp[v][nmask], v, nmask}); 
    }
   }
  }
done:; 
 }
 cout << (ret == oo ? -1 : ret) << '\n'; 
 return 0; 
}