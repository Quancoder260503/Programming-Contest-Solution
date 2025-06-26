#include "bits/stdc++.h"
using namespace std; 
#define MAXN (int) 6e4 + 10
#define M 70
int n, g;
int dp[M][MAXN]; 
int a[MAXN]; 
signed main(void)
{
    scanf("%d %d", &n, &g); 
    dp[0][0] = 1; 
    for(int i = 1; i <= n; i++)
    {
         scanf("%d", a + i); 
    }
    for(int i = 1; i <= n; i++)
    {
         for(int j = MAXN; j >= 0; j--)
         {
             for(int k = 1; k <= n; k++)
             {
                 if(j >= a[i])
                 {
                     dp[k][j] |= dp[k - 1][j - a[i]];
                 }
             }
         }
    }
    double ans = -1.0; 
    for(int i = 1; i <= n; i++)
    {
         for(int j = 0;  j <= MAXN; j++)
         {
             if(dp[i][j] && (j + 5 - g) <= 5 * i) 
             {
                 ans = max(ans, (double) (j + 10 - g) / (double)(i + 1)); 
             }
         }
    }
    if(ans < 0) 
    {
         puts("impossible"); 
    }
    else 
    {
        printf("%0.7lf\n",ans);
    }
    return 0;
}