#include "bits/stdc++.h"

using namespace std; 

const int64_t oo = 1e17;

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N; 
  cin >> N; 
  vector<int>cost(N); 
  vector<string>s(N); 
  for(int i = 0; i < N; i++) { 
   cin >> cost[i]; 
  }
  for(int i = 0; i < N; i++) { 
   cin >> s[i]; 
  }
  vector<vector<int64_t>>dp(N + 1, vector<int64_t>(2, oo)); 
  dp[0][0] = 0;
  dp[0][1] = cost[0]; 
  for(int i = 1; i < N; i++) { 
   string rs = s[i], rsp = s[i - 1]; 
   reverse(rs.begin(), rs.end());
   reverse(rsp.begin(), rsp.end()); 
   if(s[i - 1] <= s[i]) { 
    dp[i][0] = min(dp[i][0], dp[i - 1][0]); 
   } 
   if(s[i - 1] <= rs) { 
    dp[i][1] = min(dp[i][1], dp[i - 1][0] + cost[i]); 
   }
   if(rsp <= s[i]) { 
    dp[i][0] = min(dp[i][0], dp[i - 1][1]); 
   }
   if(rsp <= rs) { 
    dp[i][1] = min(dp[i][1], dp[i - 1][1] + cost[i]); 
   }
  }
  int64_t ret = min(dp[N - 1][1], dp[N - 1][0]); 
  cout << (ret >= oo ? -1 : ret) << '\n'; 
  return 0; 
}

