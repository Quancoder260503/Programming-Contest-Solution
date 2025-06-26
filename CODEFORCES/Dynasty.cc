#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N;
  string S;  
  cin >> N; 
  vector<vector<int>>dp(26, vector<int>(26, -1)); 
  for(int i = 0; i < N; i++) { 
   cin >> S; 
   for(int c = 0; c < 26; c++) { 
    if(dp[c][S.front() - 'a'] != -1) { 
      dp[c][S.back() - 'a'] = max(dp[c][S.front() - 'a'] + sz(S), dp[c][S.back() - 'a']); 
    } 
   }
   dp[S.front() - 'a'][S.back() - 'a'] = max(dp[S.front() - 'a'][S.back() - 'a'], sz(S));  
  }

  int ans = 0; 
  for(int i = 0; i < 26; i++) { 
   ans = max(ans, dp[i][i]); 
  }
  cout << ans << '\n'; 
  return 0; 
}
