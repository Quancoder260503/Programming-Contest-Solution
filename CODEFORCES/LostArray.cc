#include <bits/stdc++.h> 

using namespace std; 

const int MOD = 1e9 + 7; 

int main() {
 int N, L, R; 
 cin >> N >> L >> R; 
 vector<vector<int64_t>>dp(N + 1, vector<int64_t>(3)); 
 dp[0][0] = 1; 
 auto func = [&](int L, int R) {
  if(max(L, R) < 0) return 0; 
  L = max(L, 0), R = max(R, 0); 
  int x = R / 3, y = L / 3; 
  if(L % 3 == 0) return x - y + 1; 
  return x - y; 
 }; 
 for(int i = 1; i <= N; i++) { 
  (dp[i][0] += dp[i - 1][0] % MOD * func(L, R) % MOD + 
               dp[i - 1][2] % MOD * func(L - 1, R - 1) % MOD + 
               dp[i - 1][1] % MOD * func(L - 2, R - 2) % MOD) %= MOD; 
  (dp[i][1] += dp[i - 1][1] % MOD * func(L, R) % MOD + 
               dp[i - 1][0] % MOD * func(L - 1, R - 1) % MOD + 
               dp[i - 1][2] % MOD * func(L - 2, R - 2) % MOD) %= MOD; 
  (dp[i][2] += dp[i - 1][2] % MOD * func(L, R) % MOD + 
               dp[i - 1][1] % MOD * func(L - 1, R - 1) % MOD + 
               dp[i - 1][0] % MOD * func(L - 2, R - 2) % MOD) %= MOD; 
  //cout << dp[i][0] << " " << dp[i][1] << " " << dp[i][2] << '\n'; 
 } 
 cout << dp[N][0] << '\n'; 
 return 0;
}