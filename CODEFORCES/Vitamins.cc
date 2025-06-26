#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int oo = 1e9 + 10; 

#define int64_t long long
#define sz(x) int(x.size())

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N; 
 cin >> N; 
 vector<vector<int64_t>>dp(N + 1, vector<int64_t>(8, oo)); 
 dp[0][0] = 0; 
 for(int i = 0; i < N; i++) {
  int c; 
  string s; 
  cin >> c >> s; 
  int curr = 0; 
  for(int j = 0; j < sz(s); j++) { 
   curr |= (1 << (s[j] - 'A')); 
  }
  for(int mask = 0; mask < 8; mask++) { 
    dp[i + 1][mask | curr] = min(dp[i + 1][mask | curr], dp[i][mask] + c); 
    dp[i + 1][mask] = min(dp[i][mask], dp[i + 1][mask]); 
  }
 }
 cout << (dp[N][7] == oo ? -1 : dp[N][7]) << '\n'; 
 return 0; 
}

/**
 * 
 * 
 */
