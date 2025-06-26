#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int C = 5000; 

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int N; 
  cin >> N; 
  vector<int>a(N); 
  for(int i = 0; i < N; i++) { 
   cin >> a[i]; 
  } 
  sort(a.begin(), a.end()); 
  queue<pair<int, int>>q, nq; 
  vector<vector<int>>dp(C + 1, vector<int>(C + 1, -1)); 
  q.push({0, 0}); 
  dp[0][0] = 0; 
  auto doit = [&](int w1, int w2, int f1, int f2) { 
   if(w1 > C || w2 > C) return; 
   if(dp[w1][w2] != -1) return; 
   dp[w1][w2] = dp[f1][f2] + 1;
   nq.push({w1, w2}); 
   return; 
  }; 
  for(int i = 0; i < N; i++) {
   while(sz(q)) { 
    auto [w1, w2] = q.front();
    q.pop(); 
    doit(w1 + a[i], w2, w1, w2); 
    doit(w1, w2 + a[i], w1, w2); 
   } 
   q = move(nq); 
  }
  for(int i = 0; i <= C; i++) { 
   for(int j = 0; j <= C; j++) { 
    if(i > 0) dp[i][j] = max(dp[i - 1][j], dp[i][j]); 
    if(j > 0) dp[i][j] = max(dp[i][j - 1], dp[i][j]); 
   } 
  }
  int64_t ret = 0; 
  for(int i = 1; i <= C; i++) { 
   for(int j = 1; j <= C; j++) { 
    // cout << dp[i][j] << '\n'; 
    //if(dp[i][j] < 0) dp[i][j] = 0;
    (ret += 1LL * (i ^ j ^ dp[i][j])); 
   } 
  } 
  cout << ret << '\n'; 
  return 0;
}