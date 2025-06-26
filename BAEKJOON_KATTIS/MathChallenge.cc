#include "bits/stdc++.h"

using namespace std; 

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

template <typename T>
struct CRT {
  T res;

  CRT() { res = 0, prd = 1; }

  // Add condition: res % p == r
  void add(T p, T r) {
    res += mul(r - res % p + p, euclid(prd, p).first + p, p) * prd;
    prd *= p;
    if (res >= prd) res -= prd;
  }

 private:
  T prd;
  T mul(T a, T b, T p) {
    a %= p, b %= p;
    T q = (T)((long double)a * b / p);
    T r = a * b - q * p;
    while (r < 0) r += p;
    while (r >= p) r -= p;
    return r;
  }
  pair<T, T> euclid(T a, T b) {
    if (!b) return make_pair(1, 0);
    pair<T, T> r = euclid(b, a % b);
    return make_pair(r.second, r.first - a / b * r.second);
  }
};

int64_t fact[1 << 20], ifact[1 << 20];

const int MOD1 = 5e8 + 3; 

int main() {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 fact[0] = ifact[0] = 1; 
 for(int i = 1; i < (1 << 20); i++) { 
  fact[i] = fact[i - 1] % MOD1 * i % MOD1; 
  ifact[i] = mod_inv(fact[i], MOD1); 
 }
 int A, B, C, T; 
 for(cin >> T; T--; ) { 
  cin >> A >> B >> C;
  // we want to compute Comb(B, C) % 2
  int64_t comb_mod_2 = 1; 
  for(int mask = 0; mask < 30; mask++) { 
   if(C >> mask & 1) {
    if(!(B >> mask & 1)) { comb_mod_2 = 0; break; } 
   }
  }
  int64_t comb_mod_c = fact[B] % MOD1 * ifact[B - C] % MOD1 * ifact[C] % MOD1;
  CRT<int64_t>crt; 
  crt.add(2, comb_mod_2);
  crt.add(MOD1, comb_mod_c); 
  cout << mod_pow(A, crt.res, MOD) << '\n';  
 } 
 return 0;
}