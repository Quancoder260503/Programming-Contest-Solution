#include "bits/stdc++.h"

using namespace std;
 
#define sz(x) int(x.size())
 
int N, K, MOD; 
 
#define int64_t long long
#define sz(x) int(x.size())
 
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
 
int B; 
 
int64_t h[1 << 19][19], f[1 << 19][19], g[1 << 19][19]; 
int64_t fact[1 << 19], ifact[1 << 19]; 
 
 
int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);  
 cin >> N >> K >> MOD; 
 int64_t ret = mod_pow(K, N, MOD);  
 if(N & 1) { 
  cout << ret << '\n'; 
  return 0; 
 }
 // Initialize
 B = 0; 
 while((1 << B) <= N) { B++; } 
 fact[0] = 1; 
 for(int i = 1; i <= N; i++) { 
  fact[i] = fact[i - 1] % MOD * i % MOD; 
 }
 ifact[N] = mod_inv(fact[N], MOD);  
 for(int i = N - 1; i >= 0; i--) { 
  ifact[i] = ifact[i + 1] % MOD * (i + 1) % MOD; 
 }
 for (int mask = 0; mask <= N; mask++) {
  f[mask][__builtin_popcount(mask)] = ifact[mask];
 }
 g[0][0] = 1; 
 for (int i = 0; i <= B; i++) {
  for (int mask = 0; mask <= N; mask++) {
    if (mask >> i & 1) {
     for (int k = 0; k <= B; k++) {
      (f[mask][k] += f[mask ^ (1 << i)][k]) %= MOD;
      (g[mask][k] += g[mask ^ (1 << i)][k]) %= MOD;
     }
    }
  }
 } 
 for (int mask = 0; mask <= N; mask++) {
  if((mask & N) != mask) continue; 
  int store_K = K;
  while(K) { 
   if(K & 1) { 
     for (int k = 0; k <= B; k++) {
      for (int i = 0; i <= k; i++) {
       (h[mask][k] += 1LL * f[mask][i] % MOD * g[mask][k - i] % MOD) %= MOD;
      }
     } 
     memcpy(g[mask], h[mask], sizeof(g[mask])); 
     memset(h[mask], 0, sizeof(h[mask])); 
    }
    K = K / 2; 
    for (int k = 0; k <= B; k++) {
     for (int i = 0; i <= k; i++) {
      (h[mask][k] += 1LL * f[mask][i] % MOD * f[mask][k - i] % MOD) %= MOD;
     }
    }
    memcpy(f[mask], h[mask], sizeof(f[mask])); 
    memset(h[mask], 0, sizeof(h[mask])); 
  }
   K = store_K; 
 }
 for (int i = 0; i <= B; i++) {
  for (int mask = 0; mask <= N; mask++) {
    if (mask >> i & 1) {
     (g[mask][__builtin_popcount(N)] += MOD - g[mask ^ (1 << i)][__builtin_popcount(N)]) %= MOD;
    }
   }
 }
 int64_t c = g[N][__builtin_popcount(N)];
 c = c % MOD * fact[N] % MOD; 
 (ret += MOD - c) %= MOD; 
 cout << ret << '\n'; 
 return 0; 
}