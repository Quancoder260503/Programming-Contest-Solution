#include<bits/stdc++.h> 

using namespace std;

#define sz(x) int(x.size())

const int mod = 998244353;
const int maxf = 1e7 + 10;

int64_t fact[maxf], ifact[maxf], fib[maxf];

int64_t Comb(int a, int b) {
  if (a == b) return 1;
  if (a < b || b < 0) return 0;
  return fact[a] % mod * ifact[b] % mod * ifact[a - b] % mod;
}

int64_t fpow(int64_t a, int64_t k) {
  if (!k) return 1;
  int64_t res = a, tmp = a;
  k--;
  while (k) {
    if (k & 1) {
      res = (int64_t)res % mod * tmp % mod;
    }
    tmp = (int64_t)tmp % mod * tmp % mod;
    k >>= 1;
  }
  return res;
}

void init(void) {
 fact[0] = ifact[0] = 1;
 for (int i = 1; i < maxf; i++) {
  fact[i] = fact[i - 1] % mod * i % mod;
 // ifact[i] = ifact[i - 1] % mod * fpow(i, mod - 2) % mod;
 }
 ifact[maxf - 1] = fpow(fact[maxf - 1], mod - 2); 
 for(int i = maxf - 2; i >= 0; i--) { 
  ifact[i] = ifact[i + 1] % mod * (i + 1) % mod; 
 } 
 return;
}

int main() {
 init(); 
 int N, K, P; 
 cin >> N >> K >> P; 
 int64_t ret = 1; 
 for(int x = 0; x < K; x++) { 
  if(N < 1LL * P * x) { ret = 0; break; } 
  ret = ret % mod * Comb(N - P * x, P) % mod;  
 } 
 int64_t den = fpow(Comb(N, P), K); 
 ret = ret % mod * fpow(den, mod - 2) % mod; 
 (ret = 1 - ret + mod) %= mod; 
 cout << ret << '\n'; 
 return 0;
}