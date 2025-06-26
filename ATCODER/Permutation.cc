#include "bits/stdc++.h"

using namespace std;

const int mod = 1e9 + 7; 

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N; 
  cin >> N; 
  vector<vector<int64_t>>dyn(N + 2, vector<int64_t>(N + 2));
  char c;  
  dyn[1][1] = 1; 
  for(int i = 2; i <= N; i++) { 
    cin >> c; 
    for(int j = 1; j <= i; j++) { 
      if(c == '<') { 
        dyn[i][j] = dyn[i - 1][j - 1]; 
        dyn[i][j] %= mod; 
      }
      else { 
        dyn[i][j] = (dyn[i - 1][i - 1] + mod - dyn[i - 1][j - 1]) % mod;
      }
    }   
    for(int j = 1; j <= i; j++) { 
      dyn[i][j] = (dyn[i][j] + dyn[i][j - 1]) % mod; 
    }
  }
  cout << dyn[N][N] << '\n'; 
  return 0; 
}