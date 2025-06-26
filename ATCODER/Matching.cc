#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz = 4e5 + 1;
const int N = 1e6 + 50000;
const int mod = 1e9 + 7;
long long n,m,k,q,r;
int res;
int g[22][22];
long long dp[1 << 23];
int main(){
     scanf("%d",&n); 
     for(int i = 0; i < n; i++){ 
          for(int j = 0; j < n; j++){
              scanf("%d",&g[i][j]); 
          }
     }
     dp[0] = 1;
     for(int mask = 0; mask < (1 << n); mask++){
          int x = __builtin_popcount(mask); 
          for(int i = 0; i < n; i++){
                if(!g[x][i] or mask & (1 << i)) continue; 
                dp[mask | (1 << i)] = (dp[mask | (1 << i)] + mod + dp[mask]) % mod;
                dp[mask] %= mod; 
          }
     }
     printf("%d \n",dp[(1 << n) - 1]);
}