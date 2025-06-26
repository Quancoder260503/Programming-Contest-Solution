#include <bits/stdc++.h> 

using namespace std; 

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

int main() { 
 int N, M, K; 
 cin >> N >> M >> K; 
 vector<vector<int64_t>>dp(K + 1, vector<int64_t>(K + 1)); 
 dp[0][0] = 1;
 for(int pos = 0; pos < K; pos++) { 
  for(int distinct = 0; distinct <= K; distinct++) { 
   (dp[pos + 1][distinct] += distinct * dp[pos][distinct]) %= MOD; 
   if(distinct < K) (dp[pos + 1][distinct + 1] += max(0, N - distinct) % MOD * dp[pos][distinct] % MOD) %= MOD; 
  } 
 }
 int64_t ret = 0; 
 for(int distinct = 1; distinct <= K; distinct++) { 
  int64_t den = mod_pow(M, distinct, MOD); 
  (ret += dp[K][distinct] % MOD * mod_inv(den, MOD) % MOD) %= MOD; 
 } 
 cout << ret << '\n'; 
 return 0;
}
