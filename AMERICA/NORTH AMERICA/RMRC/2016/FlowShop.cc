#include "bits/stdc++.h"

using namespace std; 

const int oo = 2e9;

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N, M; 
  cin >> N >> M; 
  vector<vector<int>>cost(N + 1, vector<int>(M + 1));
  vector<vector<int>>dyn(N + 1, vector<int>(M + 1)); 
  for(int i = 1; i <= N; i++)
  for(int j = 1; j <= M; j++) { 
    cin >> cost[i][j]; 
    dyn[i][j] = oo; 
  }
  for(int i = 1; i <= N; i++) 
  for(int j = 1; j <= M; j++) { 
    dyn[i][j] = cost[i][j] + max(dyn[i - 1][j], dyn[i][j - 1]); 
  }
  for(int i = 1; i <= N; i++) { 
    cout << dyn[i][M] << ' '; 
  }
  return 0; 
}

