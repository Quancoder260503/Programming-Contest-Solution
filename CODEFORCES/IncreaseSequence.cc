#include "bits/stdc++.h"
 
using namespace std; 
 
const int MOD = 1e9 + 7; 
 
int main() {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N, H; 
  cin >> N >> H;
  vector<int>a(N); 
  for(int i = 0; i < N; i++) { 
    cin >> a[i]; 
  } 
  vector<vector<int64_t>>dp(N + 1, vector<int64_t>(N + 1));
  dp[0][0] = 1; 
  // number of ways to fill up 
  for(int i = 0; i < N; i++) { 
    if(H - a[i] >= 0) { 
      (dp[i + 1][H - a[i]] += dp[i][H - a[i]]) %= MOD; 
      if(H - a[i] > 0)      (dp[i + 1][H - a[i] - 1] += dp[i][H - a[i]]  % MOD * (H - a[i]) % MOD) %= MOD; 
    } 
    if(0 <= H - a[i] - 1 && H - a[i] - 1 <= i) { 
      (dp[i + 1][H - a[i]]     += dp[i][H - a[i] - 1]) %= MOD;
      (dp[i + 1][H - a[i] - 1] += dp[i][H - a[i] - 1] % MOD * (H - a[i]) % MOD) %= MOD; 
    }
  } 
  cout << dp[N][0] << '\n'; 
  return 0; 
}