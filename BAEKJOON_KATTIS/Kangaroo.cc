#include "bits/stdc++.h"

using namespace std; 

const int MOD = 1e9 + 7; 

int main(void) {
  int N, start, end;
  cin >> N >> start >> end; 
  vector<vector<int64_t>>dp(N + 1, vector<int64_t>(N + 1)); 
  dp[1][1] = 1; 
  for(int i = 2; i <= N; i++) { 
   for(int j = 1; j <= i; j++) { 
    if(i == start || i == end) { 
      (dp[i][j] += dp[i - 1][j - 1] + dp[i - 1][j]) %= MOD;
    } 
    else { 
      (dp[i][j] += dp[i - 1][j + 1] % MOD * j % MOD + 
                   dp[i - 1][j - 1] % MOD * (j - (i > start) - (i > end)) % MOD) %= MOD; 
    }
   }
  }
  cout << dp[N][1] << '\n'; 
  return 0; 
}

/**
 */