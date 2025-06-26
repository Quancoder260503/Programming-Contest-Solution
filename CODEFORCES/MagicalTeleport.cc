#include "bits/stdc++.h"
 
using namespace std; 
 
#define sz(x) int(x.size())
 
const int MOD = 1e9 + 7;
 
int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  string s; 
  int start, end; 
  cin >> s >> start >> end; 
  int N = sz(s); 
  vector<vector<int64_t>>dp(N + 1, vector<int64_t>(N + 2, 0)); 
  dp[1][1] = (end == 1 || s[0] != 'L');  
  for(int i = 2; i <= N; i++) { 
   for(int j = 1; j <= i; j++) { 
     if(start == i || end == i) { 
       if(start != i || s[i - 1] != 'L')(dp[i][j] += dp[i - 1][j - 1]) %= MOD; 
       if(i == start && s[i - 1] != 'R') { 
        (dp[i][j] += dp[i - 1][j]) %= MOD;
       }
       else if (i == end) { 
        (dp[i][j] += dp[i - 1][j]) %= MOD; 
       }
     }
     else { 
       if(s[i - 1] == 'B') { 
        (dp[i][j] += dp[i - 1][j - 1] % MOD * (j - (i > start) - (i > end)) % MOD) %= MOD; 
        (dp[i][j] += dp[i - 1][j] % MOD * (j - (i > start)) % MOD + dp[i - 1][j] % MOD * (j - (i > end)) % MOD ) %= MOD; 
        (dp[i][j] += dp[i - 1][j + 1] % MOD * j % MOD) %= MOD; 
       }
       else { 
        if(s[i - 1] == 'L') {
          (dp[i][j] += dp[i - 1][j] % MOD * (j - (i > start)) % MOD) %= MOD; 
          (dp[i][j] += dp[i - 1][j + 1] % MOD * j % MOD) %= MOD;
        }
        if(s[i - 1] == 'R') { 
          (dp[i][j] += dp[i - 1][j] % MOD * (j - (i > end))   % MOD) %= MOD; 
          (dp[i][j] += dp[i - 1][j - 1] % MOD * (j - (i > start) - (i > end)) % MOD) %= MOD; 
        }
       }
     }
   }
  }
  cout << dp[N][1] << '\n'; 
  return 0; 
}
 
/* 
  // Assuming the other ends is always 'B' or 'R' and the first is always of type 'L' 
  dp[i][j] = {ways to fill first i-th numbers and there are currently j components}
*/