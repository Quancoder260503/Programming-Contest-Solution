#include "bits/stdc++.h"

using namespace std; 

int64_t dp[1 << 9][101][101][2];

const int64_t oo = INT_MAX; 

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N, K, M, T; 
  for(cin >> T; T--; ) { 
   cin >> K >> M >> N;
   vector<int>E(N), P(N); 
   for(int i = 0; i < N; i++) { 
    cin >> E[i]; 
   }
   for(int i = 0; i < N; i++) { 
    cin >> P[i]; 
   }
#define MAX 101
   for(int i = 0; i < (1 << 9); i++) { 
    for(int j = 0; j < MAX; j++) { 
     for(int k = 0; k < MAX; k++) { 
      dp[i][j][k][0] = dp[i][j][k][1] = -oo; 
     }
    }
   }
   dp[0][100][0][0] = 0; 
   for(int mask = 0; mask < (1 << N); mask++) { 
    for(int energy = MAX - 1; energy > 0; energy--) { 
     for(int toxic = MAX - 2; toxic >= 0; toxic--) { 
      for(int used = 0; used < 2; used++) { 
        if(dp[mask][energy][toxic][used] < 0) continue; 
        if(energy > K) { 
         int64_t &ret = dp[mask][energy - K][max(0, toxic - M)][0]; 
         ret = max(ret, dp[mask][energy][toxic][used] + 1); 
        }
        if(!used) { 
         for(int i = 0; i < N; i++) { 
          if(mask & (1 << i)) continue; 
          if(toxic + P[i] < 100) { 
           int64_t &ret = dp[mask | (1 << i)][min(energy + E[i], 100)][toxic + P[i]][1]; 
           ret = max(ret, dp[mask][energy][toxic][used]);  
          }
        } 
      }
     }
    }
   }
  }
  int64_t ret = -oo; 
  for(int mask = 0; mask < (1 << N); mask++) { 
   for(int i = 1; i < MAX; i++) { 
    for(int j = 0; j < MAX - 1; j++) { 
     ret = max(ret, dp[mask][i][j][0]); 
     ret = max(ret, dp[mask][i][j][1]);
    }  
   }
  }
  cout << ret << '\n'; 
 }
 return 0; 
}
