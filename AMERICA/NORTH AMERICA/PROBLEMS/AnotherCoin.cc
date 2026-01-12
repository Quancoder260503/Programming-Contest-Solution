#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define int64_t long long

const int maxn = 1e6 + 2; 
const int MOD = 998244353; 

int64_t dp[maxn]; 
int m, k; 

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

int64_t f(int64_t x) { 
 if(dp[x] != -1) return dp[x]; 
 if(x == 1) { 
  return (mod_pow(3, m, MOD) - 1 + MOD) % MOD; 
 }
 int64_t &ret = dp[x]; 
 if(ret != -1) return ret; 
 ret = mod_pow(2 * x + 1, m, MOD) - 1; 
 for(int i = 2; i <= x; i++) { 
  (ret += MOD - f(x / i)) %= MOD; 
 }
 return ret; 
}

int main(void) {
  ios_base::sync_with_stdio(0); 
  cin.tie(0); 
  cout.tie(0); 
  cin >> m >> k; 
  memset(dp, -1, sizeof dp); 
  cout << (1 + f(k)) % MOD << '\n'; 
  return 0; 
}
