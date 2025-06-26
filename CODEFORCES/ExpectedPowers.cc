#include "bits/stdc++.h"

using namespace std; 


#define sz(x) int(x.size())
const int MOD = 1e9 + 7; 
const int LOG = 11; 


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

void solve(int64_t inv) {
  int N; 
  cin >> N; 
  vector<int64_t>a(N), p(N); 
  for(int i = 0; i < N; i++) { 
    cin >> a[i]; 
  }
  for(int i = 0; i < N; i++) { 
    cin >> p[i]; 
    p[i] = p[i] % MOD * inv % MOD; 
  } 
  vector<vector<int64_t>>expected(LOG, vector<int64_t>(LOG)); 
  vector<vector<vector<int64_t>>>dp(N + 1, vector<vector<int64_t>>(2, vector<int64_t>(2))); 
  for(int k = 0; k < LOG; k++) { 
    for(int j = k; j < LOG; j++) { 
      dp[0][0][0] = 1; 
      for(int i = 0; i < N; i++) { 
        int stateA = a[i] >> j & 1; 
        int stateB = a[i] >> k & 1; 
        if(stateA || stateB) { 
          for(int sa = 0; sa < 2; sa++) { 
            for(int sb = 0; sb < 2; sb++) { 
              (dp[i + 1][sa][sb] += dp[i][sa][sb] % MOD * (1 - p[i] + MOD) % MOD) %= MOD; 
              if(stateA && stateB) { 
                (dp[i + 1][sa ^ 1][sb ^ 1] += dp[i][sa][sb] % MOD * p[i] % MOD) %= MOD; 
              }
              else if(stateA) { 
                (dp[i + 1][sa ^ 1][sb] += dp[i][sa][sb] % MOD * p[i] % MOD) %= MOD; 
              }
              else if(stateB) { 
                (dp[i + 1][sa][sb ^ 1] += dp[i][sa][sb] % MOD * p[i] % MOD) %= MOD; 
              }
            }
          }
        } 
        else { 
          for(int sa = 0; sa < 2; sa++) { 
            for(int sb = 0; sb < 2; sb++) { 
              dp[i + 1][sa][sb] = dp[i][sa][sb]; 
            }
          }
        }
      }
      expected[j][k] = expected[k][j] = dp[N][1][1]; 
      for(int i = 0; i < N + 1; i++) { 
        for(int sa = 0; sa < 2; sa++) { 
          for(int sb = 0; sb < 2; sb++) { 
            dp[i][sa][sb] = 0; 
          }
        }
      }
    }
  }
  int64_t ret = 0; 
  for(int i = 0; i < sz(expected); i++) { 
    for(int j = i; j < sz(expected); j++) { 
      (ret += (i == j ? 1 : 2) * expected[i][j] % MOD * (1LL << (i + j)) % MOD) %= MOD; 
    } 
  }
  cout << ret << '\n'; 
  return; 

}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int T; 
  int64_t inv = mod_inv(10000, MOD); 
  for(cin >> T; T--; ) {
    solve(inv); 
  }  
  return 0; 
}
