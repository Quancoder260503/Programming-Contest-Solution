#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int oo = 1e9; 

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);
 int n; 
 cin >> n; 
 vector<int>pos(n); 
 for(int i = 0, x; i < n; i++) { 
  cin >> x; 
  pos[--x] = i; 
 }
 vector<vector<int>>dp(n, vector<int>(n, -1)); 
 function<int(int, int)> memo = [&](int i, int j) { 
  if(i >= j) return 0; 
  int &ret = dp[i][j]; 
  if(ret != -1) return ret; 
  ret = oo; 
  for(int k = i + 1; k <= j; k++) { 
   ret = min(ret, memo(i, k - 1) + memo(k, j) + abs(pos[i] - pos[k]));  
  }
  return ret; 
 };
 cout << memo(0, n - 1) << '\n';  
 return 0; 
}