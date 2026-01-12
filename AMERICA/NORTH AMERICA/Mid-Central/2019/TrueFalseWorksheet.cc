#include "bits/stdc++.h"

using namespace std;

const int MOD = 1e9 + 7; 

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);
 int n, m; 
 cin >> n >> m; 
 vector<int>diff(n + 1, -1), same(n + 1, -1); 
 string s; 
 iota(same.begin() + 1, same.end(), 1); 
 for(int i = 0, x, y; i < m; i++) { 
  cin >> x >> y >> s;
  if(s[0] == 's') { 
    same[y] = min(same[y], x);
  } else { 
    diff[y] = max(diff[y], x); 
  }
 }
 for(int i = 1; i <= n; i++) { 
  if(diff[i] >= same[i]) { 
    cout << 0 << '\n'; 
    return 0;
  }
 }
 // dp[i][j] = {number of ways to paint the first i-th given that the last different position is at j-th}
 vector<vector<int64_t>>dp(n + 1, vector<int64_t>(n + 1)); 
 dp[1][1] = 2; 
 for(int i = 2; i <= n; i++) { 
  for(int j = diff[i] + 1; j <= same[i]; j++) { 
    (dp[i][j] += dp[i - 1][j]) %= MOD; 
  }
  if(same[i] == i) { 
   for(int j = 1; j < i; j++) { 
    (dp[i][i] += dp[i - 1][j]) %= MOD; 
   }
  }
 }
 int64_t ans = 0; 
 for(int i = 1; i <= n; i++) { 
  (ans += dp[n][i]) %= MOD; 
 }
 cout << ans << '\n'; 
 return 0; 
}