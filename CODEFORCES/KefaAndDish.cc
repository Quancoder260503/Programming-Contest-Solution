#include "bits/stdc++.h"

using namespace std; 

const int oo = 1e9 + 2; 

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N, M, K; 
  cin >> N >> M >> K; 
  vector<int>a(N); 
  vector<vector<int64_t>>g(N, vector<int64_t>(N)); 
  for(int i = 0; i < N; i++) { 
   cin >> a[i]; 
  }
  for(int i = 0, u, v, c; i < K; i++) { 
   cin >> u >> v >> c; 
   --u, --v; 
   g[u][v] = c; 
  }
  vector<vector<int64_t>>dp(N, vector<int64_t>(1 << N, -oo)); 
  for(int i = 0; i < N; i++) { 
   dp[i][1 << i] = a[i]; 
  }
  int64_t ret = 0; 
  for(int mask = 0; mask < (1 << N); mask++) { 
   for(int i = 0; i < N; i++) { 
    if(mask & (1 << i)) {
     for(int j = 0; j < N; j++) { 
      if(mask & (1 << j)) continue; 
      dp[j][mask | (1 << j)] = max(dp[j][mask | (1 << j)], dp[i][mask] + g[i][j] + a[j]); 
     }
    }
   }
   if(__builtin_popcount(mask) == M) { 
    for(int i = 0; i < N; i++) { 
      ret = max(ret, dp[i][mask]); 
    }
   }
  }
  cout << ret << '\n'; 
  return 0; 
}
