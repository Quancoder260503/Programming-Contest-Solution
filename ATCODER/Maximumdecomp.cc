#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())
#define int64_t long long

const int64_t oo = 1e9; 

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N, K; 
 cin >> N >> K; 
 vector<int>a(N), b(N); 
 for(int i = 0; i < N; i++) { 
  cin >> a[i] >> b[i]; 
 }
 vector<int>ord(N);
 iota(ord.begin(), ord.end(), 0); 
 sort(ord.begin(), ord.end(), [&](int i, int j) { 
  return (a[i] - 1) * b[j] < (a[j] - 1) * b[i]; 
 }); 
 vector<vector<int64_t>>dp(N + 1, vector<int64_t>(K + 1, -oo)); 
 dp[0][0] = 1; 
 for(int i = 0; i < N; i++) { 
  //cout << ord[i] << " " << a[ord[i]] << " " << b[ord[i]] << '\n'; 
  for(int j = 0; j <= K; j++) { 
   dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]); 
   if(j < K && dp[i][j] != -oo) { 
    dp[i + 1][j + 1] = max(dp[i + 1][j + 1], 1LL * a[ord[i]] * dp[i][j] + b[ord[i]]); 
   }
  }
 }
 cout << dp[N][K] << '\n'; 
 return 0; 
} 



