#include "bits/stdc++.h"

using namespace std; 

const int MOD = 998244353; 

int main(void) {  
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int T; 
 for(cin >> T; T--; ) { 
  int N, K; 
  cin >> N >> K; 
  vector<vector<int64_t>>dp(N + 1, vector<int64_t>(K + 1)); 
  for(int i = 0; i < K; i++) { 
    dp[0][i] = 1; 
  }
  for(int sum = 1; sum <= N; sum++) { 
   for(int prev_sz = 0; prev_sz <= K; prev_sz++) { 
    for(int curr_sz = 0; (curr_sz + 1) * (prev_sz + 1) <= sum && curr_sz + prev_sz < K; curr_sz++) { 
      (dp[sum][curr_sz] += dp[sum - (curr_sz + 1) * (prev_sz + 1)][prev_sz]) %= MOD; 
    }
   }
  }
  int64_t ans = 0; 
  for(int i = 0; i <= K; i++) { 
   (ans += dp[N][i]) %= MOD;  
  }
  cout << ans << '\n'; 
 } 
 return 0;
}