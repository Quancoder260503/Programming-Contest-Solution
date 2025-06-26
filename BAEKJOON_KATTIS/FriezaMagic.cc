#include "bits/stdc++.h"

using namespace std; 

#define int64_t long long
#define sz(x) int(x.size())

const int MOD = 1e9 + 7; 

int64_t mod_pow(int64_t a, int64_t b, int64_t p) {
  int64_t res = 1;
  while (b > 0) {
    if (b & 1) res = (res * a) % p;
    a = (a * a) % p;
    b >>= 1;
  }
  return res;
}

int64_t mod_inv(int64_t a, int64_t p) { return mod_pow(a % p, p - 2, p); }

const int _N = 1e6 + 1; 

int64_t ifact[_N], fact[_N]; 

int64_t Comb(int n, int k) { 
  if(n < k) return 0; 
  return fact[n] % MOD * ifact[k] % MOD * ifact[n - k] % MOD; 
}

void solve() { 
  int N; 
  cin >> N; 
  vector<vector<int>>g(N); 
  for(int i = 0, u, v; i < N - 1; i++) { 
    cin >> u >> v; 
    --u, --v; 
    g[u].push_back(v); 
    g[v].push_back(u); 
  } 
  vector<int>h(N); 
  function<void(int, int)> dfs = [&](int u, int p) { 
    for(auto v : g[u]) { 
      if(v == p) continue; 
      h[v] = h[u] + 1; 
      dfs(v, u); 
    }
    return; 
  }; 
  dfs(0, -1); 
  int64_t ret = 0; 
  for(int i = 0; i < N; i++) { 
    (ret += Comb(N, h[i] + 1) % MOD * fact[N - h[i] - 1] % MOD) %= MOD; 
  }
  cout << ret << '\n'; 
  return; 
} 

int main() {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  fact[0] = ifact[0] = 1; 
  for(int i = 1; i < _N; i++) { 
    fact[i] = fact[i - 1] % MOD * i % MOD; 
    ifact[i] = mod_inv(fact[i], MOD); 
  }
  int T; 
  cin >> T; 
  while(T--) { 
    solve(); 
  }
  return 0;
}