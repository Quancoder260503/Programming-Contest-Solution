#include "bits/stdc++.h"
 
using namespace std; 
 
#define sz(x) int(x.size())
#define int64_t long long
 
const int MOD = 31607; 
 
int64_t dp[2][1 << 23]; 
 
class Bingo { 
 public :  
  void solve() { 
   int N; 
   cin >> N; 
   vector<vector<int64_t>>a(N, vector<int64_t>(N));
   int64_t MOD_INV = mod_inv(10000, MOD); 
   for(int i = 0; i < N; i++) { 
    for(int j = 0; j < N; j++) { 
     cin >> a[i][j]; 
     a[i][j] = a[i][j] % MOD * MOD_INV % MOD; 
    }
   }
   vector<int64_t>row_prob(1 << N, 1), col_prob(1 << N); 
   vector<vector<int64_t>>probs(2, vector<int64_t>(1 << N, 1)); 
   for(int i = 0; i < 2; i++) { 
    for(int mask = 0; mask < (1 << N); mask++) { 
     for(int j = 0; j < N; j++) { 
        if(mask >> j & 1) { 
          probs[i][mask] = probs[i][mask] % MOD * (i ? a[j][N - j - 1] : a[j][j]) % MOD; 
        }
      }
    } 
   }
   for(int i = 0; i < N; i++) { 
    for(int j = 0; j < N; j++) { 
     row_prob[i] = row_prob[i] % MOD * a[i][j] % MOD; 
    }
   }
   for(int mask = 0; mask < 1 << (N + 2); mask++) { 
    dp[0][mask] = 1; 
   }
   for(int pos = 2 * N + 1; pos >= 0; pos--) { 
    if(pos > N + 1) { 
     fill(col_prob.begin(), col_prob.end(), 1); 
     for(int mask = 0; mask < (1 << N); mask++) { 
      for(int j = 0; j < N; j++) { 
       if(mask >> j & 1) { 
        col_prob[mask] = col_prob[mask] % MOD * a[j][pos - N - 2] % MOD; 
       } 
      }
     }
    }
    for(int mask = 0; mask < (1 << (N + 2)); mask++) { 
      if(N + 1 < pos) { 
       int curr_mask = (1 << N) - 1, col = pos - N - 2; 
       curr_mask = curr_mask ^ mask; 
       if(curr_mask >> (N + 1) & 1) { 
         curr_mask = curr_mask ^ (1 << (N + 1)); 
         if(curr_mask >> (N - 1 - col) & 1) { 
          curr_mask = curr_mask ^ (1 << (N - 1 - col)); 
         }
       }
       if(curr_mask >> N & 1) { 
        curr_mask = curr_mask ^ (1 << N); 
        if(curr_mask >> col & 1) { 
          curr_mask = curr_mask ^ (1 << col); 
        }
       }
       dp[pos & 1][mask] = dp[(pos + 1) & 1][mask] % MOD * (1 - col_prob[curr_mask] + MOD) % MOD;  
      } 
      else if(pos < N) { 
       dp[pos & 1][mask] = (dp[(pos + 1) & 1][mask] - row_prob[pos] % MOD * dp[(pos + 1) & 1][mask | (1 << pos)] % MOD + MOD) % MOD; 
      } 
      else if(pos == N) { 
       int diag_mask = (1 << N) - 1;
       diag_mask = diag_mask ^ mask;  
       if(diag_mask < (1 << N)) { 
        dp[pos & 1][mask] = (dp[(pos + 1) & 1][mask] - probs[0][diag_mask] % MOD * dp[(pos + 1) & 1][mask | (1 << pos)] % MOD + MOD) % MOD; 
       } 
      } 
      else { 
       int diag_mask = (1 << N) - 1;
       diag_mask = diag_mask ^ mask; 
       if(diag_mask >> N & 1) { 
        diag_mask = diag_mask ^ (1 << N); 
        if((N & 1) && diag_mask >> (N / 2) & 1) { 
          diag_mask = diag_mask ^ (1 << (N / 2)); 
        } 
       }
       if(diag_mask < (1 << N)) { 
        dp[pos & 1][mask] = (dp[(pos + 1) & 1][mask] - probs[1][diag_mask] % MOD * dp[(pos + 1) & 1][mask | (1 << pos)] % MOD + MOD) % MOD; 
       } 
      }
    }
   }
   cout << (1 - dp[0][0] + MOD) % MOD << '\n'; 
   return; 
  }
 private: 
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
}; 
 
int main(void) {
  Bingo problem; 
  problem.solve();  
  return 0; 
}