#include "bits/stdc++.h"
using namespace std; 
#define lint long long
#define MAXN 502 
char g[MAXN][MAXN]; 
lint dp[MAXN][MAXN]; 
lint ndp[MAXN][MAXN]; 
const int mod = 1e9 + 7;
int n; 
signed main(void)
{
     scanf("%d", &n);
     for(int i = 0; i < n; i++)
     {
        for(int j = 0; j < n; j++)
        {
             scanf(" %c", &g[i][j]); 
        }
     }
     for(int i = 0; i < n; i++)
     {
          dp[i][i] = 1;
     }
     for(int len = n - 1; len > 0; len--)
     {
         for(int rowa = 0; rowa < n; rowa++)
         {
             int cola = len - rowa - 1;
             if(cola < 0) continue; 
             for(int rowb = 0; rowb < n; rowb++)
             { 
                int colb = 2 * n - len - rowb - 1;
                if(colb >= n) continue;  
                if(g[rowa][cola] == g[rowb][colb])
                {
                    ndp[rowa][rowb] += dp[rowa][rowb];     
                    if(rowa + 1 < n) ndp[rowa][rowb] += dp[rowa + 1][rowb]; 
                    if(rowb > 0) ndp[rowa][rowb] += dp[rowa][rowb - 1]; 
                    if(rowa + 1 < n && rowb > 0) ndp[rowa][rowb] += dp[rowa + 1][rowb - 1]; 
                    ndp[rowa][rowb] %= mod; 
                }
             }
         }
         for(int i = 0; i < n; i++)
         {
             for(int j = 0; j < n; j++)
             {
                 dp[i][j] = ndp[i][j];
                 ndp[i][j] = 0; 
             }
         }
     }
     printf("%lld\n", dp[0][n - 1]); 
     return 0; 
}
// given a grid find total number of palindromic paths
/*
     Let DP[i][j][k] = {number of palindromic paths of length 2 * k + 1 start at i and end at j (vertical)}
*/ 