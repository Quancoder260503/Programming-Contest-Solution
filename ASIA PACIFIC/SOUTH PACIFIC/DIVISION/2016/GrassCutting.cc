#include "bits/stdc++.h"

using namespace std; 

const int oo = 1e7; 

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int K = 10;
  vector<vector<int>>g(K, vector<int>(K, 1));  
  int N; 
  cin >> N; 
  for(int _ = 0; _ < N; _++) { 
    for(int i = 0; i < K; i++) { 
      for(int j = 0; j < K; j++) { 
        g[i][j]++; 
      }
    }
    int r1, r2, r3, c1, c2, c3;
    cin >> r1 >> r2 >> r3 >> c1 >> c2 >> c3;
    --r1, --r2, --r3, --c1, --c2, --c3; 
    for(int i = 0; i < K; i++) { 
      g[r1][i] = 1; 
      g[r2][i] = 1; 
      g[r3][i] = 1;
      g[i][c1] = 1; 
      g[i][c2] = 1; 
      g[i][c3] = 1; 
    }
  }
  for(int i = 0; i < K; i++) { 
    for(int j = 0; j < K; j++) { 
      cout << g[i][j] << " "; 
    }
    cout << '\n'; 
  }
  return 0; 
}
