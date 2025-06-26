#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N, M; 
 cin >> N >> M; 
 if(M == 1) { 
  cout << 1 << '\n'; 
  return 0; 
 }
 vector<int>rank(N); 
 int sum = 0; 
 for(int i = 0; i < N; i++) { 
  cin >> rank[i]; 
  sum += rank[i]; 
 } 
 vector<vector<double>>dp(N + 1, vector<double>(N * M + 1)); // Probability that a player score s points after i-th round
 dp[0][0] = 1.; 
 for(int round = 0; round < N; round++) { 
  vector<double>prefix(N * M + 1); 
  for(int i = 0; i < N * M + 1; i++) { 
   prefix[i] = (i ? prefix[i - 1] : 0) + dp[round][i];
  }
  for(int score = 0; score < sz(dp[round]); score++) { 
   dp[round + 1][score] = (score ? prefix[score - 1] : 0) - 
                          (score > M ? prefix[score - M - 1] : 0) - 
                          (score >= rank[round] ? dp[round][score - rank[round]] : 0); 
   dp[round + 1][score] /= (M - 1); 
  }
 } 
 vector<double>prob(N * M + 1); 
 double ret = 0; 
 for(int i = 0; i < sum; i++) { 
  ret += dp[N][i]; 
  //cout << dp[N][i] << '\n'; 
 }
 cout << fixed << setprecision(10) << (M - 1) * ret + 1 << '\n'; 
 return 0; 
}