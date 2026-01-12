#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int LOG = 30; 

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  int n, T;
  cout << fixed << setprecision(10); 
  for(cin >> T; T--; ) { 
   cin >> n; 
   vector<int>a(n); 
   vector<double>prob(n); 
   for(auto &x : a) { 
    cin >> x; 
   }
   for(auto &x : prob) { 
    cin >> x; 
   }
   double ret = 0.; 
   for(int b = LOG; b >= 0; b--) { 
    vector<vector<double>>dp(n, vector<double>(2));
    dp[0][1] = (a[0] >> b & 1 ? prob[0] : 0.); 
    dp[0][0] = (a[0] >> b & 1 ? 1. - prob[0] : 1.); 
    for(int i = 1; i < n; i++) { 
     if(a[i] >> b & 1) {     
      dp[i][1] = dp[i - 1][1] * (1. - prob[i]) + dp[i - 1][0] * prob[i]; 
      dp[i][0] = dp[i - 1][0] * (1. - prob[i]) + dp[i - 1][1] * prob[i];   
     } else { 
      dp[i] = dp[i - 1]; 
     }
    }  
  //  cout << dp[n - 1][1] << '\n'; 
    ret += dp[n - 1][1] * (1 << b); 
   }
   cout << ret << '\n'; 
  }
  return 0; 
}