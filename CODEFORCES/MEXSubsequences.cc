#include "bits/stdc++.h"

using namespace std;

const int MOD = 998244353; 

int64_t dp[500007][2]; 

void solve() { 
 int N; 
 cin >> N;
 dp[0][0] = 1; 
 for(int i = 0, x; i < N; i++) { 
  cin >> x;
  (dp[x + 1][0] += dp[x + 1][0] + dp[x][0]) %= MOD; 
  if(x > 0) (dp[x - 1][1] += dp[x - 1][0] + dp[x - 1][1]) %= MOD; 
  (dp[x + 1][1] += dp[x + 1][1]) %= MOD; 
 } 
 int64_t ans = 0; 
 for(int i = 0; i <= N; i++) { 
  (ans += dp[i][0] + dp[i][1]) %= MOD; 
  dp[i][0] = dp[i][1] = 0; 
 }
 (ans += MOD - 1) %= MOD; 
 cout << ans << '\n'; 
 return; 
}

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int T; 
 for(cin >> T; T--; ) { solve(); } 
 return 0; 
}
/** 
 Type 0 : the sequence is (0, 1, 2, 3, ..., x[i] - 2, ,x[i]) -> mex : (x[i] - 1)
 Type 1 : the sequence is (0, 1, 2, 3, ...., x[i] - 1, x[i]) -> mex : (x[i] + 1)

 dp[x[i]][1] := dp[x[i] - 1][1] + 2 * dp[x[i]][1]
 dp[x[i]][0] := dp[x[i] - 1][0] + 
*/