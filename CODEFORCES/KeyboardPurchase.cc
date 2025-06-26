#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int64_t oo = 1e12; 

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);  
 int N, M; 
 string S; 
 cin >> N >> M >> S;
 vector<vector<int>>g(M, vector<int>(M)); 
 for(int i = 1; i < sz(S); i++) { 
  g[S[i] - 'a'][S[i - 1] - 'a']++; 
  g[S[i - 1] - 'a'][S[i] - 'a']++; 
 }
 vector<int64_t>dp(1 << M, oo); 
 dp[0] = 0; 
 for(int mask = 0; mask < (1 << M); mask++) {
  int pos = __builtin_popcount(mask) + 1; 
  for(int i = 0; i < M; i++) { 
   if(mask & (1 << i)) continue; 
   int total_lower = 0, total_larger = 0; 
   for(int j = 0; j < M; j++) { 
    if(mask & (1 << j)) { 
      total_lower   += g[i][j]; 
    } else if(i != j) { 
      total_larger  += g[i][j]; 
    } 
   }
   dp[mask | (1 << i)] = min(dp[mask | (1 << i)], dp[mask] - pos * total_larger + pos * total_lower); 
  }
 }
 cout << dp[(1 << M) - 1] << '\n'; 
 return 0; 
}