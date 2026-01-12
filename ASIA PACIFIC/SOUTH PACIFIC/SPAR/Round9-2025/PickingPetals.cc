#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int MOD = 1e9 + 7;
const int maxf = 2e5 + 10;

int64_t fact[maxf], ifact[maxf], fib[maxf];

int64_t Comb(int a, int b) {
  if (a < b || b < 0) return 0;
  return fact[a] % MOD * ifact[b] % MOD * ifact[a - b] % MOD;
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

void init(void) {
 fact[0] = ifact[0] = 1;
 for (int i = 1; i < maxf; i++) {
  fact[i]  = (fact[i - 1] * i) % MOD;
  ifact[i] = mod_inv(fact[i], MOD);
 }
 return;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0); 
  init();
  int n, m, k;
  cin >> n >> k >> m;
  vector<int>a(k);
  for(auto &x : a) cin >> x;
  vector<vector<int64_t>>dp(k + 1, vector<int64_t>(m + 1));
  int cnt = 0;
  dp[0][0] = 1;  
  for(int pos = 0; pos < k; pos++) { 
   for(int black = 0; black <= m; black++) { 
    for(int used_black = 0; black + used_black <= m && used_black <= a[pos]; used_black++) {  
     dp[pos + 1][black + used_black] += (dp[pos][black] * Comb(a[pos] - used_black + cnt - black, cnt - black)) % MOD;  
     dp[pos + 1][black + used_black] %= MOD; 
    }
   }
   cnt += a[pos];
  }
  int64_t ans = 0; 
  for(int j = 0; j <= m; j++) { 
   ans += dp[k][j]; 
   ans %= MOD;
  }
  cout << ans << '\n'; 
  //cout << dp[k][m] << '\n'; 
  return 0;
}