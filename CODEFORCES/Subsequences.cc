#include "bits/stdc++.h"
 
using namespace std;
 
#define int64_t long long
#define sz(x) int(x.size())
 
void solve() { 
 int64_t K;
 int N;  
 string S; 
 cin >> N >> K >> S; 
 S = " " + S; 
 vector<vector<int64_t>>dp(sz(S), vector<int64_t>(sz(S))); 
 vector<int>pre(26); 
 dp[0][0] = 1; 
 for(int pos = 1; pos < sz(S); pos++) { 
  dp[pos][0] = 1; 
  for(int len = 1; len <= pos; len++) { 
   dp[pos][len] = dp[pos - 1][len - 1] + dp[pos - 1][len];   
   int j = pre[S[pos] - 'a']; 
   if(j && len >= pos - j) {
    dp[pos][len] = dp[pos][len] - dp[j - 1][len - pos + j]; 
   }
   dp[pos][len] = min(dp[pos][len], K); 
  }
  pre[S[pos] - 'a'] = pos; 
 }
 int64_t ans = 0; 
 for(int j = 0; j <= N; j++) { 
  if(K < dp[N][j]) { 
   ans += j * K; 
   K = 0; 
   break; 
  } else { 
   ans += j * dp[N][j]; 
   K = K - dp[N][j]; 
  }
 }
 cout << (K == 0 ? ans : -1)  << '\n'; 
 return; 
}
 
int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  solve(); 
  return 0;
}
