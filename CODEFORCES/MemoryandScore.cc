#include "bits/stdc++.h"
 
using namespace std;
 
#define int64_t long long
 
const int maxf = 200200; 
const int mod = 1e9 + 7;
const int max_R = 101;
 
int A, B, N, K;
int64_t dyn[max_R][maxf], prefix[maxf];

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> A >> B >> K >> N;
  dyn[0][0] = 1; 
  for(int i = 1; i <= N; i++) { 
    for(int j = 0; j < maxf; j++) { 
      prefix[j] = ((j ? prefix[j - 1] : 0) + dyn[i - 1][j]) % mod;  
    }
    for(int j = 0; j < maxf; j++) { 
      dyn[i][j] = (prefix[j] - (j > 2 * K ? prefix[j - 2 * K - 1] : 0) + mod) % mod; 
    }
  }
  for(int i = 0; i < maxf; i++) { 
    prefix[i] = (dyn[N][i] + (i ? prefix[i - 1] : 0)) % mod; 
  }
  int64_t ret = 0; 
  for(int i = 0; i <= 2 * K * N; i++) { 
    ret += dyn[N][i] % mod * (i + A - B - 1 < 0 ? 0 : prefix[i + A - B - 1]) % mod; 
    ret %= mod; 
  }
  cout << ret << '\n'; 
  return 0;
}

/* 
int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> A >> B >> K >> N;
  for (int i = offset + 1; i < maxf; i++) {
    dyn[i][0] = 1;
  }
  for (int round = 1; round <= N; round++) {
    prefixS[0] = 0; 
    prefix[0]  = dyn[0][round - 1]; 
    for(int diff = 1; diff < maxf; diff++) { 
      prefixS[diff] = (prefixS[diff - 1] + dyn[diff][round - 1] % mod * diff % mod) % mod; 
      prefix[diff]  = (prefix[diff - 1]  + dyn[diff][round - 1]) % mod; 
    }
    for (int diff = 2 * K + 1; diff + 2 * K < maxf; diff++) {
      int64_t sumLarge = (prefix[diff + 2 * K] - prefix[diff - 1] + mod) % mod * diff % mod; 
      int64_t sumSmall = (prefix[diff - 1]  - prefix[diff - 2 * K - 1] + mod) % mod * diff % mod; 
      int64_t sumPL    = (prefixS[diff + 2 * K] - prefixS[diff - 1] + mod) % mod; 
      int64_t sumPS    = (prefixS[diff - 1] - prefixS[diff - 2 * K - 1] + mod) % mod; 
      int64_t sum      = (prefix[diff + 2 * K] - prefix[diff - 2 * K - 1]) % mod * (2 * K + 1) % mod;
      dyn[diff][round] = (dyn[diff][round] + sumLarge + sum + sumPS) % mod; 
      dyn[diff][round] = (dyn[diff][round] - sumSmall + mod) % mod; 
      dyn[diff][round] = (dyn[diff][round] - sumPL    + mod) % mod;
    }
  } 
  cout << dyn[A - B + offset][N] << '\n'; 
  return 0;
}
*/ 