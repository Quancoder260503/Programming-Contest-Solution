#include "bits/stdc++.h"

using namespace std; 

const int MOD = 1e9 + 7; 

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N, M; 
  cin >> N >> M; 
  vector<int64_t>f(max(N, M) + 1); 
  f[0] = f[1] = 1;
  for(int i = 2; i < max(N, M) + 1; i++) { 
   f[i] = (f[i - 1] + f[i - 2]) % MOD; 
  }
  cout << 2LL * (f[M] + f[N] + MOD - 1) % MOD << '\n'; 
  return 0; 
}

