#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int LOG = 22; 
const int MAXN = (1 << LOG) + 10; 

int a[MAXN], bit[MAXN], dp[MAXN]; 

int main(void) { 
 int N; 
 cin >> N; 
 vector<int>a(N);
 for(int i = 0; i < N; i++) { 
  cin >> a[i]; 
  int msb = 31 - __builtin_clz(a[i]); 
  int mask = ((1 << (msb + 1)) - 1) ^ a[i]; 
  bit[mask] |= (1 << msb); 
 }
 for(int mask = MAXN - 1; mask >= 0; mask--) { 
  for(int i = 0; i < LOG; i++) { 
   if(mask >> i & 1) continue; 
   bit[mask] |= bit[mask ^ (1 << i)]; 
  }
 }
 for(int mask = 0; mask < MAXN; mask++) { 
  for(int j = 0; j < LOG; j++) { 
   if(mask >> j & 1) continue;
   if(bit[mask] >> j & 1) { 
    dp[mask | (1 << j)] = max(dp[mask | (1 << j)], dp[mask] + 1); 
   }
  }
 }
 cout << *max_element(dp, dp + MAXN) << '\n'; 
 return 0; 
}