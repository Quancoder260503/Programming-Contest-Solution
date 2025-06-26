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
 vector<int64_t>suffix(N + 3), a(N + 3); 
 for(int i = 1; i < N; i++) { 
  cin >> a[i]; 
 }
 int64_t ret = 0; 
 for(int i = N - 1; i > 0; i--) { 
  int64_t expectedRange = (suffix[i + 1] - suffix[i + a[i] + 1] + MOD) % MOD; 
  ret = (a[i] + 1 + expectedRange) % MOD * mod_inv(a[i], MOD) % MOD; 
  suffix[i] = (suffix[i + 1] + ret) % MOD; 
 }
 cout << ret << '\n'; 
 return 0; 
}