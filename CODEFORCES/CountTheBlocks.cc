#include <bits/stdc++.h>
 
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
 
int main() { 
 int N; 
 cin >> N;
 for(int i = 1; i <= N; i++) { 
  int64_t ret = 0; 
  (ret += 10LL * 9 * 9 * max(0, N - i - 1) * mod_pow(10, N - i - 2, MOD) % MOD) %= MOD;
  if(i < N) { 
   (ret += 10LL * 9 * 2 *  mod_pow(10, N - i - 1, MOD) % MOD) %= MOD; 
  } else {
   (ret += 10) %= MOD; 
  }
  cout << ret << " "; 
 } 
 return 0;
}