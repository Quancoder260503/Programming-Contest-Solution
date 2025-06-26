#include "bits/stdc++.h"

using namespace std; 

const int LOG  = 62; 
const int maxf = 12; 
const int mod = 1e9 + 7; 

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  int T; 
  cin >> T; 
  for(int iter = 0, N, M, Q; iter < T; iter++) { 
    cin >> N >> M >> Q; 
    vector<int64_t>dyn(1 << N), ret(N + 1); 
    vector<vector<int>>a(N, vector<int>(M)); 
    for(int i = 0; i < N; i++) { 
      for(int j = 0; j < M; j++) { 
        cin >> a[i][j]; 
      }
    }
    int64_t sum = 0; 
    for(int i = 0; i < M; i++) { 
      vector<pair<int, int>>cc; 
      for(int j = 0, x; j < N; j++) { 
        cc.push_back({a[j][i], j}); 
      }
      sort(cc.begin(), cc.end()); 
      sum += cc[N - 1].first; 
      for(int j = N - 1, mask = 0; j > 0; j--) { 
        mask |= (1 << cc[j].second); 
        dyn[mask] += cc[j].first - cc[j - 1].first; 
      }
    }
    for(int i = 0; i < N; i++) { 
      for(int mask = 0; mask < (1 << N); mask++) { 
        if(mask & (1 << i)) { 
          dyn[mask] += dyn[mask ^ (1 << i)];  
        }      
      }
    }
    for(int mask = 0; mask < (1 << N); mask++) { 
       int num = __builtin_popcount(mask);
       ret[N - num] = max(ret[N - num], dyn[mask]);    
    }
    for(int i = 0, x; i < Q; i++) { 
      cin >> x;   
      cout << sum - ret[x] << '\n'; 
    }
  }
  return 0; 
}