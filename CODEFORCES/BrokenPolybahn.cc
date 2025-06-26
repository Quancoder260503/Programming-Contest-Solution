#include "bits/stdc++.h" 

using namespace std; 

const int mod = 1e9 + 7; 

int main(void) { 
  int N; 
  cin >> N;
  vector<int64_t> pw2(N);
  pw2[0] = 1; 
  for(int i = 1; i < N; i++) {
    pw2[i] = pw2[i - 1] * 2 % mod;
  } 
  vector<int>deg(N); 
  for(int i = 0, u, v; i < N - 1; i++) { 
    cin >> u >> v; 
    --u, --v; 
    deg[u]++; 
    deg[v]++; 
  }
  int64_t ret = 0; 
  for(int i = 0; i < N; i++) {
    (ret += mod - 1 + pw2[deg[i]]) %= mod; 
  }
  (ret = ret - N + 1 + mod) %= mod; 
  cout << ret << '\n'; 
  return 0; 
}