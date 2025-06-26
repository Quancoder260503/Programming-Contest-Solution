#include <bits/stdc++.h>

using namespace std; 

const int64_t oo = 1e14; 

#define sz(x) int(x.size())

int main() {
 int N; 
 cin >> N; 
 vector<int>c(N + 1); 
 for(int i = 1; i <= N; i++) { 
  cin >> c[i]; 
 } 
 sort(c.begin(), c.end());
 vector<vector<int64_t>>dp(N + 1, vector<int64_t>(N + 1, -1)); 
 function<int64_t(int, int)> f = [&](int l, int r) -> int64_t { 
  if(l >= r) return 0; 
  int64_t &ret = dp[l][r]; 
  if(ret != -1) return ret; 
  ret = c[r] - c[l] + min(f(l + 1, r), f(l, r - 1)); 
  return ret; 
 }; 
 cout << f(1, N) << '\n'; 
 return 0; 
}
