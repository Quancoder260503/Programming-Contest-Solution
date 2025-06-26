#include "bits/stdc++.h"
#include <stdio.h>
#include <algorithm>
using namespace std;
#define N 1500000
#define C 5
typedef long double ldb;
const int mod = 1e9 + 7; 
long long finv[N];
long long fac[N];
long long inv[N]; 
int n,k,m;  
long long dp[N][(1 << C)]; 
vector<int>adj[N]; 
int col[N]; 
signed main(void){
     scanf("%d%d%d",&n,&m,&k);
     for(int i = 1; i <= n; i++){
            scanf("%d",&col[i]);
            --col[i]; 
            dp[i][(1 << col[i])] = 1;
     }
     for(int i = 0; i < m; i++){
          int u,v; scanf("%d%d",&u,&v);
          adj[u].push_back(v);
          adj[v].push_back(u);
     }
     long long ans = 0;
     for(int  mask = 0; mask < (1 << k); mask++){
           if(mask == (mask & -mask)) continue; 
           for(int i = 1; i <= n; i++){ 
                if((1 << col[i]) & mask){
                   for(int j = 0; j < adj[i].size(); j++){
                       int v = adj[i][j];
                       dp[i][mask] += dp[v][mask xor (1 << col[i])];
                   }
                   ans += dp[i][mask];  
                }
           }
     }
     printf("%lld\n",ans); 
     return 0; 
}