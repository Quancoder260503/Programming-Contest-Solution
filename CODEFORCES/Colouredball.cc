#include "bits/stdc++.h"

using namespace std; 

class ColouredBall { 
  const int MOD = 998244353; 
  public: 
   void solve() { 
    int N; 
    cin >> N; 
    vector<int>a(N); 
    for(int i = 0; i < N; i++) { 
     cin >> a[i]; 
    }
    int s = accumulate(a.begin(), a.end(), 0);
    vector<int64_t>dp(s + 1); 
    dp[0] = 1; 
    for(int i = 0; i < N; i++) { 
     for(int j = s; j >= a[i]; j--) { 
       (dp[j] += dp[j - a[i]]) %= MOD; 
     }
    }
    int64_t ans = 0; 
    for(int w = 1; w <= s; w++) { 
     (ans += 1LL * (w + 1) / 2 % MOD * dp[w] % MOD) %= MOD;  
    }
    for(int i = 0; i < N; i++) { 
     for(int j = 0; j < a[i]; j++) { 
      (ans += 1LL * (a[i] - (j + a[i] + 1) / 2) % MOD * dp[j] % MOD) %= MOD; 
     }
    }
    cout << ans << '\n'; 
    return; 
   }
}; 
int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 ColouredBall color; 
 color.solve(); 
 return 0; 
}