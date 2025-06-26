#include "bits/stdc++.h"

using namespace std;

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
 int N; 
 cin >> N;
 vector<int64_t>f(N + 1); 
 f[1] = 1, f[2] = 1; 
 for(int i = 3; i <= N; i++) { 
  f[i] = (f[i - 1] + f[i - 2]) % MOD; 
 }
 int64_t den = mod_pow(2, N, MOD); 
 cout << (f[N] * mod_inv(den, MOD)) % MOD << '\n'; 
 return 0; 
}