#include "bits/stdc++.h"

using namespace std; 

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(nullptr); 
 int w, k, c;
 cin >> w >> k >> c; 
 vector<vector<int>> dp(w + 1, vector<int>(k + 1, -1)); 
 function<int(int, int)> memo = [&](int rem_w, int rem_k) { 
  if(rem_w == rem_k) return 1; 
  if(rem_w <  rem_k) return 0; 
  int &res = dp[rem_w][rem_k]; 
  if(res != -1) return res;
  res = 0;  
  for(int i = 1; i <= rem_k - c; i++) { 
   res |= memo(rem_w - (rem_k - 1), i); 
  }
  return res;  
 }; 
 cout << (memo(w, k) ? "yes" : "no") << '\n'; 
 return 0; 
}