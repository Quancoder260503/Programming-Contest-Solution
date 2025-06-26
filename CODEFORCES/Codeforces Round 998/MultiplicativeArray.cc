#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define int64_t long long

const int MOD = 998244353; 

class Multiplicative { 
  public:   
   void solve() { 
    int N, M; 
    cin >> N >> M; 
    vector<vector<int64_t>>dp(N + 1, vector<int64_t>(19));
    for(int i = 2; i <= N; i++) { 
      dp[i][1] = 1;   
    } 
    for(int num_elem = 2; num_elem < 19; num_elem++) { 
     for(int curr = 2; curr <= N; curr++) { 
      for(int j = 2; j * curr <= N; j++) { 
       (dp[curr * j][num_elem] += dp[curr][num_elem - 1]) %= MOD; 
      }
     }
    }
    cout << M << " "; 
    for(int i = 2; i <= N; i++) { 
     int64_t ans = 0; 
     for(int j = 1; j < 19; j++) { 
      (ans += dp[i][j] % MOD * Comb(M + 1, j + 1) % MOD) %= MOD; 
     }
     cout << ans << " "; 
    }
    cout << '\n'; 
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

   int64_t Comb(int64_t a, int64_t b) { 
    int64_t ans = 1; 
    for(int x = a - b + 1; x <= a; x++) { 
     ans = ans % MOD * x % MOD; 
    }
    for(int x = 2; x <= b; x++) { 
     ans = ans % MOD * mod_inv(x, MOD) % MOD;    
    }
    return ans; 
   }
};


int main(void) {  
 int T; 
 Multiplicative problem; 
 for(cin >> T; T--; ) { problem.solve(); }
 return 0; 
}