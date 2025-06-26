#include "bits/stdc++.h"

using namespace std;

int64_t dp[502][502];
int a[502], b[502];  

int main(void) {
 ios_base::sync_with_stdio(false);
 cin.tie(0); 
 cout.tie(0);
 int N, M, K; 
 cin >> N >> M >> K; 
 for(int i = 0; i < N; i++) { 
  cin >> a[i]; 
 }
 for(int i = 0; i < N; i++) { 
  cin >> b[i]; 
 }
 a[N] = M; 
 memset(dp, 63, sizeof(dp));
 dp[0][0] = 0;
 for(int i = 0; i <= N; i++) { 
  for(int skip = 0; skip <= K; skip++) { 
   for(int j = 0; j < i; j++) { 
    if(skip + i - j - 1 <= K) { 
     dp[i][skip + i - j - 1] = min(dp[i][skip + i - j - 1], dp[j][skip] + 1LL * (a[i] - a[j]) * b[j]); 
    } 
   }
  }  
 }
 int64_t ret = LLONG_MAX / 2; 
 for(int i = 0; i <= K; i++) { 
  ret = min(ret, dp[N][i]); 
//  cout << dp[N][i] << '\n'; 
 }
 cout << ret << '\n'; 
 return 0;
}