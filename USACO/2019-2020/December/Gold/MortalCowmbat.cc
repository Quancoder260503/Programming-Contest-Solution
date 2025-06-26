#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int oo = 1e9; 
const int MOD = 1e9 + 7;

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N, M, K; 
 cin >> N >> M >> K;
 string S; 
 cin >> S; 
 vector<vector<int>>g(M, vector<int>(M)); 
 for(int i = 0; i < M; i++) { 
  for(int j = 0; j < M; j++) { 
   cin >> g[i][j]; 
  }
 }
 for(int k = 0; k < M; k++) { 
  for(int i = 0; i < M; i++) { 
   for(int j = 0; j < M; j++) { 
    g[i][j] = min(g[i][j], g[i][k] + g[k][j]); 
   }
  }
 }
 // cost to make certain prefix the same 
 vector<vector<int>>cost(N + 1, vector<int>(M + 1, oo)); 
 for(int i = 0; i <= N; i++) { 
  int c = S[i - 1] - 'a'; 
  for(int j = 0; j < M; j++) {
   cost[i][j] = (i ? cost[i - 1][j] + g[c][j] : 0); 
  }
 }
 vector<vector<int>>dp(N + 1, vector<int>(M + 1, oo)); 
 vector<int>opt(N + 1, oo); 
 opt[0] = 0; 
 for(int i = 1; i <= N; i++) { 
  for(int j = 0; j < M; j++) { 
   dp[i][j] = min(dp[i][j], dp[i - 1][j] + g[S[i - 1] - 'a'][j]); 
   if(i >= K) { 
    dp[i][j] = min(dp[i][j], opt[i - K] + cost[i][j] - cost[i - K][j]); 
   } 
   opt[i] = min(opt[i], dp[i][j]); 
  }  
 }
 cout << opt.back() << '\n'; 
 return 0; 
}
