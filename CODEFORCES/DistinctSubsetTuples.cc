#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int mod = 1e9 + 7;
const int maxf = 2e6 + 10;

int64_t fact[maxf], ifact[maxf], fib[maxf];

int64_t Comb(int a, int b) {
  if (a == b) return 1;
  if (a < b || b < 0) return 0;
  return fact[a] % mod * ifact[b] % mod * ifact[a - b] % mod;
}

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

void init(void) {
  fact[0] = ifact[0] = 1;
  for (int i = 1; i < maxf; i++) {
    fact[i] = fact[i - 1] % mod * i % mod;
    ifact[i] = ifact[i - 1] % mod * fpow(i, mod - 2) % mod;
  }
  return;
}

int main() {
 init(); 
 int N, M; 
 cin >> N >> M; 
 int64_t ret = 0; 
 for(int i = 1; i <= N; i++) { 
  ret += Comb(N, i - 1) % mod * fpow(M - 1, N - i) % mod * fpow(M, i) % mod;  
  ret %= mod; 
 } 
 (ret += fpow(M, N))  %= mod; 
 cout << ret << '\n'; 
 return 0;
}

/**
 * P(x) = (x ^ 0) * Comb(n - s, 0) + (x ^ 1) * Comb(n - s + 1, 1) + (x ^ 2) * Comb(n - s + 2, 2) + ... + (x ^ k) * Comb(n - s + k, k) = Comb(n + k - 1, n)
 * sum Comb(n - s + k, k) = Comb(n - s + s, s - 1) = Comb(n, s - 1 )
 / 