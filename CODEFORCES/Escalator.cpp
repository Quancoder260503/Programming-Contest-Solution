#include "bits/stdc++.h"
using namespace std;
#define MAXN 5000
int n, t;
double p;
double dp[MAXN][MAXN];
signed main(void)
{
    scanf("%d%lf%d",&n,&p,&t); 
    long double ans = 0.0; 
    dp[0][0] = 1.0; 
    for(int i = 1; i <= t; i++)
    { 
        dp[i][0] = dp[i - 1][0] * (1.0 - p); 
        for(int j = 1; j <= n; j++)
        {
             dp[i][j] = dp[i - 1][j] * (j == n ? 1.0 : (1.0 - p))  + dp[i - 1][j - 1] * p; 
        }
    }
    for(int i = 1; i <= n; i++)
    {
         ans += dp[t][i] * i; 
    }
    printf("%0.10llf\n",ans); 
    return 0;
}