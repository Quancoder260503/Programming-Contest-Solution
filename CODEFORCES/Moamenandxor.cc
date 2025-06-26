#include "bits/stdc++.h"

using namespace std; 

const int MOD = 1e9 + 7;

int64_t pw[200005]; 

int64_t mod_pow(int64_t a, int64_t b, int64_t p) {
  int64_t res = 1;
  while (b > 0) {
    if (b & 1) res = (res * a) % p;
    a = (a * a) % p;
    b >>= 1;
  }
  return res;
}

void solve(void) { 
 int N, K; 
 cin >> N >> K; 
 if(N % 2 == 0) { 
  int64_t base = (pw[N - 1] - 1), ret = 0, equals = 1; 
  for(int i = 0; i < K; i++) {
   int64_t ways = equals % MOD * mod_pow(pw[N], K - i - 1, MOD) % MOD; 
   (ret += ways) %= MOD; 
   equals = equals % MOD * base % MOD; 
  }
  (ret += equals) %= MOD; 
  cout << ret << '\n'; 
 } else { 
  int64_t base = (pw[N - 1] + 1), ret = 1;
  for(int i = 0; i < K; i++) { 
   ret = ret % MOD * base % MOD; 
  }
  cout << ret << '\n'; 
 } 
 return; 
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  pw[0] = 1; 
  for(int i = 1; i < 200005; i++) {
   pw[i] = (pw[i - 1] * 2) % MOD; 
  }
  int T; 
  for(cin >> T; T--; ) { 
   solve(); 
  }
  return 0; 
}

/**
  Let X = sum_AND, Y = sum_XOR, assume X >= Y, then let kth be the first position 
 */