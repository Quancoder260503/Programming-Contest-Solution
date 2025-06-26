#include "bits/stdc++.h"
using namespace std;
#define MAXN (int)510
#define pii pair<int, int>
#define mp make_pair
int dp[MAXN][MAXN];
int arr[MAXN];
int n;
signed main(void)
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }
    memset(dp, 63, sizeof(dp));
    for (int i = 1; i <= n; i++)
    {
        dp[i][i] = 1;
        dp[i][i + 1] = (arr[i] == arr[i + 1] ? 1 : 2);
    }
    for (int len = 3; len <= n; len++)
    {
        for (int i = 1; i + len - 1 <= n; i++)
        {
            int j = i + len - 1;
            for (int k = i; k < j; k++)
            {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
            }
            if (arr[i] == arr[j])
            {
                dp[i][j] = min(dp[i][j], dp[i + 1][j - 1]);
            }
        }
    }
    printf("%d\n", dp[1][n]);
    return 0;
}
/*
 */