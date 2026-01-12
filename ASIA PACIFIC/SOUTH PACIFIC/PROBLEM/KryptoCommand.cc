#include "bits/stdc++.h"

using namespace std; 

// choose with replacement a sequence 

const int MOD = 1e9 + 7; 
const int maxn = 1e6 + 2; 
const int LOG = 32; 

int64_t cache[maxn][LOG], fact[maxn], ifact[maxn]; 
int64_t dp[maxn]; 
int n, max_value; 

int64_t memo(int num, int c) { 
 if(c == 0) return 1; 
 if(cache[num][c] != -1) return cache[num][c]; 
 int64_t &ret = cache[num][c]; 
 ret = 0; 
 for(int i = 2 * num; i <= max_value; i += num) {  
  ret += memo(i, c - 1);   
 }
 return ret; 
}

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

int64_t Comb(int64_t a, int64_t b) { 
 if(b < 0 || a < b) return 0; 
 return fact[a] % MOD * ifact[b] % MOD * ifact[a - b] % MOD; 
}

int main(void) { 
 fact[0] = ifact[0] = 1; 
 for(int i = 1; i < maxn; i++) { 
  fact[i] = fact[i - 1] * i % MOD; 
  ifact[i] = mod_inv(fact[i], MOD); 
 }
 cin >> n >> max_value;
 memset(cache, -1, sizeof cache);
 int64_t ans = 0; 
 for(int i = max_value; i > 0; i--) { 
  for(int j = 1; j <= LOG; j++) { 
   (dp[i] += memo(i, j - 1) % MOD * Comb(n - 1, j - 1) % MOD) %= MOD; 
  }
  (ans += dp[i]) %= MOD; 
 }
 cout << ans << '\n'; 
 return 0; 
}

/**
 * Comb(cnt[i], k) *  Comb(n - 1, k - 1) 
 * Let x[1] + x[2] + ... + x[cnt[i]] = n  // some of them can smaller than.  
 * Comb(n - 1, k - 1)
 * 
 * dp[i][gcd()] = dp[i - 1][ ]
 */