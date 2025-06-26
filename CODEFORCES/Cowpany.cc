#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define int64_t long long

const int mod = 1e9 + 7; 
const int maxf = 100000;
const int N = 4000; 

vector<int>graph[maxf]; 
vector<int64_t>cc[maxf]; 
int M, D;

int64_t acc[maxf], fact[maxf], ifact[maxf], fib[maxf];

int64_t Comb(int a, int b) {
  if (a == b) return 1;
  if (a < b || b < 0) return 0;
  return fact[a] % mod * ifact[b] % mod * ifact[a - b] % mod;
}

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

void init(void) {
  fact[0] = ifact[0] = 1;
  for (int i = 1; i < maxf; i++) {
    fact[i] = fact[i - 1] % mod * i % mod;
    ifact[i] = ifact[i - 1] % mod * fpow(i, mod - 2) % mod;
  }
  return;
}

vector<int64_t> Combine(const vector<int64_t> &a, const vector<int64_t> &b) { 
  vector<int64_t>ret(min(N, D) + 1, 0);
  vector<int64_t>rb(sz(b)); 
  for(int i = 0; i < sz(b); i++) { 
    rb[i] = (i ? rb[i - 1] : 0) + b[i]; 
  }
  for(int i = 0; i < sz(a); i++) { 
    (ret[i] += rb[i] % mod * a[i] % mod) %= mod; 
  }
  return ret;
}

void dfs(int u, int p) { 
  cc[u].resize(min(N, D) + 1, 1); 
  cc[u][0] = 0; 
  for(auto v : graph[u]) { 
    if(v == p) continue; 
    dfs(v, u); 
    cc[u] = Combine(cc[u], cc[v]); 
  }
  return; 
}

int64_t Interpolation(void) { 
  if(D <= N) return acc[D]; 
  int64_t ret = 0; 
  for(int i = 1; i < N; i++) {
    int64_t den = ((D - i) % mod * (i & 1 ? 1 : -1) + mod) % mod; 
    den = den * fact[i - 1] % mod * fact[N - i - 1] % mod; 
    ret = (ret + acc[i] % mod * fpow(den, mod - 2) % mod) % mod; 
  } 
  for(int i = 1; i < N; i++) { 
    ret = ret % mod * (D - i) % mod; 
  }
  return ret;
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  cin >> M >> D; 
  for(int i = 2, x; i <= M; i++) { 
    cin >> x; 
    graph[x].push_back(i); 
  }
  dfs(1, 0); 
  for(int i = 0; i < sz(cc[1]); i++) {
    (acc[i] += (i ? acc[i - 1] : 0) + cc[1][i]) %= mod;  
  } 
  init(); 
  cout << Interpolation() << '\n'; 
  return 0; 
}

