#include "bits/stdc++.h"

using namespace std; 

const int oo = 1e8; 

int cost(char curr, char target) { 
 if(curr == 'R' && target == 'B') return 2; 
 if(curr == 'R' && target == 'G') return 1; 
 if(curr == 'G' && target == 'B') return 1; 
 if(curr == 'G' && target == 'R') return 2; 
 if(curr == 'B' && target == 'R') return 1;
 if(curr == 'B' && target == 'G') return 2;  
 return 0; 
}

int main(void) { 
 string s; 
 cin >> s; 
 int n = s.size();  
 vector<vector<int>>prefix(n, vector<int>(3, 0));
 vector<vector<int>>dp(n, vector<int>(3, oo));  
 for(int i = 0; i < n; i++) { 
  prefix[i][0] = (i ? prefix[i - 1][0] : 0) + cost(s[i], 'R'); 
  prefix[i][1] = (i ? prefix[i - 1][1] : 0) + cost(s[i], 'G'); 
  prefix[i][2] = (i ? prefix[i - 1][2] : 0) + cost(s[i], 'B'); 
  dp[i][0] = prefix[i][0]; 
 }
 int min_so_far = oo; 
 for(int i = 0; i < n; i++) { 
  dp[i][1] = min(dp[i][1], prefix[i][1] + min_so_far); 
  min_so_far = min(min_so_far, dp[i][0] - prefix[i][1]); 
 }
 min_so_far = oo; 
 for(int i = 0; i < n; i++) { 
  dp[i][2] = min(dp[i][2], prefix[i][2] + min_so_far); 
  min_so_far = min(min_so_far, dp[i][1] - prefix[i][2]); 
 }
 cout << dp[n - 1][2] << '\n'; 
 return 0; 
}