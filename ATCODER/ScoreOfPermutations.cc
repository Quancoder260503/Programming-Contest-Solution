#include "bits/stdc++.h"

using namespace std;

#define int64_t long long
#define sz(x) int(x.size())

const int MOD = 998244353; 

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
 int N, K; 
 cin >> N >> K; 
 vector<vector<int64_t>>Comb(2 * N, vector<int64_t>(2 * N)); 
 vector<int64_t>fact(2 * N); 
 Comb[0][0] = fact[0] = 1; 
 for(int i = 1; i < sz(Comb); i++) { 
  for(int j = 0; j <= i; j++) { 
   Comb[i][j] = Comb[i - 1][j] + (j ? Comb[i - 1][j - 1] : 0); 
   Comb[i][j] %= MOD; 
  }
  fact[i] = 1LL * fact[i - 1] % MOD * i % MOD; 
 }
 vector<map<int64_t, int64_t>>dp(N + 1); 
 dp[0][1] = 1; 
 for(int filled = 0; filled <= N; filled++) { 
  for(int rem = 1; rem <= N - filled; rem++) { 
   for(auto [curr, ways] : dp[filled]) { 
     (dp[filled + rem][lcm(curr, rem)] += ways % MOD * 
                                          Comb[N - filled - 1][rem - 1] % MOD * 
                                          fact[rem - 1] % MOD) %= MOD; 
   }
  }
 }
 int64_t ret = 0; 
 for(auto [curr, ways] : dp[N]) { 
  (ret += 1LL * ways % MOD * mod_pow(curr, K, MOD) % MOD) %= MOD; 
 }
 cout << ret << '\n'; 
 return 0; 
}