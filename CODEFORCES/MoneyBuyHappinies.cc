#include <bits/stdc++.h>
 
using namespace std; 
 
#define int64_t long long
#define sz(x) int(x.size())

const int oo = 1e9; 


int main() { 
 int N, M, T; 
 for(cin >> T; T--; ) {
  cin >> N >> M;
  vector<int>a(N), cost(N); 
  for(int i = 0; i < N; i++) { 
   cin >> cost[i] >> a[i]; 
  } 
  int sum = accumulate(a.begin(), a.end(), 0); 
  vector<vector<int64_t>>dp(N + 1, vector<int64_t>(sum + 1, -oo));
  dp[0][0] = 0;
  for(int ind = 0; ind < N; ind++) { 
   for(int c = 0; c <= sum; c++) { 
    if(dp[ind][c] == -oo) continue; 
    dp[ind + 1][c] = max(dp[ind + 1][c], dp[ind][c] + M); 
    if(c + a[ind] <= sum && dp[ind][c] >= cost[ind]) { 
     dp[ind + 1][c + a[ind]] = max(dp[ind + 1][c + a[ind]], dp[ind][c] + M - cost[ind]); 
    } 
   } 
  }
  for(int i = sum; i >= 0; i--) {
   if(dp[N][i] >= 0) { 
    cout << i << "\n"; 
    break; 
   } 
  } 
 } 
 return 0;
}