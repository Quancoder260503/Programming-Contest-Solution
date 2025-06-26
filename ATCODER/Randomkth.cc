#include "bits/stdc++.h"

using namespace std;

const int MOD = 998244353;

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
  int N, K;
  cin >> N >> K; 
  vector<int>L(N), R(N); 
  int maxBound = 0; 
  for(int i = 0; i < N; i++) { 
    cin >> L[i] >> R[i];
    maxBound = max(maxBound, R[i]);  
  }
  int64_t ret = 0; 
  for(int range = 0; range < maxBound; range++) { 
    vector<vector<vector<int64_t>>>dp(N + 1, vector<vector<int64_t>>(N + 1, vector<int64_t>(N + 1))); 
    dp[0][0][0] = 1; 
    for(int i = 0; i < N; i++) { 
      int64_t den = mod_inv(R[i] - L[i], MOD); 
      int64_t probIn  = max(min(range + 1, R[i]) - max(L[i], range), 0) * den % MOD;
      int64_t probOut = max(0, R[i] - max(L[i], range + 1)) * den % MOD; 
      for(int j = 0; j <= N; j++) { 
        for(int k = 0; k <= N; k++) { 
         // cout << dp[i][j][k] << " : (" << i << "," << j << "," << k << ") " << probIn << " " << probOut << " " << '\n'; 
          if(k < N) (dp[i + 1][j][k + 1] += probIn  % MOD * dp[i][j][k] % MOD) %= MOD; 
          if(j < N) (dp[i + 1][j + 1][k] += probOut % MOD * dp[i][j][k] % MOD) %= MOD;
          (dp[i + 1][j][k] += (1 + MOD - probIn - probOut) % MOD * dp[i][j][k] % MOD) %= MOD; 
        }
      }
    }
    for(int j = 0; j < K; j++) { 
      for(int var = K - j; var <= N; var++) {
        int64_t Prob = (K - j) % MOD * mod_inv(var + 1, MOD) % MOD;
        (ret += dp[N][j][var] % MOD * (range + 1 + MOD - Prob) % MOD) %= MOD; 
      }
    }
  }
  cout << ret << '\n'; 
  return 0;
}

  /*
    Fixed the range [A, A + 1]
    dp[i][j][k] = {Probability that for the first i-th intergers, 
                   j-th of which larger than A + 1 and 
                   k-th of the first number is in the fixed range}

    dp[i][j][k] = Prob(In)  * dp[i - 1][j][k - 1]
    dp[i][j + 1][k] = Prob(Out) * dp[i - 1][j][k]
  */ 