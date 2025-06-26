#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int oo = 1e9; 

void solve(void) { 
 int N; 
 string S; 
 cin >> N >> S;
 vector<vector<pair<int, int>>>dp(N + 1, vector<pair<int, int>>(2, {oo, oo}));
 dp[0][0] = dp[0][1] = {0, 1}; 
 for(int i = 2; i <= N; i++) {
  if(S[i - 1] == S[i - 2]) { 
   int c = S[i - 1] - '0'; 
   dp[i][c] = dp[i - 2][c];  
   if(dp[i][c].first > dp[i - 2][c ^ 1].first) { 
    dp[i][c] = {dp[i - 2][c ^ 1].first, dp[i - 2][c ^ 1].second + 1}; 
   } else if(dp[i][c].first == dp[i - 2][c ^ 1].first) { 
    dp[i][c].second = min(dp[i][c].second, dp[i - 2][c ^ 1].second + 1); 
   }
   dp[i][c ^ 1] = {dp[i - 2][c ^ 1].first + 2, dp[i - 2][c ^ 1].second}; 
   if(dp[i][c ^ 1].first > dp[i - 2][c].first + 2) { 
    dp[i][c ^ 1] = {dp[i - 2][c].first + 2, dp[i - 2][c].second + 1}; 
   } else if(dp[i][c ^ 1].first == dp[i - 2][c].first + 2) { 
    dp[i][c ^ 1].second = min(dp[i][c ^ 1].second, dp[i - 2][c].second + 1); 
   }
  } else { 
    int c = S[i - 1] - '0';
    dp[i][c] = {dp[i - 2][c].first + 1, dp[i - 2][c].second}; 
    if(dp[i][c].first > dp[i - 2][c ^ 1].first + 1) { 
     dp[i][c] = {dp[i - 2][c ^ 1].first + 1, dp[i - 2][c ^ 1].second + 1}; 
    } else if(dp[i][c].first == dp[i - 2][c ^ 1].first + 1) { 
     dp[i][c].second = min(dp[i][c].second, dp[i - 2][c ^ 1].second + 1); 
    }
    dp[i][c ^ 1] = {dp[i - 2][c ^ 1].first + 1, dp[i - 2][c ^ 1].second}; 
    if(dp[i][c ^ 1].first > dp[i - 2][c].first + 1) { 
     dp[i][c ^ 1] = {dp[i - 2][c].first + 1, dp[i - 2][c].second + 1}; 
    } else if(dp[i][c ^ 1].first == dp[i - 2][c].first + 1) { 
     dp[i][c ^ 1].second = min(dp[i][c ^ 1].second, dp[i - 2][c].second + 1); 
    }
  }
 }
 pair<int, int> ret = min(dp[N][0], dp[N][1]); 
 cout << ret.first << " " << ret.second << '\n'; 
 return; 
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int T; 
  for(cin >> T; T--; ) { 
   solve(); 
  }
  return 0;
}