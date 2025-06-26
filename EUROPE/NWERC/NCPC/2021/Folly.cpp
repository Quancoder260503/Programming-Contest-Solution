#include "bits/stdc++.h"
using namespace std; 
#define MAXN 1000
double dp[MAXN][MAXN]; 
int n, k; 
double p;
double res[MAXN]; 
signed main(void)
{
    scanf("%d %d %lf", &n, &k, &p); 
    int fmask = (1 << n); 
    for(int i = 0; i < fmask; i++)
    {
         if(__builtin_popcount(i) >= k)
         {
             dp[i][i] = 1; 
             dp[i][fmask] = 0; 
         }
         else 
         {
             dp[i][i] = 1; 
             dp[i][fmask] = -1; 
             dp[i][((i << 1) + 1) & ~fmask] -= p; 
             dp[i][(i << 1) & ~fmask] -= (1.0 - p); 
         }
    }
    for(int i = 0; i < fmask - 1; i++)
    {
         for(int j = i + 1; j < fmask; j++)
         {
              assert(dp[i][i] != 0); 
              double ratio = dp[j][i] / dp[i][i];
              for(int k = 0; k <= fmask; k++)
              {
                dp[j][k] = dp[j][k] - ratio * dp[i][k]; 
              }
         }
    }
    res[fmask - 1] = dp[fmask - 1][fmask] / dp[fmask - 1][fmask - 1];  
    for(int i = fmask - 2; i >= 0; i--)
    {
         res[i] = dp[i][fmask];
         for(int j = i + 1; j < fmask; j++)
         {
             res[i] = res[i] - res[j] * dp[i][j];
         }
         res[i] = res[i] / dp[i][i]; 
    }
    printf("%.7lf\n", -res[0]); 
    return 0; 
}