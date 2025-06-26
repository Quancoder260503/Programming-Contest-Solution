#include "bits/stdc++.h"

using namespace std;

int main(void) {
  ios_base::sync_with_stdio(0); 
  cin.tie(0); 
  cout.tie(0); 
  int N, M, K; 
  cin >> N >> M >> K; 
  vector<vector<vector<int>>>canReach(N + 1, vector<vector<int>>(M + 1, vector<int>(K + 1))); 
  canReach[0][M][K] = true; 
  for(int i = 1, x; i <= N; i++) { 
    cin >> x; 
    for(int j = 0; j <= M; j++) { 
      for(int k = 0; k <= K; k++) { 
        if(j >= x) { 
          canReach[i][j - x][k] |= canReach[i - 1][j][k]; 
        }
        if(k > 0) { 
          canReach[i][j][k - 1] |= canReach[i - 1][j][k]; 
        }
      }
    }
  }
  for(int i = N; i >= 0; i--) { 
    int flag = false; 
    for(int j = 0; j <= M; j++) { 
      for(int k = 0; k <= K; k++) { 
        if(canReach[i][j][k]) {
          flag = true; 
          break; 
        }
      }
      if(flag) break; 
    }
    if(flag) { 
      cout << i << '\n'; 
      return 0; 
    }
  }
  cout << 0 << '\n'; 
  return 0;
}