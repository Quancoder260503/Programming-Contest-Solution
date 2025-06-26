#include <bits/stdc++.h>

using namespace std; 

#define sz(x) int(x.size())

int main() {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);
 int N, M; 
 cin >> N >> M;
 vector<vector<double>>dp(N + 1, vector<double>(M + 1));
 dp[0][0] = 1.;
 for(int ind = 1; ind <= N; ind++) {
  for(int sum = 0; sum <= M; sum++) { 
   for(int curr = 1; curr <= sum; curr++) { 
    dp[ind][sum] = max(dp[ind][sum], dp[ind - 1][sum - curr] * curr); 
   } 
  } 
 }
 double ret = dp[N][M]; 
 for(int i = 0; i < N; i++) { 
  ret = ret / 6;
 } 
 cout << fixed << setprecision(10) << ret << '\n'; 
 return 0;
}
