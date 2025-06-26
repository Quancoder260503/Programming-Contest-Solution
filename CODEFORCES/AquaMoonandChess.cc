#include "bits/stdc++.h"

using namespace std;

#define int64_t long long

const int MOD = 998244353; 
const int maxf = 1e6 + 2; 

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

int64_t Comb(int a, int b) {
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

void solve() { 
 int N; 
 string S; 
 cin >> N >> S; 
 int ones = 0, zeros = 0; 
 for(int i = 0; i < N; i++) { 
  if(S[i] == '0') zeros++; 
  else if(i < N && S[i + 1] == '1') { 
   ones++;
   i++;  
  }
 }
 cout << Comb(ones + zeros, zeros) << '\n'; 
 return; 
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  init(); 
  int T; 
  for(cin >> T; T--; ) { solve(); }
  return 0;
}
