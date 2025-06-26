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
  int N, K, T; 
  for(cin >> T; T--; ) { 
   cin >> N >> K; 
   vector<int64_t>pw2(N + 1), rcnt(1 << K), fact(N + 1), dp(1 << K); 
   pw2[0] = 1; 
   fact[0] = 1; 
   for(int i = 1; i <= N; i++) { 
    pw2[i] = pw2[i - 1] * 2 % MOD; 
    fact[i] = fact[i - 1] % MOD * i % MOD; 
   }
   int sum = (1 << K) - 1; 
   for(int i = 0, x; i < N; i++) { 
    cin >> x; 
    dp[x]++;  
    rcnt[x]++; 
    sum = sum & x; 
   }
   if(sum > 0) { 
    cout << fact[N] % MOD * N % MOD << '\n';
    continue; 
   }
   for(int i = 0; i < K; i++) { 
    for(int mask = 0; mask < (1 << K); mask++) { 
     if(mask & (1 << i)) { 
      (dp[mask] += dp[mask ^ (1 << i)]) %= MOD; 
     } else { 
      (rcnt[mask] += rcnt[mask ^ (1 << i)]) %= MOD; 
     }
    }
   }
   for(int mask = 0; mask < (1 << K); mask++) { 
    rcnt[mask] = fact[N] % MOD * rcnt[mask] % MOD * mod_inv(N - rcnt[mask], MOD) % MOD * mod_inv(N - rcnt[mask] + 1, MOD) % MOD; 
   }
   for(int i = 0; i < K; i++) { 
    for(int mask = 0; mask < (1 << K); mask++) { 
     if(~mask & (1 << i)) { 
      (rcnt[mask] += MOD - rcnt[mask ^ (1 << i)]) %= MOD;
     }  
    }
   } 
   int64_t ans = 0; 
   for(int mask = 1; mask < (1 << K); mask++) { 
   // cout << rcnt[mask] << " " << dp[mask] << '\n'; 
    (ans += rcnt[mask] % MOD * dp[((1 << K) - 1) ^ mask] % MOD) %= MOD; 
   }
   cout << ans << '\n'; 
  }
  return 0;   
}