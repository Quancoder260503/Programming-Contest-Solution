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
  int n, m, T; 
  for(cin >> T; T--; ) { 
   cin >> n >> m; 
   int64_t sum = 0; 
   vector<int64_t>a(n); 
   for(auto &x : a) { 
    cin >> x; 
    sum += x; 
   }
   int64_t inv_sum = mod_inv(sum, MOD); 
   int64_t inv_4 = mod_inv(4, MOD); 
   int64_t ans = 0; 
   for(auto &x : a) { 
    int64_t curr = (1 + MOD - x % MOD * inv_sum % MOD * 2LL % MOD) % MOD; 
    ans += (1 + MOD - mod_pow(curr, m, MOD)) % MOD * inv_4 % MOD; 
   }
   (ans += 1LL * m % MOD * mod_inv(2, MOD) % MOD) %= MOD; 
   cout << ans << '\n'; 
  } 
  return 0;
}
