#include "bits/stdc++.h"

using namespace std;

const int MOD = 1e9 + 7; 

#define sz(x) int(x.size())

int64_t Comb(int a, int b) { 
 #define MAX__COMB_A 302
 #define MAX__COMB_B 302
 static int64_t comb[MAX__COMB_A + 1][MAX__COMB_B + 1]; 
 if(a < b || b < 0) return 0; 
 if(b == 0) return 1; 
 int64_t &ret = comb[a][b]; 
 if(ret > 0) return ret; 
 ret = (Comb(a - 1, b) + Comb(a - 1, b - 1)) % MOD; 
 return ret; 
}

int64_t fact(int n) { 
  static int64_t dp[302]; 
  if(n == 0) return 1; 
  int64_t &ret = dp[n]; 
  if(ret > 0) return ret; 
  return 1LL * n % MOD * fact(n - 1) % MOD; 
}

int main(void) { 
 ios_base::sync_with_stdio(false);
 cin.tie(0); 
 cout.tie(0); 
 int N; 
 cin >> N; 
 vector<int>a(N), vis(N); 
 for(int i = 0; i < N; i++) { 
  cin >> a[i]; 
 }
 vector<vector<int>>group; 
 for(int i = 0; i < N; i++) { 
  if(vis[i]) continue;
  vis[i] = true; 
  vector<int>curr{i}; 
  for(int j = 0; j < N; j++) { 
   if(i == j) continue;
   int n = (int) sqrt(1. * a[i] * a[j]); 
   if(1LL * n * n == 1LL * a[i] * a[j]) { 
    curr.push_back(j); 
    vis[j] = true; 
   }
  }
  group.push_back(curr);
 }
 vector<vector<int64_t>>dp(sz(group), vector<int64_t>(N + 1)); 
 dp[0][sz(group[0]) - 1] = fact(sz(group[0])); 
 for(int pos = 1, size = sz(group[0]); pos < sz(group); pos++) { 
  for(int badInv = 0; badInv < size; badInv++) { 
   for(int choose = 1; choose <= min(size + 1, sz(group[pos])); choose++)
   for(int pickInv = 0; pickInv <= min(choose, badInv); pickInv++) { 
    int newBad = badInv - pickInv + sz(group[pos]) - choose;
    dp[pos][newBad] += fact(sz(group[pos])) % MOD * dp[pos - 1][badInv] % MOD * Comb(sz(group[pos]) - 1, choose - 1) % MOD * 
                       Comb(badInv, pickInv) % MOD * Comb(size + 1 - badInv, choose - pickInv) % MOD; 
    dp[pos][newBad] %= MOD;  
   }
  }
  size += sz(group[pos]);  
 }
 cout << dp[sz(group) - 1][0] << '\n'; 
 return 0; 
}