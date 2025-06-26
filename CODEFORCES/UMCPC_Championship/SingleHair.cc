#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define int64_t long long

const int64_t oo = 1e18; 

class SingleHair { 
  public:   
   void solve() { 
    int N, M, X; 
    cin >> N >> M >> X; 
    vector<int64_t>a(M); 
    for(int i = 0; i < M; i++) { 
     cin >> a[i]; 
    }
    vector<vector<int64_t>>dp(N + 2, vector<int64_t>(N + 1, -oo)); 
    dp[0][0] = a[0]; 
    for(int pos = 0; pos < N; pos++) { 
     for(int hair_len = 0; hair_len <= N; hair_len++) { 
      dp[pos + 1][hair_len + 1] = max(dp[pos][hair_len] + (hair_len + 1 < M ? a[hair_len + 1] : 0),
                                      dp[pos + 1][hair_len + 1]); 
      for(int next_len = 0; next_len <= hair_len; next_len++) { 
       dp[pos + 1][next_len] = max(dp[pos][hair_len] + (next_len < M ? a[next_len] : 0) - X, 
                                   dp[pos + 1][next_len]);
      }
     }
    }
    int64_t ans = 0;  
    for(int i = 0; i <= N; i++) { 
     ans = max(ans, dp[N - 1][i]); 
    }
    cout << ans << '\n'; 
    return; 
   }
};


int main(void) {  
 SingleHair Problem; 
 int T; 
 for(cin >> T; T--; ) { 
  Problem.solve(); 
 } 
 return 0; 
}