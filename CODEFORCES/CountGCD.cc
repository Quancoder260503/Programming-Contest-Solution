/**
 * @file CountGCD.cc
 * @author Minh Quan Le
 * @brief 
 * @version 0.1
 * @date 2024-10-24
 * 
 */

#include "bits/stdc++.h"

using namespace std; 

const int MOD = 998244353; 

#define sz(x) int(x.size())

int main() { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  int N, T, M; 
  for(cin >> T; T--; ) { 
    cin >> N >> M; 
    vector<int>a(N); 
    for(int i = 0; i < N; i++) { 
     cin >> a[i]; 
    }
    vector<int64_t>dp(N + 1); 
    dp[0] = 1; 
    for(int i = 1; i < N; i++) { 
      if(a[i - 1] == a[i]) { 
        (dp[i] += dp[i - 1] % MOD * (M / a[i]) % MOD) %= MOD; 
      }
      else if(a[i - 1] % a[i] == 0) {
       int num = a[i - 1] / a[i]; 
       vector<int>prime; 
       for(int j = 2; j * j <= num; j++) { 
        if(num % j == 0) { 
         prime.push_back(j); 
         while(num % j == 0) { 
          num = num / j; 
         }
        }
       }
       if(num > 1) { 
        prime.push_back(num); 
       } 
       int64_t ways = 0; 
       for(int mask = 1; mask < (1 << sz(prime)); mask++) { 
        int64_t cc = 1; 
        int sign = __builtin_popcount(mask) & 1 ? 1 : -1; 
        for(int j = 0; j < sz(prime); j++) { 
          if(mask & (1 << j)) { 
           cc = cc * prime[j]; 
          }
        }
        (ways += (M / a[i] / cc) * sign); 
       }
       (dp[i] += dp[i - 1] % MOD *(M / a[i] - ways) % MOD) %= MOD; 
      }
      else { 
        break; 
      }
    }
    cout << dp[N - 1] << '\n'; 
  }
  return 0; 
}

/**
 * M / a[i] - M / a[i - 1]
 * gcd(a[i - 1] / a[i], k) = 1 for k <= M / a[i]
 * 
 */