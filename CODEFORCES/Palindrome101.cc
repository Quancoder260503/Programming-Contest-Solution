#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
const int mod = 1e9 + 7; 

int64_t dyn[203][203][4][101]; 
int pw[7]; 
int N; 
string S; 

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  cin >> N >> S;
  pw[0] = 1; 
  for(int i = 1; i < 7; i++) { 
    pw[i] = pw[i - 1] * 10; 
  }
  for(int i = N - 1; i >= 0; i--) { 
    if(i > 0) dyn[i][i - 1][0][0]++; 
    dyn[i][i][0][0]++;
    dyn[i][i][1][(S[i] - '0')]++;  
    for(int j = i + 1; j < N; j++) { 
      for(int len = 0; len < min(j - i + 1, 4); len++) { 
        for(int rem = 0; rem < 101; rem++) { 
          if(S[i] == S[j]) { 
            int c = S[i] - '0'; 
            int next_state = (c * pw[len + 1] + rem * 10 + c) % 101; 
            dyn[i][j][(len + 2) % 4][next_state] += dyn[i + 1][j - 1][len][rem]; 
            dyn[i][j][(len + 2) % 4][next_state] %= mod; 
          }
          dyn[i][j][len][rem] += (dyn[i + 1][j][len][rem] + dyn[i][j - 1][len][rem] - dyn[i + 1][j - 1][len][rem] + mod) % mod; 
          dyn[i][j][len][rem] %= mod;
        }
      }
    }
  }
  int64_t ret = 0; 
  for(int i = 0; i < 4; i++) { 
    ret += dyn[0][N - 1][i][0];
    ret %= mod; 
  }
  cout << ret - 1 << '\n'; 
  return 0; 
}