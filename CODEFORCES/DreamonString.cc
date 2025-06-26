#include "bits/stdc++.h"
 
using namespace std; 
 
#define sz(x) int(x.size())

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  string S, P; 
  cin >> S >> P; 
  int N = sz(S); 
  vector<int>a(N, -1); 
  for(int i = 0; i < N; i++) { 
    int state = i; 
    int stateP; 
    for(stateP = 0; stateP < sz(P); stateP++) { 
      while(state < N && P[stateP] != S[state]) state++; 
      if(state == N) break; 
      else state++; 
    }
    if(stateP == sz(P)) {
      a[i] = state - i; 
    }
  }
  vector<vector<int>>dyn(N + 1, vector<int>(N + 1)); 
  for(int i = 0; i < N; i++) { 
    for(int j = 0; j <= i; j++) {
      dyn[i + 1][j]     = max(dyn[i][j], dyn[i + 1][j]); 
      dyn[i + 1][j + 1] = max(dyn[i + 1][j + 1], dyn[i][j]); 
      if(a[i] >= 0) { 
        dyn[i + a[i]][j + a[i] - sz(P)] = max(dyn[i + a[i]][j + a[i] - sz(P)], dyn[i][j] + 1); 
      }
    }
  }
  for(int i = 0; i <= N; i++) { 
    cout << dyn[N][i] << " "; 
  }
  return 0; 
}