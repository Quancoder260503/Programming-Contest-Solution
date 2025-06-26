#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define int64_t long long

const int oo = 1e9; 

class Mercedes { 
  public:   
   void solve() { 
    int N; 
    cin >> N; 
    vector<vector<int>>g(N, vector<int>(N)); 
    for(int i = 0; i < N; i++) { 
     for(int j = 0; j < N; j++) { 
      cin >> g[i][j]; 
     }
    }
    // hey we only care about the last node, hence only need to know whether it is include or not 
    vector<vector<vector<int>>>dp(N, vector<vector<int>>(1 << N, vector<int>(2, oo))); 
    for(int i = 0; i < N; i++) {
      dp[i][1 << i][0] = 0; 
      dp[i][1 << i][1] = 1; 
    }
    for(int mask = 0; mask < (1 << N); mask++) { 
     for(int i = 0; i < N; i++) { 
      if(mask & (1 << i)) { 
       for(int j = 0; j < N; j++) { 
        if(mask & (1 << j)) continue; 
        if(g[i][j]) { 
         // there is a route from i->j
         dp[j][mask | (1 << j)][0] = min(dp[j][mask | (1 << j)][0], dp[i][mask][0]); 
         dp[j][mask | (1 << j)][1] = min(dp[j][mask | (1 << j)][1], 1 + dp[i][mask][1]); 
        } 
        if(g[j][i]) { 
         // there is a route from j->i (reverse it)
         dp[j][mask | (1 << j)][0] = min(dp[j][mask | (1 << j)][0], dp[i][mask][1]);
         dp[j][mask | (1 << j)][1] = min(dp[j][mask | (1 << j)][1], dp[i][mask][0] + 1);     
        }
       }
      }
     }
    }
    int ret = oo; 
    for(int i = 0; i < N; i++) { 
     ret = min({ret, dp[i][(1 << N) - 1][0], dp[i][(1 << N) - 1][1]}); 
    }
    if(ret == oo) cout << "life" << '\n';
    else cout << ret << '\n';  
    return; 
   }
};


int main(void) {  
 Mercedes problem; 
 problem.solve(); 
 return 0; 
}