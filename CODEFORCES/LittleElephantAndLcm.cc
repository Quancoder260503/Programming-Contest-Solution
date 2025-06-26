#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int MOD = 1e9 + 7; 

vector<int>d[100005]; 

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

void init() { 
 for(int i = 1; i < 100005; i++) { 
  for(int j = i; j < 100005; j += i) { 
   d[j].push_back(i); 
  }
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
  vector<int>a(N); 
  for(int i = 0; i < N; i++) { 
   cin >> a[i]; 
  }
  sort(a.begin(), a.end()); 
  int64_t ans = 0; 
  for(int m = 1; m <= a.back(); m++) { 
   int64_t cc = 1;
   vector<int>b; 
   for(auto &x : d[m]) { 
    b.push_back(lower_bound(a.begin(), a.end(), x) - a.begin() + 1); 
   } 
   for(int i = 0; i + 1 < sz(b); i++) { 
     cc = cc % MOD * mod_pow(i + 1, b[i + 1] - b[i], MOD) % MOD; 
   }
   (ans += cc % MOD * mod_pow(sz(b), N + 1 - b.back(), MOD) % MOD) %= MOD; 
   (ans += MOD - cc % MOD * mod_pow(sz(b) - 1, N + 1 - b.back(), MOD) % MOD) %= MOD;  
  }
  cout << ans << '\n'; 
  return 0;
} 