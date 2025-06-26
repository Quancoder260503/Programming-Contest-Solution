#include <bits/stdc++.h>

using namespace std; 

const int MOD= 1e9 + 7;

int main() { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N, M, K;
 cin >> N >> M >> K;
 vector<vector<vector<vector<int64_t>>>>dp(N + 1, 
                                           vector<vector<vector<int64_t>>>(M + 1, 
                                           vector<vector<int64_t>>(N + 1,    
                                           vector<int64_t>(2))));
 dp[0][0][0][0] = 1; 
 for(int line = 1; line <= M; line++) { 
  for(int pos = 0; pos <= N; pos++) { 
   for(int open = N; open >= 0; open--) { 
    if(line < K) { 
     dp[pos][line][open][0] += dp[pos][line - 1][open][0]; 
     if(pos < N && open == 0) dp[pos + 1][line][open][0] += dp[pos][line - 1][open][0]; 
     if(pos < N && open <  N) dp[pos + 1][line][open][0] += dp[pos][line - 1][open + 1][0]; 
     if(open > 0) dp[pos][line][open][0] += dp[pos][line][open - 1][0] + dp[pos][line - 1][open - 1][0];
    } else if(line == K) { 
     if(open > 0) dp[pos][line][open][1] += dp[pos][line - 1][open - 1][0] + dp[pos][line][open - 1][0]; 
     if(pos < N && open == 0) dp[pos + 1][line][open][1] += dp[pos][line - 1][open][0]; 
    } else { 
     dp[pos][line][open][1] += dp[pos][line - 1][open][1]; 
     if(pos < N && open == 0) { 
      dp[pos + 1][line][open][1] += dp[pos][line - 1][open][1]; 
     }
     if(pos < N &&  open < N) { 
      dp[pos + 1][line][open][1] += dp[pos][line - 1][open + 1][1]; 
     }
     if(open > 0) { 
      dp[pos][line][open][1] += dp[pos][line][open - 1][1] + dp[pos][line - 1][open - 1][1];
     }
    } 
   } 
  } 
 } 
 int64_t ret = 0; 
 for(int i = 0; i <= M; i++) { 
  (ret += dp[N][i][0][1]) %= MOD; 
 } 
 cout << dp[1][2][1][1] << '\n'; 
 cout << ret << '\n'; 
 return 0;
}


/*
* dp[i][j][k][l] 
* [1, 1] -> 3 // singular interval 
* [1, 1] -> [2, 3] -> [4, 4]
* [1, 1] -> [2, 2] -> [3, 4]
* [1, 2] -> [3, 3] -> [4, 4]
* [1, 2] -> [2, 3] -> [4, 4]
*/


