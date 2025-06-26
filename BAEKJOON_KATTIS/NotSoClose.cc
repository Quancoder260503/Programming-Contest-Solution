#include <bits/stdc++.h>

using namespace std; 

const int MOD = 1e9 + 7; 

int main() {
  int R, C; 
  cin >> R >> C; 
  vector<int>isGood(1 << R); 
  vector<vector<int>>g(1 << R); 
  for(int mask = 0; mask < (1 << R); mask++) { 
    int flag = true; 
    for(int i = 1; i < R; i++) { 
     if((mask >> i & 1) && (mask >> (i - 1) & 1)) { 
      flag = false; 
      break; 
     } 
    }
    isGood[mask] = flag; 
  } 
  for(int mask1 = 0; mask1 < (1 << R); mask1++) { 
   if(!isGood[mask1]) continue; 
   for(int mask2 = 0; mask2 < (1 << R); mask2++) { 
    if(!isGood[mask2]) continue; 
    int flag = true;
    for(int i = 0; i < R; i++) { 
     if(mask1 >> i & 1) { 
      if(mask2 >> i & 1) { 
        flag = false; 
        break; 
      } 
      if(i > 0 && (mask2 >> (i - 1) & 1)) { 
        flag = false; 
        break; 
      } 
      if(i + 1 < R && (mask2 >> (i + 1) & 1)) { 
        flag = false; 
        break; 
      } 
     } 
    }
    if(flag) { 
     g[mask1].push_back(mask2); 
    } 
   } 
  } 
  vector<vector<int64_t>>dp(C, vector<int64_t>(1 << R, 0)); 
  for(int mask = 0; mask < (1 << R); mask++) {
    dp[0][mask] = isGood[mask]; 
  } 
  for(int i = 1; i < C; i++) { 
   for(int mask = 0; mask < (1 << R); mask++) { 
    if(isGood[mask]) { 
      for(auto v : g[mask]) { 
        (dp[i][mask] += dp[i - 1][v]) %= MOD; 
      } 
    } 
   } 
  } 
  int64_t ret = 0; 
  for(int mask = 0; mask < (1 << R); mask++) { 
    (ret += dp[C - 1][mask]) %= MOD; 
  } 
  cout << ret << '\n'; 
  return 0;
}