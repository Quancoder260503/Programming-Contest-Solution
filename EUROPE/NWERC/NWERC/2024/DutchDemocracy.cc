#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define int64_t long long

int64_t dp[62][600002]; 

int main(void) {
 int N; 
 cin >> N; 
 if(N == 1) { 
  cout << 1 << '\n'; 
  exit(0); 
 }
 vector<int>a(N); 
 int sum = 0; 
 for(int i = 0; i < N; i++) { 
  cin >> a[i];
  sum += a[i];  
 }
 sort(a.rbegin(), a.rend()); 
 dp[0][0] = dp[0][a[0]] = 1;
 int64_t ans = 0; 
 ans += (sum < 2 * a[0]); 
 for(int i = 1; i < N; i++) { 
  for(int j = 0; j < 600002; j++) { 
   dp[i][j] += dp[i - 1][j]; 
   if(j >= a[i]) dp[i][j] += dp[i - 1][j - a[i]]; 
  }
  for(int j = 0; j < 600002; j++) {
   if(sum < 2 * (j + a[i]) && 2 * j <= sum) ans += dp[i - 1][j]; 
  } 
 }
 cout << ans << '\n'; 
 return 0; 
}