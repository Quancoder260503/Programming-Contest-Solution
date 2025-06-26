#include "bits/stdc++.h"

using namespace std; 

const int maxf = 7000; 
const int oo = 1e8;

int N, D, K, dyn[maxf][maxf]; 

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  cin >> N >> D >> K;  
  vector<int>w(N); 
  for(int i = 0; i < N; i++) { 
    cin >> w[i]; 
  }
  for(int i = N - 1; i >= 0; i--) { 
    for(int j = D - 1; j >= 0; j--) { 
      dyn[i][j] = max(dyn[i + 1][j], dyn[i][j]); 
      for(int k = 1; k <= K; k++) { 
        if(i + 2 * k - 1 < N && j + k <= D) { 
          dyn[i][j] = max(dyn[i][j], w[i + 2 * k - 1] * k + 
                                    (i + 2 * k == N || k + j == D ? 0 : dyn[i + 2 * k][k + j])); 
        }
      }
    }
  }
  cout << dyn[0][0] << '\n'; 
  return 0; 
}

