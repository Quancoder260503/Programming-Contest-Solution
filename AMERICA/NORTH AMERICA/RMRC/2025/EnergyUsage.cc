#include "bits/stdc++.h"

using namespace std;

const int maxn = 1005; 
const int oo = 1e9; 
const int L = 150; 

int dp[maxn][25]; // dp[i][j] : minimum energy spent to reach city i with j energy stored 

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(nullptr); 
 int n, m, B; 
 cin >> n >> m >> B;
 vector<array<int, 3>>days(n); 
 for(auto &x: days) { 
  cin >> x[0] >> x[1] >> x[2]; 
 } 
 vector<vector<int>>c(n, vector<int>(m)), d(n, vector<int>(m)); 
 for(int i = 0; i < n; i++) { 
  for(int j = 0; j < m; j++) {
   cin >> c[i][j]; 
  }
 }
 for(int i = 0; i < n; i++) { 
  for(int j = 0; j < m; j++) { 
   cin >> d[i][j]; 
  }
 }
 vector<vector<int>>dp(n + 1, vector<int>(B + 1, oo)); 
 dp[0][0] = 0; 
 for(int day = 0; day < n; day++) { 
  const auto &[price, need, gain] = days[day]; 
  for(int energy = 0; energy <= B; energy++) { 
   int curr_cost = dp[day][energy]; 
   if(curr_cost == oo) continue;
   if(need >= energy + gain) { 
    int to_buy = need - energy - gain; 
    for(int extra = 0; extra <= L; extra++) { 
     dp[day + 1][min(B, extra)] = min(dp[day + 1][min(B, extra)], curr_cost + (to_buy + extra) * price);
     for(int j = 0; j < m; j++) { 
      if(extra >= d[day][j]) { 
       dp[day + 1][min(B, extra - d[day][j])] = min(dp[day + 1][min(B, extra - d[day][j])], curr_cost + (to_buy + extra) * price - c[day][j]); 
      }
     }    
    }
   } else { 
    int rem = energy + gain - need; 
    for(int extra = 0; extra <= L; extra++) { 
     dp[day + 1][min(B, rem + extra)] = min(dp[day + 1][min(B, rem + extra)], curr_cost + extra * price); 
     for(int j = 0; j < m; j++) { 
      if(rem + extra >= d[day][j]) { 
       dp[day + 1][min(B, rem + extra - d[day][j])] = min(dp[day + 1][min(B, rem + extra - d[day][j])], curr_cost + extra * price - c[day][j]); 
      }
     }
    }
   }
  }
 }
 int ans = oo;
 for(int energy = 0; energy <= B; energy++) { 
  ans = min(ans, dp[n][energy]); 
 } 
 //cout << dp[1][0] << '\n'; 
 cout << ans << '\n'; 
 return 0; 
}