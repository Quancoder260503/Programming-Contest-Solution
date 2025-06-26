#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())
#define ctoi(x) x - 'a'

const int MOD = 998244353; 

#define int64_t long long
#define sz(x) int(x.size())

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

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);  
 int N, M; 
 cin >> N >> M; 
 vector<int64_t>fact(N + 1); 
 fact[0] = 1; 
 for(int i = 1; i < sz(fact); i++) {
  fact[i] = (fact[i - 1] * i) % MOD; 
 }
 vector<vector<int>>g(M);
 for(int i = 0; i < N; i++) { 
  for(int j = 0, x; j < M; j++) { 
   cin >> x; 
   g[j].push_back(x); 
  }
 }
 int64_t ans = 0; 
 for(int i = 0; i < M; i++) { 
  vector<int64_t>d(N + 1), cnt(N + 1); 
  for(int j = 0; j < N; j++) { 
   cnt[N + 1 - g[i][j]]++; 
  }
  d[0] = 1; 
  int64_t ret = 0; 
  for(int i = 0; i < N; i++) { 
   ret += cnt[i]; 
   (d[i + 1] += d[i] % MOD * ret % MOD) %= MOD;
   ret = max(0LL, ret - 1); 
  }
  (ans += 1 + MOD - d[N] % MOD * mod_inv(fact[N], MOD) % MOD) %= MOD; 
 }
 cout << ans << '\n'; 
 return 0; 
}

/**
 * 
 *
 Linearity of expectation, Let X be the r.v. of the events then 
 E(X[1] + ... + X[m]) = E(X[1]) + ... + E(X[m])
 E(X[i]) = P(X[i]) = P(X[i] first hit by N) * P(Turn of N = dist[N][X[i]]) // This like the 


 1 + 0 + 1 + (1 / 3) + (7 / 6) 
**/ 