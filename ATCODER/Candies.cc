#include "bits/stdc++.h"

using namespace std;

const int mod = 1e9 + 7;

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N, M; 
  cin >> N >> M; 
  int offset = 1; 
  vector<int64_t>dyn(M + offset + 1);
  vector<int>a(N); 
  for(int i = 0; i < N; i++) { 
    cin >> a[i]; 
  }
  dyn[offset] = 1; 
  for(int i = 0; i < N; i++) {
    vector<int64_t>ndyn(M + offset + 1);  
    for(int j = 1; j <= M; j++) { 
      dyn[offset + j] += dyn[offset + j - 1]; 
    }
    for(int j = 0; j <= M; j++) { 
       ndyn[offset + j] += dyn[offset + j] - dyn[max(0, j - a[i])]; 
       ndyn[offset + j] %= mod; 
    }
    dyn.swap(ndyn); 
  }
  cout << dyn[offset + M] << '\n'; 
  return 0; 
}
/*
  dyn[i][j] = dyn[i - 1][j - j'] where 0 <= j' <= a[i]; 
*/