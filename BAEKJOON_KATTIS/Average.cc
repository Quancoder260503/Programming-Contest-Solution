#include "bits/stdc++.h"

using namespace std; 

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

const int MOD = 1e9 + 7; 
const int maxf = 1e5 + 10;

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

int main(void) {
 init(); 
 int N, M; 
 while(cin >> N >> M && N) {
   function<int64_t(int, int)> F = [&](int score, int nJudges) {
     int64_t sum = 0;  
     for(int nLarge = 0, sign = 1; nLarge <= nJudges; nLarge++) {
       (sum += Comb(nJudges, nLarge) % MOD * Comb(score - nLarge * (M + 1) + nJudges - 1, nJudges - 1) % MOD * sign + MOD) %= MOD;
       sign = -sign; 
     }
     return sum; 
    };
    int64_t ret = 0; 
    for(int score = 0; score <= M; score++) { 
     (ret += F(score * (N - 1), N - 1)) %= MOD;
    }
    ret = ret % MOD * N % MOD;
    cout << ret << '\n'; 
 }   
 return 0; 
}
