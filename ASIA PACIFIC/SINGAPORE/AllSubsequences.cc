#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int MOD = 998244353; 

struct Fenwick { 
 int n; 
 vector<int>bit; 
 Fenwick(int _n) : n(_n) { 
  bit.resize(n); 
 }
 void upd(int p, int v) { 
  for(p++; p < n; p += p & (-p)) { 
   bit[p] += v; 
   bit[p] %= MOD;  
  }
 }
 int64_t query(int p) {
  int64_t ret = 0;  
  for(p++; p > 0; p -= p & (-p)) { 
   ret += bit[p]; 
   ret %= MOD; 
  }
  return ret; 
 }
 int64_t query(int L, int R) { 
  return (query(R) - query(L - 1) + MOD) % MOD; 
 }
}; 

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int n; 
 cin >> n; 
 vector<int>a(n + 1); 
 vector<int>coord; 
 for(int i = 1; i <= n; i++) { 
  cin >> a[i]; 
  coord.push_back(a[i]); 
 }
 sort(coord.begin(), coord.end()); 
 coord.erase(unique(coord.begin(), coord.end()), coord.end()); 
 Fenwick fenw1(n + 7), fenw2(n + 7); 
 vector<int64_t>dp(n + 1, 0); 
 int64_t ret = 0; 
 for(int i = 1; i <= n; i++) { 
  int x = lower_bound(coord.begin(), coord.end(), a[i]) - coord.begin() + 1; 
  if(i > 1) { 
   (dp[i] += fenw2.query(x + 1, n) - fenw1.query(x + 1, n) % MOD * a[i] % MOD + MOD) %= MOD; 
   (dp[i] += fenw1.query(x - 1) % MOD * a[i] % MOD - fenw2.query(x - 1)       + MOD) %= MOD; 
   (ret += dp[i]) %= MOD; 
   fenw1.upd(x, dp[i] + 1); 
   fenw2.upd(x, 1LL * (dp[i] + 1) % MOD * a[i] % MOD); 
  } else { 
    fenw1.upd(x, 1); 
    fenw2.upd(x, a[i]);  
  }
 }
 cout << ret << '\n'; 
 return 0; 
}