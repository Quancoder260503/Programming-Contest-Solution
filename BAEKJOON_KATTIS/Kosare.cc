#include "bits/stdc++.h"
 
using namespace std; 
 
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
 int N, M; 
 cin >> N >> M; 
 vector<int64_t>cnt(1 << M); 
 for(int i = 0, num; i < N; i++) { 
  int mask = 0; 
  cin >> num; 
  for(int j = 0, x; j < num; j++) { 
   cin >> x; 
   mask |= 1 << (x - 1); 
  }
  cnt[mask]++; 
 } 
 for(int i = 0; i < M; i++) { 
  for(int mask = 0; mask < (1 << M); mask++) {
   if(mask & (1 << i)) { 
    cnt[mask] += cnt[mask ^ (1 << i)]; 
    cnt[mask] %= (MOD - 1); 
   }
  }
 }
 for(int mask = 0; mask < (1 << M); mask++) { 
  cnt[mask] = mod_pow(2, cnt[mask], MOD); 
 }
 for(int i = 0; i < M; i++) { 
  for(int mask = 0; mask < (1 << M); mask++) { 
   if(mask & (1 << i)) { 
    (cnt[mask] += MOD - cnt[mask ^ (1 << i)]) %= MOD; 
   }
  }
 }
 cout << cnt[(1 << M) - 1] << '\n'; 
 return 0; 
}