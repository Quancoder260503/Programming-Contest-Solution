#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int MOD = 1e9 + 7;

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  string S, T; 
  cin >> S >> T; 
  int N = sz(S), M = sz(T); 
  vector<vector<int64_t>>dp(N + 1, vector<int64_t>(M + 1)); 
  int64_t ret = 0; 
  for(int i = 1; i <= N; i++) { 
   for(int j = 1; j <= M; j++) { 
    (dp[i][j] += dp[i][j - 1]) %= MOD; 
    if(S[i - 1] == T[j - 1]) { 
     (dp[i][j] += dp[i - 1][j - 1] + 1) %= MOD;
    }
   }
  }
  for(int i = 0; i <= N; i++) { 
   (ret += dp[i][M]) %= MOD; 
  }
  cout << ret << '\n'; 
  return 0; 
}

/**
 * dp[i][j] = {number of substring ends with i-th in S that matches a subsequence ending at j-th in T} 
 * dp[i][j] = dp[i - 1][j - 1] (S[i] == T[j]) 
 * dp[i][j] = dp[i][j - 1]     if(S[i] != T[j])
 * 
 * 
 */