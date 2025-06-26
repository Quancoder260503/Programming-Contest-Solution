#include "bits/stdc++.h"

using namespace std; 

#define int64_t long long
#define sz(x) int(x.size())

const int MOD = 998244353; 

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

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N;
 int64_t M;  
 cin >> N >> M;
 int64_t ret = 0; 
 vector<int>vis(N + 1, false); 
 for(int i = 2; i <= N; i++) { 
  if(vis[i]) continue; 
  for(int j = 2 * i; j <= N; j += i) { 
   vis[j] = true; 
  }
 }
 for(int i = 0; i < N; i++) {  
  (ret += mod_pow(M % MOD, i + 1, MOD)) %= MOD; 
 }
 int64_t x = 1, acc = 1; 
 for(int i = 1; i <= N; i++) { 
  if(x > M) break; 
  if(!vis[i]) { x = x * i; }
  acc = (1LL * M / x) % MOD * acc % MOD; 
  (ret += MOD - acc) %= MOD; 
 }  
 cout << ret % MOD << '\n'; 
 return 0; 
}
/* 
 gcd(2, a[i) > 1 ..
 [1, 2, 3, 4, 5, 6] [2, 4, 6] [6] [6] =  
 [1, 2, 3, 4, 5, 6] [2, 4, 6] [6]    
 [1, 2, 3, 4, 5, 6] [2, 4, 6]
*/ 