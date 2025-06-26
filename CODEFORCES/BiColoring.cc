#include <bits/stdc++.h> 

using namespace std; 

#define sz(x) int(x.size())

const int MOD = 998244353; 

int main() {
 int N, K; 
 cin >> N >> K; 
 vector<vector<vector<int64_t>>>dp(N + 1, vector<vector<int64_t>>(K + 10, vector<int64_t>(4))); 
 dp[1][1][0] = dp[1][2][1] = dp[1][2][2] = dp[1][1][3] = 1; 
 for(int i = 1; i < N; i++) { 
  for(int comp = 0; comp <= K; comp++) { 
   (dp[i + 1][comp][3] += dp[i][comp][1] + dp[i][comp][2] + dp[i][comp][3]) %= MOD; 
   (dp[i + 1][comp][2] += dp[i][comp][2]) %= MOD;
   (dp[i + 1][comp][1] += dp[i][comp][1]) %= MOD; 
   (dp[i + 1][comp][0] += dp[i][comp][0] + dp[i][comp][1] + dp[i][comp][2]) %= MOD; 
   if(comp < K) { 
    (dp[i + 1][comp + 1][3] += dp[i][comp][0]) %= MOD; 
    (dp[i + 1][comp + 1][2] += dp[i][comp][0] + dp[i][comp][3]) %= MOD; 
    (dp[i + 1][comp + 1][1] += dp[i][comp][0] + dp[i][comp][3]) %= MOD; 
    (dp[i + 1][comp + 1][0] += dp[i][comp][3]) %= MOD; 
   }
   if(comp + 1 < K) { 
    (dp[i + 1][comp + 2][2] += dp[i][comp][1]) %= MOD; 
    (dp[i + 1][comp + 2][1] += dp[i][comp][2]) %= MOD; 
   } 
  } 
 }
 int64_t ret = 0; 
 for(int i = 0; i < 4; i++) { 
  (ret += dp[N][K][i]) %= MOD; 
 } 
 cout << ret << '\n'; 
 return 0;
}
