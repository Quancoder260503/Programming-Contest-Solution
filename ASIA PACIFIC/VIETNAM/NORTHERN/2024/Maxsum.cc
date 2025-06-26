#include "bits/stdc++.h"

using namespace std; 

#define int64_t long long 
#pragma GCC optimize("O3")
#pragma GCC optimization("Ofast,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

int64_t ind[1000001], mp[1000001]; 

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N, M, K; 
 cin >> N >> M >> K;  
 vector<vector<int>>g(N + 1, vector<int>(M + 1));
 for(int i = 1; i <= N; i++) { 
  for(int j = 1; j <= M; j++) { 
   cin >> g[i][j];
  }
 }    
 int64_t ans = 0; 
 if(N > M) {
  vector<vector<int>>buffer(M + 1, vector<int>(N + 1)); 
  for(int i = 1; i <= N; i++) { 
   for(int j = 1; j <= M; j++) { 
    buffer[j][i] = g[i][j]; 
   }
  }
  swap(N, M); 
  swap(g, buffer); 
 } 
 vector<vector<int64_t>>dp(N + 1, vector<int64_t>(M + 1)); 
 for(int c = 1; c <= M; c++) { 
  for(int r = 1; r <= N; r++) { 
   dp[r][c] = (dp[r - 1][c] + g[r][c]); 
  }
 }
 int cc = 0;  
 for(int rowA = 1; rowA <= N; rowA++) { 
  int turn = 0; 
  for(int rowB = N; rowB >= rowA; rowB--) { 
   int64_t acc = 0; 
   cc++; 
   ind[acc] = cc;  
   for(int col = 1; col <= M; col++) { 
    acc += dp[rowB][col] - dp[rowA - 1][col]; 
    if(ind[acc % K] == cc)  ans = max(ans, acc - mp[acc % K]); 
    else { 
     ind[acc % K] = cc; 
     mp[acc % K] = acc; 
    } 
   }
   turn++; 
   if(turn == 180) break; 
  }
 }  
 cout << ans << '\n'; 
 return 0; 
} 