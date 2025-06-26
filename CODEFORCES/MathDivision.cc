#include "bits/stdc++.h"

using namespace std; 

const int MOD = 1e9 + 7; 
const int inv = 5e8 + 4; 

#define sz(x) int(x.size())

int main(void) { 
 int N, T;
 string S;  
 for(cin >> T; T--; ) { 
  cin >> N >> S;  
  int64_t ans = 0; 
  for(int i = N - 1; i > 0; i--) { 
   ans = ((S[i] - '0') + ans) % MOD * inv % MOD; 
  }
  cout << (N - 1 + ans + MOD) % MOD << '\n'; 
 }
 return 0; 
}
/* 

*/ 