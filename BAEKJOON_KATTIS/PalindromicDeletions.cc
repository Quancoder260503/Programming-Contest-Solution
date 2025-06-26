#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int maxf = 402; 
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


int64_t fact[maxf], ifact[maxf];
int64_t dp[maxf][maxf][maxf]; 

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N, T; 
 fact[0] = 1; 
 for(int i = 1; i < maxf; i++) { 
  fact[i] = fact[i - 1] % MOD * i % MOD; 
  ifact[i] = mod_inv(fact[i], MOD); 
 }
 cin >> T; 
 string S; 
 for(int _case = 0; _case < T; _case++) {
  memset(dp, -1, sizeof(dp)); 
  cin >> N >> S;
  function<int64_t(int, int, int)> func = [&](int l, int r, int len) -> int64_t { 
   if(len == 0) return 1;
   if(l == r) return len == 1;
   if(l >  r) return 0;
   int64_t &ret = dp[l][r][len]; 
   if(ret != -1) return ret;
   ret = 0; 
   if(S[l] == S[r] && len >= 2) { 
    (ret += func(l + 1, r - 1, len - 2)) %= MOD; 
   } 
   (ret += func(l + 1, r, len) + func(l, r - 1, len) - func(l + 1, r - 1, len) + MOD) %= MOD;
   return ret; 
  };
  int64_t ret = 0; 
  for(int len = 1; len <= sz(S); len++) { 
   (ret += func(0, sz(S) - 1, len) % MOD * fact[sz(S) - len] % MOD * fact[len] % MOD) %= MOD; 
  }
  ret = ret % MOD * ifact[N] % MOD; 
  bool isPalin = true; 
  for(int i = 0; i < sz(S) / 2; i++) { 
   isPalin &= (S[i] == S[sz(S) - 1 - i]); 
  } 
  ret += !isPalin;   
  printf("Case #%d: %lld\n", _case + 1, ret); 
 } 
 return 0; 
}