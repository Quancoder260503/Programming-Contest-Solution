#include <bits/stdc++.h> 

using namespace std; 

#define sz(x) int(x.size())

const int MOD = 1e9 + 7; 

int main() { 
 int N, T;
 cin >> N >> T; 
 vector<int>a(N), col(N); 
 vector<int64_t>fact(N + 1); 
 fact[0] = 1; 
 for(int i = 1; i < sz(fact); i++) {
  fact[i] = fact[i - 1] % MOD * i % MOD; 
 }
 vector<vector<int>>cc(3); 
 for(int i = 0; i < N; i++) { 
  cin >> a[i] >> col[i];   
  cc[col[i] - 1].push_back(a[i]); 
 } 
 vector<vector<int64_t>>dp(sz(cc[0]) + 1, vector<int64_t>(T + 1)); 
 dp[0][0] = 1; 
 for(int ind = 0; ind < sz(cc[0]); ind++) { 
  for(int choose = sz(cc[0]); choose >= 0; choose--) { 
   for(int total = T; total >= 0; total--) { 
    if(total + cc[0][ind] <= T && choose < sz(cc[0])) {
      (dp[choose + 1][total + cc[0][ind]] += dp[choose][total]) %= MOD; 
    } 
   } 
  } 
 }
 vector<vector<vector<int64_t>>>dyn(sz(cc[1]) + 1, 
                                   vector<vector<int64_t>>(sz(cc[2]) + 1, vector<int64_t>(T + 1)));
 dyn[0][0][0] = 1;
 for(int ind = 0; ind < sz(cc[1]) + sz(cc[2]); ind++) {
  for(int stoneA = sz(cc[1]); stoneA >= 0; stoneA--) { 
   for(int stoneB = sz(cc[2]); stoneB >= 0; stoneB--) { 
    for(int currT = T; currT >= 0; currT--) { 
      if(ind < sz(cc[1])) { 
       if(stoneA < sz(cc[1]) && currT + cc[1][ind] <= T) { 
        (dyn[stoneA + 1][stoneB][currT + cc[1][ind]] += dyn[stoneA][stoneB][currT]) %= MOD; 
       } 
      } else { 
       if(stoneB < sz(cc[2]) && currT + cc[2][ind - sz(cc[1])] <= T) {
        (dyn[stoneA][stoneB + 1][currT + cc[2][ind - sz(cc[1])]] += dyn[stoneA][stoneB][currT]) %= MOD; 
       } 
      } 
    } 
   } 
  }
 }
 vector<vector<vector<vector<int64_t>>>>ways(sz(cc[0]) + 2, 
                                             vector<vector<vector<int64_t>>>(sz(cc[1]) + 2, 
                                             vector<vector<int64_t>>(sz(cc[2]) + 2, 
                                             vector<int64_t>(3))));
 ways[0][0][1][2] = ways[1][0][0][0] = ways[0][1][0][1] = 1; 
 for(int stones1 = 0; stones1 <= sz(cc[0]); stones1++) { 
  for(int stones2 = 0; stones2 <= sz(cc[1]); stones2++) { 
   for(int stones3 = 0; stones3 <= sz(cc[2]); stones3++) { 
    if(stones1 < sz(cc[0])) { 
     (ways[stones1 + 1][stones2][stones3][0] += ways[stones1][stones2][stones3][1] + 
                                                ways[stones1][stones2][stones3][2]) %= MOD;     
    }
    if(stones2 < sz(cc[1])) { 
     (ways[stones1][stones2 + 1][stones3][1] += ways[stones1][stones2][stones3][0] + 
                                                ways[stones1][stones2][stones3][2]) %= MOD;     
    }
    if(stones3 < sz(cc[2])) { 
     (ways[stones1][stones2][stones3 + 1][2] += ways[stones1][stones2][stones3][1] + 
                                                ways[stones1][stones2][stones3][0]) %= MOD;     
    }
   } 
  } 
 } 
 int64_t ret = 0;
 for(int c1 = 0; c1 <= sz(cc[0]); c1++) { 
  for(int c2 = 0; c2 <= sz(cc[1]); c2++) { 
   for(int c3 = 0; c3 <= sz(cc[2]); c3++) { 
    for(int currT = 0; currT <= T; currT++) { 
     (ret += fact[c1] % MOD * fact[c2] % MOD * fact[c3] % MOD * 
            (ways[c1][c2][c3][0] + ways[c1][c2][c3][1] + ways[c1][c2][c3][2]) % MOD * 
            dp[c1][currT] % MOD * dyn[c2][c3][T - currT] % MOD) %= MOD; 
    } 
   } 
  } 
 } 
 cout << ret << '\n'; 
 return 0;
}