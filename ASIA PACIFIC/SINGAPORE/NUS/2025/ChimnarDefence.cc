#include "bits/stdc++.h"
 
using namespace std; 
 
#define int64_t long long
#define sz(x) int(x.size())

const int64_t oo = 1e17; 
const int maxn = 1e4 + 2; 

int main(void) { 
  int N; 
  cin >> N; 
  vector<int>h(N), d(N), c(N); 

  for(int i = 0; i < N; i++) cin >> h[i]; 
  for(int i = 0; i < N; i++) cin >> d[i]; 
  for(int i = 0; i < N; i++) cin >> c[i]; 

  vector<vector<int64_t>>dp(N + 1, vector<int64_t>(maxn, -oo)); 
  dp[N][0] = 0; 
  for(int i = N - 1; i >= 0; i--) { 
   for(int j = 0; j < maxn; j++) { 
    dp[i][j] = dp[i + 1][j] + min(h[i], j); 
    if(j >= d[i]) { 
      dp[i][j] = max(dp[i][j], dp[i + 1][j - d[i]] + min(h[i], j) - c[i]);   
    }
   }
  }
  int64_t ret = -oo; 
  for(int w = 0; w < maxn; w++) {
   ret = max(ret, dp[0][w]); 
  }
  cout << ret << '\n'; 
  return 0; 
}