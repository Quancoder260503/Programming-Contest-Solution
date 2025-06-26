#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1000001;
const int M = 18;
long long n,L,m; 
long long A[N]; 
bool vis[N]; 
long long dp[N]; 
long long g[M][M]; 
long long cost[N];
signed main(){
     scanf("%d",&n);
     for(int i = 0; i < n; i++){
          for(int j = 0; j < n; j++){
               scanf("%lld",&g[i][j]); 
          }
     }
     for(int mask = 0; mask < (1 << n); mask++){
           for(int i = 0; i < n; i++){
                 for(int j = i + 1; j < n; j++){
                      if((1 << i) & mask && (1 << j) & mask){
                           cost[mask] += g[i][j]; 
                      }
                 }
           }
     }
     for(int mask = 0; mask < (1 << n); mask++){
            int submask = ((1 << n) - 1) xor mask; 
            for(int j = submask; j; j = (j - 1) & submask){
                  dp[mask | j] = max(dp[mask | j], cost[j] + dp[mask]); 
            }
     }
     printf("%lld\n", dp[(1 << n) - 1]); 
     return 0; 
}