#include "bits/stdc++.h"

using namespace std;

#define int64_t long long
#define sz(x) int(x.size())

const int MOD = 1e9 + 7;

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
 int g = false, parity = true;
 int64_t a = 2;  
 for(int i = 0; i < N; i++) { 
  int64_t x; 
  cin >> x; 
  if(x % 2 == 0) parity = false; 
  if(x > 1) g = true; 
  a = mod_pow(a, x, MOD); 
 }
 if(!g) { 
  cout << 0 << '/' << 1 << '\n'; 
  return 0; 
 }
 parity = parity ^ 1; 
 a = a % MOD * mod_inv(2, MOD) % MOD; 
 int64_t num = (a + (parity ? 1 : -1) + MOD) % MOD; 
 num = num % MOD * mod_inv(3, MOD) % MOD; 
 cout << num << "/" << a << '\n'; 
 return 0; 
}
/**
 * dp[0][j] = dp[1][j - 1] / 2 
 * dp[1][j] = (dp[0][j - 1] + dp[2][j - 1]) / 2
 * dp[2][j] = dp[1][j - 1] / 2
 */