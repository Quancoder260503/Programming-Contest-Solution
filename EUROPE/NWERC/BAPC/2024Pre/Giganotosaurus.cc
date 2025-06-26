#include "bits/stdc++.h"
using namespace std; 

#define sz(x) int(x.size())

const int MOD = 1e9 + 7; 

class Giganotosaurus { 
public: 
  void solve() { 
   int N; 
   string S;
   cin >> N >> S;  
   // dp[i][j] = {num ways to reach the ith-cells know that the last jump is j}
   int n = int(sqrt(N)) + 300; 
   vector<vector<int64_t>>dp(N + 1, vector<int64_t>(n + 1)); 
   dp[0][0] = 1; 
   S = S + " "; 
   for(int pos = 0; pos < N; pos++) {
    for(int jump = 0; jump < n; jump++) { 
     if(S[min(N, pos + 1)] != '#') { 
      (dp[min(N, pos + 1)][jump] += dp[pos][jump]) %= MOD; 
     }
     if(S[min(N, pos + jump + 2)] != '#') { 
      (dp[min(N, pos + (jump + 1) + 1)][jump + 1] += dp[pos][jump]) %= MOD;   
     }  
    }
   }
   int64_t ans = 0; 
   for(int jump = 0; jump <= n; jump++) { 
    (ans += dp[N][jump]) %= MOD; 
   }
   cout << ans << '\n'; 
   return; 
  }
}; 

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 Giganotosaurus gigano; 
 gigano.solve(); 
 return 0; 
}