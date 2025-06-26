#include <bits/stdc++.h> 
 
using namespace std; 

#define sz(x) int(x.size())

const int MOD  = 1e9 + 7;
const int maxf = 2e6 + 10;

int64_t fact[maxf], ifact[maxf], fib[maxf];

int64_t Comb(int a, int b) {
  if (a == b) return 1;
  if (a < b || b < 0) return 0;
  return fact[a] % MOD * ifact[b] % MOD * ifact[a - b] % MOD;
}

int64_t fpow(int64_t a, int64_t k) {
  if (!k) return 1;
  int64_t res = a, tmp = a;
  k--;
  while (k) {
    if (k & 1) {
      res = (int64_t)res % MOD * tmp % MOD;
    }
    tmp = (int64_t)tmp % MOD * tmp % MOD;
    k >>= 1;
  }
  return res;
}

void init(void) {
  fact[0] = ifact[0] = 1;
  for (int i = 1; i < maxf; i++) {
   fact[i] = fact[i - 1] % MOD * i % MOD;
   ifact[i] = ifact[i - 1] % MOD * fpow(i, MOD - 2) % MOD;
  }
  return;
}

 
 
int main() { 
 int N, M, K, T; 
 init(); 
 for(cin >> T; T--; ) { 
  cin >> N >> M >> K; 
  int64_t ret = 0; 
  for(int i = 1; i <= M; i++) { 
   (ret += 1LL * Comb(N - i - 1, M - i) % MOD * K % MOD * i % MOD * fpow(fpow(2, N - i), MOD - 2) % MOD) %= MOD;         
  } 
  if(N == M) ret = 1LL * K % MOD * M % MOD; 
  cout << ret << '\n'; 
 } 
 return 0;
}

/**
 // easy version 
 int main() { 
 int N, M, K, T; 
 for(cin >> T; T--; ) { 
  cin >> N >> M >> K; 
  vector<vector<int64_t>>dp(N + 1, vector<int64_t>(M + 1)); 
  for(int i = 1; i <= N; i++) {
   for(int j = 1; j <= M; j++) { 
    if(i == j) { 
     dp[i][j] = 1LL * K % MOD * i % MOD; 
    } 
    else { 
     dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]) % MOD * inv2 % MOD; 
    }
   } 
  }
  cout << dp[N][M] << '\n'; 
 } 
 return 0;
}
 * 
 */