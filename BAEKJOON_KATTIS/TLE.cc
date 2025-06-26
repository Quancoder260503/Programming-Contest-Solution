#include "bits/stdc++.h"

using namespace std;

const int MOD = 1e9; 

void solve() { 
 int N, M; 
 cin >> N >> M; 
 vector<int>c(N); 
 for(int i = 0; i < N; i++) { 
  cin >> c[i]; 
 }
 vector<int64_t>dp(1 << M); 
 for(int i = 1; i < (1 << M); i++) { 
  if(i % c[0]) { 
   dp[i]++; 
  }
 }
 for(int i = 1; i < N; i++) { 
  vector<int64_t>ndp(1 << M); 
  for(int j = 0; j < M; j++) { 
   for(int mask = 0; mask < (1 << M); mask++) { 
    if(mask & (1 << j)) { 
     (dp[mask] += dp[mask ^ (1 << j)]) %= MOD; 
    } 
   }
  }
  for(int mask = 1; mask < (1 << M); mask++) { 
   if(mask % c[i]) { 
    (ndp[mask] += dp[mask ^ ((1 << M) - 1)]) %= MOD; 
   }
  }
  ndp.swap(dp); 
 }
 int64_t ans = 0; 
 for(int mask = 1; mask < (1 << M); mask++) { 
  (ans += dp[mask]) %= MOD; 
 }
 cout << ans << '\n'; 
 return; 
}

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int T; 
  for(cin >> T; T--; ) { solve(); }
  return 0; 
}

