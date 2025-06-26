#include "bits/stdc++.h"

using namespace std; 

const int LOG = 20; 
const int maxf = 1 << LOG; 

int64_t dp[maxf], d[maxf]; 

int main(void) { 
 freopen("evencomb.inp", "r", stdin);
 freopen("evencomb.out", "w", stdout); 
 int N; 
 cin >> N; 
 for(int i = 0, x; i < N; i++) { 
  cin >> x; 
  d[x]++; 
 }
 for(int i = 0; i < (1 << LOG); i++) { 
  dp[i] = d[i];   
 }
 for(int i = 0; i < LOG; i++) { 
  for(int mask = 0; mask < (1 << LOG); mask++) { 
   if(mask & (1 << i)) { 
    dp[mask] += dp[mask ^ (1 << i)]; 
   }
  }
 }
 int64_t ret = 0; 
 for(int i = 0; i < (1 << LOG); i++) { 
  ret += 1LL * d[i] * (d[i] - 1) + 1LL * d[i] * (dp[i] - d[i]) * 2; 
 }
 ret = 1LL * N * (N - 1) - ret; 
 ret = ret / 2; 
 cout << ret; 
 return 0; 
}