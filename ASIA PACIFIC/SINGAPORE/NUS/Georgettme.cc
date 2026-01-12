#include "bits/stdc++.h"

using namespace std; 

const int maxn = 1e6 + 2; 

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N, T, K, MOD ; 
 // no modulo inverse 
 cin >> T >> MOD; 
 vector<int64_t>dp(maxn + 1), fact(maxn + 1); 
 dp[0] = fact[0] = dp[1] = 1; 
 for(int i = 1; i < maxn; i++) {
  fact[i] = fact[i - 1] % MOD * i % MOD; 
  if(i >= 2) (dp[i] += dp[i - 1] + (i - 1) * dp[i - 2]) %= MOD; 
 }
 for(; T--; ) { 
  cin >> N; 
  cout << (fact[N] - dp[N] + MOD) % MOD << '\n';  
 }
 return 0; 
}