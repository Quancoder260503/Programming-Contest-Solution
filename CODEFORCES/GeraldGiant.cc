#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int mod = 1e9 + 7;
const int maxf = 2e6 + 10;

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
    ifact[i] = ifact[i - 1] % mod * fpow(i, mod - 2) % mod;
  }
  return;
}
int main(void) {
  init(); 
  int H, W, N; 
  cin >> H >> W >> N; 
  vector<int64_t>dp(N);
  vector<pair<int, int>>c(N); 
  for(int i = 0; i < N; i++) { 
   cin >> c[i].first >> c[i].second; 
  }
  sort(c.begin(), c.end());  
  int64_t ret = Comb(H + W - 2, H - 1); 
  for(int i = 0; i < sz(c); i++) { 
    dp[i] = Comb(c[i].first + c[i].second - 2, c[i].first - 1) % mod; 
    for(int j = 0; j < i; j++) { 
     if(c[i].first >= c[j].first && c[i].second >= c[j].second) { 
       dp[i] += mod - dp[j] % mod * Comb(c[i].first - c[j].first + c[i].second - c[j].second, c[i].first - c[j].first) % mod;
       dp[i] %= mod;  
     }
    }
    (ret += mod - dp[i] % mod * Comb(H - c[i].first + W - c[i].second, H - c[i].first) % mod) %= mod; 
  }
  cout << ret << '\n'; 
  return 0; 
}
/*
 Let dp[i] = {number of paths that have the ith black cell as the final black cell}; 
*/