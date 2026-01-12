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
 int N, T, K; 
 for(cin >> T; T--; ) { 
  cin >> N >> K; 
  int64_t sum = 0; 
  for(int i = 0, x; i < N; i++) { 
   cin >> x; 
   sum += x; 
  }
  sum = sum % MOD * mod_inv(N, MOD) % MOD; 
  cout << sum << '\n'; 
 }
 return 0; 
}