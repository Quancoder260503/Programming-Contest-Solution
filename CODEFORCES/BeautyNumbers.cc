#include <bits/stdc++.h> 
 
using namespace std; 
 
#define sz(x) int(x.size())
 
const int MOD = 1e9 + 7; 
 
int main() { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);
 int T; 
 vector<vector<int64_t>>Comb(2002, vector<int64_t>(52)); 
 Comb[0][0] = 1; 
 vector<vector<int64_t>>cache(52, vector<int64_t>(1002, 0)); 
 for(int i = 1; i < sz(Comb); i++) { 
  for(int j = 0; j < min(sz(Comb[i]), i + 1); j++) {
   (Comb[i][j] = Comb[i - 1][j] + (j ? Comb[i - 1][j - 1] : 0)) %= MOD; 
  }
 }
 vector<int64_t>fact(52); 
 fact[0] = 1; 
 for(int i = 1; i < sz(fact); i++) { 
  fact[i] = fact[i - 1] % MOD * i % MOD; 
 } 
 vector<vector<int64_t>>dp(1002, vector<int64_t>(1002)), ndp(1002, vector<int64_t>(1002));
 dp[0][1] = ndp[0][1] = 1;
 for(int pos = 0; pos < sz(cache); pos++) { 
  for(int length = 0; length < sz(dp); length++) { 
   for(int max_dist = 0; max_dist + 1 < sz(dp[length]); max_dist++) {
    (ndp[length][max_dist + 1] += ndp[length][max_dist]) %= MOD;  // expanding the length of the next element 
    if(pos > 0 && length + max_dist < sz(dp)) {
     (ndp[length + max_dist][max_dist + 1] += dp[length][max_dist]) %= MOD;  // adding a range of (max_dist) to the set 
    }
   }
  }
  dp.swap(ndp); 
  for(int i = 0; i < sz(ndp); i++) { 
   for(int j = 0; j < sz(ndp); j++) {
     ndp[i][j] = 0; 
   }
  } 
  for(int length = 0; length < sz(dp); length++) { 
   for(int size = length; size + 1 < sz(dp[length]); size++) {
    (cache[pos][size] += 1LL * fact[pos] % MOD * 
                             (dp[length][size + 1] - dp[length][0] + MOD) % MOD *    
                             Comb[size - length + pos][pos] % MOD) %= MOD; 
   } 
  }
 }
 for(cin >> T; T--; ) { 
  int N, K; 
  cin >> N >> K; 
  if(K > 50) {
   cout << 0 << '\n'; 
   continue; 
  }
  cout << cache[K][N] << '\n'; 
 } 
 return 0;
}