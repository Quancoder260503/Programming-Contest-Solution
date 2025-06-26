#include "bits/stdc++.h"

using namespace std; 

#define int64_t long long
#define sz(x) int(x.size())

const int MOD = 998244353; 

int64_t inv[1000007]; 
int a[1000007]; 
vector<int>g[1000007]; 

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

void init() {
 inv[0] = 1;
 for(int i = 1; i < 1000007; i++) { 
  inv[i] = mod_inv(i, MOD); 
 } 
 return; 
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  init(); 
  int N; 
  cin >> N;
  for(int i = 0; i < N; i++) { 
   cin >> a[i];
   for(int j = 0, x; j < a[i]; j++) { 
    cin >> x; 
    g[x].push_back(i); 
   } 
  } 
  int64_t ans = 0; 
  for(int i = 0; i < 1000007; i++) { 
   if(sz(g[i]) == 0) continue; 
   int64_t ret = inv[N], acc = 0; 
   ret = ret % MOD * ret % MOD * sz(g[i]) % MOD;
   for(auto &x : g[i]) { 
    (acc += inv[a[x]]) %= MOD; 
   }
   ret = ret % MOD * acc % MOD; 
   (ans += ret) %= MOD; 
  }
  cout << ans << '\n'; 
  return 0; 
}