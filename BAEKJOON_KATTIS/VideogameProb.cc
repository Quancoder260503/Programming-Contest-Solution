#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

void solve() {  
 int N, M; 
 cin >> N; 
 vector<double>Prob; 
 for(int i = 0; i < N; i++) { 
  int c; double prob; 
  cin >> c >> prob;
  for(int j = 0; j < c; j++) { 
   Prob.push_back(prob); 
  } 
 }
 cin >> M; 
 N = sz(Prob); 
 vector<vector<double>>dp(N + 1, vector<double>(M + 1)); 
 dp[0][0] = 1.; 
 for(int trial = 1; trial <= M; trial++) { 
  for(int success = 0; success <= N; success++) { 
   double probFail = (success < N ? dp[success][trial - 1] * (1. - Prob[success]) : dp[success][trial - 1]); 
   double probSucc = (success > 0 ? dp[success - 1][trial - 1] *   Prob[success - 1]  : 0); 
   dp[success][trial] += (probFail + probSucc);
  }
 }
 cout << dp[N][M] << '\n'; 
 return; 
}

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int T; 
 cout << fixed << setprecision(3); 
 for(cin >> T; T--; ) { 
  solve(); 
 }
 return 0; 
}