#include "bits/stdc++.h"

using namespace std;

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N, Q; 
  string S; 
  cin >> S;
  N = S.size(); 
  vector<vector<int>>palin(N, vector<int>(N, false)); 
  for(int i = 0; i < N; i++) { 
    palin[i][i] = true; 
  }
  for(int i = N - 1; i >= 0; i--) { 
    for(int j = i; j < N; j++) if(S[i] == S[j]) {
      if(j == i + 1 || j == i) { palin[i][j] = true; }
      else { 
        palin[i][j] = palin[i + 1][j - 1]; 
      } 
    }
  }
  vector<vector<int>>dyn(N, vector<int>(N)); 
  for(int i = N - 1; i >= 0; i--) { 
    for(int j = i; j < N; j++) { 
      dyn[i][j] = palin[i][j]; 
      if(i < j) { 
        dyn[i][j] += dyn[i + 1][j] + dyn[i][j - 1]; 
      }
      if(i + 1 <= j - 1) { 
        dyn[i][j] += - dyn[i + 1][j - 1]; 
      }
    }
  }
  cin >> Q; 
  for(int i = 0, l, r; i < Q; i++) { 
    cin >> l >> r; 
    --l, --r; 
    cout << dyn[l][r] << '\n'; 
  }
  return 0; 
}