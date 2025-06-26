#include "bits/stdc++.h"
using namespace std; 
#define N 5001
const int mod = 1e9 + 7; 
long long dp[N][N]; 
int n,k;
signed main(){
     scanf("%d%d",&n,&k);
     for(int i = 1; i < n; i++){
        int u; scanf("%d",&u); 
     } 
     dp[1][1] = 1;
     for(int j = 1; j <= k; j++){
        for(int i = 1; i <= n; i++){
             if(i == 1 && j == 1) continue;
             dp[i][j] = 1ll * j % mod * dp[i - 1][j - 1] % mod + 1ll * (j - 1) % mod * dp[i - 1][j] % mod; 
             if(dp[i][j] < 0) dp[i][j] += mod;
        }
     }
     long long ans = dp[n][k];
     ans = ans % mod;
     printf("%lld\n",ans); 
}