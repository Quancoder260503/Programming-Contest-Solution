#include <bits/stdc++.h> 
 
using namespace std; 
 
const int MOD = 1e9 + 7; 
 
int main() { 
 int N, T;
 cin >> N >> T; 
 vector<int>a(N), col(N); 
 for(int i = 0; i < N; i++) { 
  cin >> a[i] >> col[i];    
 } 
 vector<vector<unordered_map<int, int>>>dp(N, vector<unordered_map<int, int>>(1 << N));
 for(int i = 0; i < N; i++) { 
  dp[i][1 << i][a[i]] = 1; 
 } 
 for(int mask = 0; mask < (1 << N); mask++) { 
  for(int last = 0; last < N; last++) {
   if(mask & (1 << last)) { 
    for(int next_ = 0; next_ < N; next_++) { 
     if(mask & (1 << next_)) continue; 
     if(col[last] == col[next_]) continue; 
     for(int currT = 0; currT + a[next_] <= T; currT++) {
      if(dp[last][mask].count(currT)) { 
       (dp[next_][mask ^ (1 << next_)][currT + a[next_]] += dp[last][mask][currT]) %= MOD; 
      } 
     } 
    } 
   } 
  } 
 } 
 int64_t ret = 0; 
 for(int mask = 0; mask < (1 << N); mask++) {
  for(int i = 0; i < N; i++) { 
   if(dp[i][mask].count(T)) { 
    (ret += dp[i][mask][T]) %= MOD; 
   } 
  }
 } 
 cout << ret << '\n'; 
 return 0;
}