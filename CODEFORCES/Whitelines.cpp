#include "bits/stdc++.h"
using namespace std;
#define MAXN (int)2e3 + 10
char g[MAXN][MAXN];
int rows[MAXN][MAXN];
int cols[MAXN][MAXN];
int grow[MAXN];
int gcol[MAXN];
int dp[MAXN][MAXN];
int n, k;
int rrange(int row, int L, int R)
{
     R = min(R, n); 
     return rows[row][R] -  rows[row][L - 1]; 
}
int crange(int col, int L, int R)
{
     R = min(R, n); 
     return cols[R][col] -  cols[L - 1][col];
}
signed main(void)
{
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            scanf(" %c", &g[i][j]);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        int rnow, cnow;
        rnow = cnow = 1;
        for (int j = 1; j <= n; j++)
        {
            rows[i][j] = rows[i][j - 1]  + (g[i][j] == 'B');
            cols[i][j] = cols[i - 1][j]  + (g[i][j] == 'B');
            rnow = rnow & (g[i][j] == 'W');
            cnow = cnow & (g[j][i] == 'W');
        }
        grow[i] = grow[i - 1] +  rnow;
        gcol[i] = gcol[i - 1] +  cnow;
    } 
    for (int i = 1; i <= n - k + 1; i++)
    {
        int opt = 0;
        for (int j = 1; j <= k; j++)
        {
            opt += ( crange(j, i, i + k - 1) == cols[n][j]); 
        }
        dp[i][1] += opt + gcol[n] - gcol[k];
        for (int j = k + 1; j <= n; j++)
        {
            opt += (crange(j, i, i + k - 1) == cols[n][j]);
            opt -= (crange(j - k, i, i + k - 1) == cols[n][j - k]);
            dp[i][j - k + 1] += opt + gcol[n] - gcol[j] + gcol[j - k]; 
        }
    }
    for (int i = 1; i <= n - k + 1; i++)
    {
        int opt = 0;
        for (int j = 1; j <= k; j++)
        {
            opt += (rrange(j, i, i + k - 1) == rows[j][n]);
        }
        dp[1][i] += opt + grow[n] - grow[k]; 
        for (int j = k + 1; j <= n; j++)
        {
            opt += (rrange(j, i, i + k - 1) == rows[j][n]);
            opt -= (rrange(j - k, i, i + k - 1) == rows[j - k][n]);
            dp[j - k + 1][i] += opt + grow[n] - grow[j] + grow[j - k];
        }
    }
    int ans = 0;
    for(int i = 1; i <= n; i++)
    {
         for(int j = 1; j <= n; j++)
         {
             ans = max(ans, dp[i][j]); 
         }
    }
    printf("%d\n", ans); 
    return 0;
}