#include "bits/stdc++.h"
using namespace std;
#define MAXN (int) 510
int n, k;
bitset<MAXN> dp[MAXN][MAXN];
int arr[MAXN]; 
signed main(void)
{
    scanf("%d %d", &n, &k); 
    for(int i = 1; i <= n; i++)
    {
       scanf("%d", &arr[i]); 
    }
    dp[0][0][0] = 1; 
    for(int i = 1; i <= n; i++)
    {
        for(int j = 0; j <= k; j++)
        {
             dp[i][j] |= dp[i - 1][j]; 
             if(j >= arr[i])
             {
                 
                 dp[i][j] |= (dp[i - 1][j - arr[i]] << arr[i]); 
                 dp[i][j] |= dp[i - 1][j - arr[i]]; 
             }
        }
    }
    int ans = 0; 
    for(int i = 0; i < MAXN; i++)
    {
        ans += (dp[n][k][i]); 
    }
    printf("%d\n", ans);
    for(int i = 0; i < MAXN; i++)
    {
         if(dp[n][k][i])
         {
             printf("%d ", i); 
         }
    }
    printf("\n");
    return 0;
}
/*
  Let dp[i][j] be the bitset representation for the constraint :
  how many distinc value can we made using the first ith items with
  sum exactly j.
*/