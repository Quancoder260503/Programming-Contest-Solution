#include "bits/stdc++.h"

using namespace std; 

const int oo = 1e9; 

int main(void) { 
 int N, M; 
 cin >> N >> M; 
 vector<vector<int>>dp(N + 1, vector<int>(M + 1, -oo)); 
 dp[N][M] = 0; 
 for(int i = N; i >= 0; i--) { 
  for(int j = M; j >= 0; j--) { 
   if(i < N) { 
    dp[i][j] = max(dp[i][j], 1 + dp[i + 1][j]); 
    if(j < M) dp[i][j] = max(dp[i][j], 10 + dp[i + 1][j + 1]); 
   }
   if(i + 1 < N) dp[i][j] = max(dp[i][j], 3 + dp[i + 2][j]); 
   if(i + 2 < N) dp[i][j] = max(dp[i][j], 10 + dp[i + 3][j]);
  }
 }
 cout << max(0, *max_element(dp[0].begin(), dp[0].end())) << '\n'; 
 return 0;
}