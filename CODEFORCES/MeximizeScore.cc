#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define int64_t long long

const int MOD = 998244353; 

class Meximize { 
  public:   
   void solve() { 
    int N; 
    cin >> N; 
    vector<int>a(N + 1); 
    vector<int64_t>fact(N + 1), ifact(N + 1); 
    fact[0] = ifact[0] = 1; 
    for(int i = 1; i < N + 1; i++) { 
     fact[i] = fact[i - 1] % MOD * i % MOD;
    }
    ifact.back() = mod_inv(fact.back(), MOD); 
    for(int i = N - 1; i > 0; i--) { 
     ifact[i] = ifact[i + 1] % MOD * (i + 1) % MOD; 
    }
    auto Comb = [&](int n, int k) -> int64_t { 
     if(n < k) return 0; 
     return fact[n] % MOD * ifact[k] % MOD * ifact[n - k] % MOD; 
    }; 
    for(int i = 0, x; i < N; i++) { 
     cin >> x;
     a[x]++;  
    }
    vector<vector<int64_t>>dp(N + 1), ways(N + 1);
    dp[0].resize(a[0] + 1); 
    ways[0].resize(a[0] + 1); 
    int total = a[0];  
    int64_t ans = 0; 
    for(int i = 0; i <= a[0]; i++) { 
     dp[0][i] = Comb(a[0], i) % MOD * i % MOD;
     ways[0][i] = Comb(a[0], i);  
     (ans += dp[0][i] % MOD * mod_pow(2, N - total - a[1], MOD) % MOD) %= MOD;  
    }
    for(int i = 1; i < N; i++) { 
     dp[i].resize(a[i] + 1); 
     ways[i].resize(a[i] + 1); 
     vector<int64_t>prefix_dp(dp[i - 1].begin(), dp[i - 1].end()); 
     vector<int64_t>prefix_ways(ways[i - 1].begin(), ways[i - 1].end()); 
     for(int j = sz(prefix_dp) - 2; j >= 0; j--) { 
      (prefix_dp[j]   += prefix_dp[j + 1]) %= MOD; 
      (prefix_ways[j] += prefix_ways[j + 1]) %= MOD; 
     }
     vector<int64_t>choose(a[i] + 1); 
     for(int j = a[i] - 1; j >= 0; j--) { 
      (choose[j] = choose[j + 1] + Comb(a[i], j + 1)) %= MOD; 
     } 
     total += a[i]; 
     for(int j = 1; j < min(a[i] + 1, sz(prefix_dp)); j++) { 
      (dp[i][j]  += (prefix_dp[j] + prefix_ways[j] % MOD * j % MOD) % MOD * Comb(a[i], j) % MOD) %= MOD; 
      (dp[i][j]  += (dp[i - 1][j] + ways[i - 1][j] % MOD * j % MOD) % MOD * choose[j]     % MOD) %= MOD; 
      ways[i][j] =  (prefix_ways[j] % MOD * Comb(a[i], j) % MOD + ways[i - 1][j] % MOD * choose[j] % MOD) % MOD;  
      (ans += dp[i][j] % MOD * mod_pow(2, N - total - a[i + 1], MOD) % MOD) %= MOD; 
     }
    }
    cout << ans << '\n'; 
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
 int T; 
 Meximize problem; 
 for(cin >> T; T--; ) { problem.solve(); }
 return 0; 
}