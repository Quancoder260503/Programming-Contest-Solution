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
  vector<int>nxt(N); 
  for(int i = 0; i < N; i++) { 
   cin >> nxt[i]; 
   --nxt[i]; 
  }
  vector<int>cyc_len(N + 1), vis(N, false); 
  for(int i = 0; i < N; i++) { 
   int cnt = 0, ptr = i; 
   while(!vis[ptr]) { 
    vis[ptr] = true; 
    ptr = nxt[ptr];
    cnt++; 
   }
   cyc_len[cnt]++; 
  }
  vector<int64_t>fact(N + 1, 1), ifact(N + 1, 1), pw2(N + 1, 1); 
  fact[0] = ifact[0] = pw2[0] = 1; 
  for(int i = 1; i < sz(fact); i++) { 
   fact[i] = fact[i - 1] % MOD * i % MOD; 
   ifact[i] = mod_inv(fact[i], MOD);
   pw2[i] = pw2[i - 1] % MOD * 2 % MOD; 
  }
  auto Comb = [&](int n, int k) -> int64_t { 
   if(n < k || k < 0) return 0; 
   return fact[n] % MOD * ifact[n - k] % MOD * ifact[k] % MOD; 
  }; 
  int64_t ret = 1; 
  for(int c = 1; c <= N; c++) { 
   if(cyc_len[c] == 0) continue;
   if(c % 2 == 0) { 
     if(cyc_len[c] & 1) ret = 0; 
     else { 
      int64_t coef = fact[cyc_len[c]] % MOD * ifact[cyc_len[c] / 2] % MOD * mod_inv(pw2[cyc_len[c] / 2], MOD) % MOD; 
      ret = ret % MOD * coef % MOD * mod_pow(c, cyc_len[c] / 2, MOD) % MOD; 
     } 
   } else { 
    int64_t acc = 1; 
    for(int j = 1; 2 * j <= cyc_len[c]; j++) { 
     int64_t coef = fact[2 * j] % MOD * ifact[j] % MOD * mod_inv(pw2[j], MOD) % MOD; 
     acc += Comb(cyc_len[c], 2 * j) % MOD * coef % MOD * mod_pow(c, j, MOD) % MOD;  
     acc %= MOD; 
    }
    ret = ret % MOD * acc % MOD; 
   }
  }
  cout << ret << '\n'; 
  return 0;
}
