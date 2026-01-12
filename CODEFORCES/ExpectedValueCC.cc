#include "bits/stdc++.h"

using namespace std;

#define int64_t long long
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
  int n, p; 
  cin >> n >> p; 
  int64_t acc = 0, sum = 0; 
  for(int i = 1; i <= n; i++) { 
   (sum += mod_inv(mod_pow(p, i - 1, MOD) * 2 % MOD, MOD)) %= MOD; 
   (acc += mod_inv(mod_pow(p, 2 * i - 2, MOD) * 4 % MOD, MOD)) %= MOD; 
   cout << (acc + sum * sum % MOD) % MOD << ' '; 
  }
  cout << '\n'; 
  return 0; 
}