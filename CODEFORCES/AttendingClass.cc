#include "bits/stdc++.h"
 
using namespace std;
 
#define sz(x) int(x.size())
 
const int maxf = 2e5 + 10;
const int mod = 998244353;
const int LOG = 19;
 
vector<int> g[maxf];
int up[LOG][maxf], h[maxf], N, Q;
int64_t ways[LOG][maxf], Prob[maxf]; 
 
int64_t fpow(int64_t a, int64_t k) {
  if (!k) return 1;
  int64_t res = a, tmp = a;
  k--;
  while (k) {
    if (k & 1) {
      res = (int64_t)res % mod * tmp % mod;
    }
    tmp = (int64_t)tmp % mod * tmp % mod;
    k >>= 1;
  }
  return res;
}
 
void dfs(int u, int p) {
  for (int i = 1; i < LOG; i++) {
    up[i][u] = up[i - 1][up[i - 1][u]];
  }
  for (auto v : g[u]) {
    if (v == p) continue;
    h[v] = h[up[0][v] = u] + 1;
    dfs(v, u);
  }
  return;
}

int jump(int u, int d) { 
  for (int i = 0; i < LOG; i++) {
    if (d & (1 << i)) {
      u = up[i][u];
    }
  } 
  return u; 
}

int LCA(int u, int v) {
  if (h[u] < h[v]) swap(u, v);
  int d = h[u] - h[v];
  for (int i = 0; i < LOG; i++) {
    if (d & (1 << i)) {
      u = up[i][u];
    }
  }
  if (u == v) return u;
  for (int i = LOG - 1; i >= 0; i--) {
    int tu = up[i][u], tv = up[i][v];
    if (tu != tv) u = tu, v = tv;
  }
  return up[0][u];
}
int dist(int u, int v) { return h[u] + h[v] - 2 * h[LCA(u, v)]; }
 
void dfsNaive(int u, int p) { 
  for(auto v : g[u]) { 
    if(v == p) continue; 
    Prob[v] = Prob[u] % mod * (sz(g[u]) - (p > 0)) % mod;
    dfsNaive(v, u);  
  }
  return; 
}

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  cin >> N >> Q;
  for(int i = 0, u, v; i < N - 1; i++) { 
    cin >> u >> v; 
    g[u].push_back(v); 
    g[v].push_back(u); 
  }
  Prob[1] = 1; 
  dfsNaive(1, 0); 
  dfs(1, 0);
  for(int i = 0, u, v; i < Q; i++) { 
    cin >> u >> v; 
    int anc = LCA(u, v);
    int64_t ret = sz(g[u]); 
    if(u == anc) { 
      ret = ret % mod * Prob[v] % mod * fpow(Prob[jump(v, h[v] - h[u] - 1)], mod - 2) % mod;    
    } 
    else if (v == anc) { 
      ret = ret % mod * Prob[u] % mod * fpow(Prob[jump(u, h[u] - h[v] - 1)], mod - 2) % mod;  
    }
    else { 
      ret = ret % mod * Prob[u] % mod * fpow(Prob[jump(u, h[u] - h[anc] - 1)], mod - 2) % mod; 
      ret = ret % mod * Prob[v] % mod * fpow(Prob[jump(v, h[v] - h[anc] - 1)], mod - 2) % mod; 
      ret = ret % mod * (sz(g[anc]) - 1) % mod; 
    }
    cout << ret << '\n'; 
  }
  return 0;
}