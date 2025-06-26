#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int MOD = 998244353; 

int64_t mod_pow(int64_t a, int64_t b, int64_t p) {
  int64_t res = 1;
  while (b > 0) {
    if (b & 1) res = (res * a) % p;
    a = (a * a) % p;
    b >>= 1;
  }
  return res;
}

int64_t mod_inv(int64_t a, int64_t p) { return mod_pow(a % p, p - 2, p); }

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N, M; 
 cin >> N >> M;
 int64_t ret = 0; 
 for(int bits = M - 1; bits >= 0; bits--) { 
  (ret += mod_pow(2, 1LL * M * N + bits - 2, MOD)) %= MOD;
 }
 ret = ret % MOD * N % MOD * (N - 1) % MOD; 
 cout << ret << '\n';
 /* 
 int64_t acc = 0; 
 for(int i = 0; i < 4; i++) { 
  for(int j = 0; j < 4; j++) { 
    (acc += (i ^ j)); 
  }
 }
 cout << acc << '\n';
 */ 
 return 0;
}