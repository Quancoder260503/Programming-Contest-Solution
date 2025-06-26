#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

int dp[100005][2][2]; 

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  string S; 
  cin >> S; 
  array<int, 2>cnt; 
  for(int i = 1; i < sz(S); i++) { 
   if(S[i - 1] == 'A' && S[i] == 'B') { 
    dp[i][1][0] = (i > 1 ? dp[i - 2][1][0] : 0) + 1;
    dp[i][0][0] += dp[i - 1][0][0];  
   }
   else if(S[i - 1] == 'B' && S[i] == 'A') { 
    dp[i][0][0] = (i > 1 ? dp[i - 2][0][0] : 0) + 1; 
    dp[i][1][0] += dp[i - 1][1][0]; 
   } else { 
     dp[i][0][0] += dp[i - 1][0][0];  
     dp[i][1][0] += dp[i - 1][1][0]; 
   }
  }
  for(int i = sz(S) - 2; i >= 0; i--) { 
   if(S[i] == 'A' && S[i + 1] == 'B') { 
    dp[i][1][1] = dp[i + 2][1][1] + 1; 
    dp[i][0][1] += dp[i + 1][0][1]; 
   }
   else if(S[i] == 'B' && S[i + 1] == 'A') { 
    dp[i][0][1] = dp[i + 2][0][1] + 1; 
    dp[i][1][1] += dp[i + 1][1][1];
   } else {  
      dp[i][0][1] += dp[i + 1][0][1]; 
      dp[i][1][1] += dp[i + 1][1][1];
    }
  }
  for(int i = 0; i + 1 < sz(S); i++) { 
    if((dp[i][0][0] && dp[i + 1][1][1]) || (dp[i][1][0] && dp[i + 1][0][1])) { 
     cout << "YES\n"; 
     exit(0); 
    }
  }
  cout << "NO\n"; 
  return 0;
}
