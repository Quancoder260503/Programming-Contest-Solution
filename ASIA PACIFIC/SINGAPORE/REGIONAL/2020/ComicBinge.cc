#include "bits/stdc++.h"
 
using namespace std; 
 
#define int64_t long long
#define sz(x) int(x.size())
 
const int oo = 1e9; 
 
class Comic { 
 public :
  void solve() { 
  int N; 
  cin >> N; 
  vector<int64_t>a(N + 1), b(N + 1); 
  int T = 0; 
  for(int i = 1; i <= N; i++) { 
   cin >> a[i]; 
   a[i] += a[i - 1]; 
  }
  for(int i = 1; i <= N; i++) { 
   cin >> b[i]; 
   T += b[i]; 
  }
  vector<vector<int64_t>>dp(N + 1, vector<int64_t>(T + 1, -oo));
  dp[1][b[1]] = 0; 
  for(int i = 2; i <= N; i++) { 
   for(int j = 1; j <= T; j++) { 
    dp[i][j] = dp[i][j - 1]; 
    if(j >= b[i]) { 
     dp[i][j] = max(dp[i][j], min(dp[i - 1][j - b[i]] + b[i], a[i - 1])); 
     dp[i][j] = max(dp[i][j], min(dp[i - 2][j - b[i]] + b[i], a[i - 1])); 
    }
   }
  } 
  int64_t ans = oo; 
  for(int i = 0; i <= T; i++) { 
   ans = min(ans, i + a[N] - dp[N][i]); 
  }
  cout << ans << '\n'; 
  return;  
 } 
}; 

// dp[i][j] = {min time for andy to reach the ith book knowing that he has j books}
 
int main(void) { 
  Comic task; 
  task.solve(); 
  return 0; 
}