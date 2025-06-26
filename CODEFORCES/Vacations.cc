#include "bits/stdc++.h"

using namespace std; 

int dp[1005][3], a[1005]; 

int main(void) {
 int N; 
 cin >> N;
 memset(dp, -1, sizeof(dp));  
 for(int i = 0; i < N; i++) { 
  cin >> a[i]; 
 }
 for(int i = 0; i < N; i++) { 
  if(i) { 
   if(a[i] == 3) {
    dp[i][1] = max(dp[i - 1][0] + 1, dp[i - 1][2] + 1); 
    dp[i][2] = max(dp[i - 1][0] + 1, dp[i - 1][1] + 1); 
   } else if(a[i] == 2) { 
     dp[i][2] = max(dp[i - 1][0] + 1, dp[i - 1][1] + 1); 
   } else if(a[i] == 1) { 
     dp[i][1] = max(dp[i - 1][0] + 1, dp[i - 1][2] + 1); 
   }
    dp[i][0] = max({dp[i - 1][0], dp[i - 1][1], dp[i - 1][2]}); 
  } else { 
    if(a[i] == 3) { 
     dp[i][2] = dp[i][1] = 1; 
    } 
    if(a[i] == 2) dp[i][2] = 1; 
    if(a[i] == 1) dp[i][1] = 1; 
    dp[i][0] = 0; 
  }
 }
 cout << N - max({dp[N - 1][0], dp[N - 1][1], dp[N - 1][2]}) << '\n'; 
 return 0; 
}