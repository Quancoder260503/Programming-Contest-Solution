#include <bits/stdc++.h> 

using namespace std; 

#define sz(x) int(x.size())

const int LOG = 12; 

int main() {
 string s; 
 cin >> s; 
 vector<vector<vector<vector<int>>>>dp(LOG, vector<vector<vector<int>>>(1 << 10, 
                                            vector<vector<int>>(2,
                                            vector<int>(2, -1)))); 
 function<int(int, int, int, int)> f = [&](int n, int mask, int prefix, int start) {
  if(n == sz(s)) return start;
  if(dp[n][mask][prefix][start] != -1) return dp[n][mask][prefix][start]; 
  int &ret = dp[n][mask][prefix][start]; 
  ret = 0; 
  int maxBound = (prefix ? s[n] - '0' : 9); 
  for(int digit = 0; digit <= maxBound; digit++) { 
   if(start) { 
    int next_mask = mask | (1 << digit); 
    if(__builtin_popcount(next_mask) > 2) continue; 
    ret += f(n + 1, next_mask, prefix & (digit == maxBound), start); 
   }
   else {
    if(digit == 0) { 
     ret += f(n + 1, mask, prefix & (digit == maxBound), start); 
    }
    else {
     int next_mask = mask | (1 << digit); 
     if(__builtin_popcount(next_mask) > 2) continue; 
     ret += f(n + 1, next_mask, prefix & (digit == maxBound), true);
     } 
    }
  } 
  return ret; 
 };
 cout << f(0, 0, true, false) << '\n'; 
 return 0;
}