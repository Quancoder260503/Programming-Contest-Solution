#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int MOD = 1e9 + 7;
const int maxf = 2e6 + 10;

int64_t fact[maxf], ifact[maxf];

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


int64_t Comb(int a, int b) {
  if(a == b) return 1;
  if (a < b || b < 0) return 0;
  return fact[a] % MOD * ifact[b] % MOD * ifact[a - b] % MOD;
}

void init(void) {
  fact[0] = ifact[0] = 1;
  for (int i = 1; i < maxf; i++) {
    fact[i] = fact[i - 1] % MOD * i % MOD;
    ifact[i] = mod_inv(fact[i], MOD); 
  }
  return;
}


int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  init(); 
  int N, M, G; 
  cin >> N >> M >> G; 
  if(!N) { 
    int ret = (M == 1 ? 0 : 1); 
    cout << (G ? 1 - ret : ret) << '\n'; 
  } else if(M == 0) {
    int ret = N & 1;
    cout << (G ? 1 - ret : ret) << '\n'; 
  } else { 
   int64_t ret = 0; 
   for(int x = 0; x <= N; x += 2) { 
    (ret += Comb(N + M - 1 - x, M - 1)) %= MOD; 
   }
   if(M == 1) { 
     (ret += MOD + (N & 1 ? 1 : -1)) %= MOD;
   }
   cout << (!G ? ret : (MOD + Comb(M + N, N) - ret) % MOD) << '\n';
  } 
  return 0; 
}
