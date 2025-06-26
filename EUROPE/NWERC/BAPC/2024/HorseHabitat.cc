#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N, M, Q;
 cin >> N >> M >> Q; 
 vector<vector<int>>prefix(N + 7, vector<int>(M + 7)), dp(N + 7, vector<int>(M + 7));
 for(int i = 1; i <= N; i++) { 
  for(int j = 1; j <= M; j++) { 
   char c; 
   cin >> c; 
   if(c == '.') dp[i][j] = dp[i - 1][j] + 1; 
  }
 } 
 for(int i = 1; i <= N; i++) { 
  vector<pair<int, int>>stk; 
  int c = -1; 
  for(int j = 0; j <= M + 1; j++) {
   int w = 0; 
   while(c > 0 && stk[c].second >= dp[i][j]) { 
    w += stk[c].first; 
    int h = max(dp[i][j], stk[c - 1].second); 
    prefix[h + 1][w]++; 
    prefix[stk[c].second + 1][w]--; 
    c--; 
    stk.pop_back(); 
   }
   c++; 
   stk.push_back({w + 1, dp[i][j]});  
  }
 }
 for (int i = 1; i <= N; i++) {
  for (int j = 1; j <= M; j++) {
   prefix[i + 1][j] += prefix[i][j];
  }
  int acc1= 0, acc2 = 0;
  for(int j = M; j >= 1; j--) {
   acc1 += prefix[i][j]; 
   acc2 += acc1; 
   prefix[i][j] = acc2; 
  }
 }
 for(int i = 0, u, v; i < Q; i++) { 
  cin >> u >> v; 
  cout << prefix[u][v] << '\n'; 
 }
 return 0; 
}