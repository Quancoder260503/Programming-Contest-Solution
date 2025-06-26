#include <bits/stdc++.h> 

using namespace std; 

#define int64_t long long
#define sz(x) int(x.size())

const int MOD = 998244353; 

int main() {  
 int N, M; 
 cin >> N >> M; 
 vector<vector<int64_t>>ways(M + 1, vector<int64_t>(M + 1)); 
 ways[0][0] = 1; 
 for(int i = 0; i < M; i++) { 
  for(int j = 0; j <= i; j++) { 
   (ways[i + 1][j + 1] = ways[i + 1][j + 1] + ways[i][j]) %= MOD; 
   if(j) (ways[i + 1][j - 1] = ways[i + 1][j - 1] + ways[i][j]) %= MOD; 
  } 
 }
 vector<vector<int64_t>>dp(N + 1, vector<int64_t>(M + 1)); 
 dp[0][0] = 1; 
 for(int i = 0; i < N; i++) { 
  for(int j = 0; j <= M; j++) { 
   for(int extra = 0; extra <= M; extra++) { 
    int next_state = i ? j - extra : j + extra; 
    if(0 <= next_state && next_state <= M) { 
     (dp[i + 1][next_state] += dp[i][j] % MOD * ways[M][extra] % MOD) %= MOD; 
    } 
   } 
  } 
 }
 cout << dp[N][0] << '\n'; 
 return 0;
}