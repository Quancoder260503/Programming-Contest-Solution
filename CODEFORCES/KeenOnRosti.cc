#include "bits/stdc++.h"

using namespace std;

#define int64_t long long

const int mod = 1e9 + 7;

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

int main(void) {
  int A, B, N, K;
  cin >> N >> K >> A >> B; 
  int64_t Prob = 1LL * A % mod * fpow(B, mod - 2) % mod; 
  int64_t num = fpow((1 - Prob + mod) % mod, K) % mod; 
  int64_t den = (1 + mod - fpow((1 - Prob + mod)   % mod, N)) % mod; 
  cout << num % mod * fpow(den, mod - 2) % mod << '\n'; 
  return 0; 
}