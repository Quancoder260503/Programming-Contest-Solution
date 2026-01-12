#include "bits/stdc++.h"

using namespace std; 

const int MOD = 1e9 + 7; 
const int maxn = 22; 

#define ll long long 
#define sz(x) int(x.size())

int n, k;
vector<int>a; 
ll dp[maxn][maxn][maxn][maxn << 1]; // dp[current_pos][current_open][num_created][valued_of_the_prev]
ll comb[maxn][maxn]; 


ll memo(int pos, int num_open, int total, int prev_val) { 
 if(pos == n) return total == k && num_open == 0; 
 ll &ret = dp[pos][num_open][total][prev_val];  
 if(ret != -1) return ret; 
 ret = 0; 
 for(int num_extra = 0; num_extra + total <= k; num_extra++) {  
  for(int num_closed = 0; num_closed <= num_open + num_extra; num_closed++) { 
   if(a[pos] + num_open + num_extra > prev_val) { 
    ll ways = memo(pos + 1, num_open - num_closed + num_extra, total + num_extra, a[pos] + num_open + num_extra);
    ways = ways * comb[num_open + num_extra][num_closed] % MOD; 
    ways = ways * comb[k - total][num_extra] % MOD; 
    ret += ways; 
    ret %= MOD;  
   } 
  }
 }
 return ret; 
}

int main(void) {
 cin >> n >> k;  
 comb[0][0] = 1; 
 a.resize(n); 
 for(int i = 1; i < maxn; i++) { 
  for(int j = 0; j <= i; j++) { 
   comb[i][j] = (comb[i - 1][j] + (j ? comb[i - 1][j - 1] : 0)) % MOD; 
  }
 }
 memset(dp, -1, sizeof dp); 
 for(int i = 0; i < n; i++) {  
  cin >> a[i]; 
 }
 cout << memo(0, 0, 0, 0) << '\n';  
 //rec(0, a); 
 return 0; 
}