#include <bits/stdc++.h> 

using namespace std; 

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

const int MOD = 1e9 + 7; 
const int maxf = 200; 

int main() {
 int N, K;
 int64_t M; 
 cin >> N >> M >> K; 
 vector<vector<int64_t>>Comb(maxf, vector<int64_t>(maxf)), pComb(maxf, vector<int64_t>(maxf)); 
 Comb[0][0] = 1; 
 for(int i = 1; i < maxf; i++) { 
  for(int j = 0; j <= i; j++) { 
   (Comb[i][j] = Comb[i - 1][j] + (j ? Comb[i - 1][j - 1] : 0)) %= MOD; 
  }
 }
 for(int i = 0; i < maxf; i++) { 
  for(int j = 0; j < maxf; j++) { 
   pComb[i][j] = mod_pow(Comb[i][j], M / N, MOD); 
  } 
 } 
 vector<vector<int64_t>>dp(N + 1, vector<int64_t>(K + 1)); 
 dp[0][0] = 1;
 for(int i = 0; i < N; i++) { 
  for(int j = 0; j <= K; j++) { 
   for(int place = 0; place <= min(j, N); place++) { 
    (dp[i + 1][j] += dp[i][j - place] % MOD * pComb[N][place] % MOD * (i < M % N ? Comb[N][place] : 1) % MOD) %= MOD; 
   } 
  } 
 }
 cout << dp[N][K] << '\n'; 
 return 0;
}
