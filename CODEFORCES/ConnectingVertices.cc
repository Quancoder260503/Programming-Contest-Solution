#include "bits/stdc++.h"

using namespace std; 

const int maxf = 750; 
const int mod = 1e9 + 7; 

int64_t dyn[maxf][maxf][2], g[maxf][maxf]; 
int N;

int64_t fpow(int64_t a, int64_t k) {
  if (!k) return 1;
  int64_t res = a, tmp = a;
  k--;
  while (k) {
    if (k & 1) {
      res = (int64_t)res % mod * tmp % mod;
    }
    tmp = (int64_t)tmp % mod * tmp % mod;
    k >>= 1;
  }
  return res;
}

int64_t memo(int i, int j, int type) {  
  if((i + 1) % N == j) return 1; 
  if(dyn[i][j][type] != -1) return dyn[i][j][type]; 
  int64_t &ret = dyn[i][j][type]; 
  ret = 0; 
  for(int nxt = (i + 1) % N; nxt != j; nxt = (nxt + 1) % N) { 
    if(g[i][nxt] && !type) { 
      (ret += memo(i, nxt, 0) % mod * memo(nxt, j, 0) % mod) %= mod; 
    }
    if(g[nxt][j]) {
      (ret += memo(i, nxt, 1) % mod * memo(nxt, j, 0) % mod) %= mod; 
    }
  }
  return ret;
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  cin >> N;
  memset(dyn, -1, sizeof(dyn)); 
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
      cin >> g[i][j]; 
    }
  }
  int64_t ret = 0; 
  for(int i = 0; i < N; i++) {
    for(int j = i + 1; j < N; j++) if(g[i][j]) {
      (ret += memo(i, j, 0) % mod * memo(j, i, 0) % mod) %= mod; 
    }
  }
  ret = ret % mod * fpow(N - 1, mod - 2) % mod; 
  cout << ret << '\n'; 
  return 0; 
}
