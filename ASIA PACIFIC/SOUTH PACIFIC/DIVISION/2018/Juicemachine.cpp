#include "bits/stdc++.h"
using namespace std;
const int MAXN = (int)2e5 + 10;
const int M = 50; 
#define lint long long
lint a[MAXN], b[MAXN];
lint dp[M][MAXN];
lint k;
int n;
signed main(void)
{
    cin >> k >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i] >> b[i];
    }
    for (int i = 1; i <= n; i++)
    {
        k = k * b[i];
        for (int j = 1; j <= n; j++)
        {
            if (i == j) continue;
            a[i] = 1LL * a[i] * b[j];
        }
    }
    lint gc = k;
    for (int i = 1; i <= n; i++)
    {
        gc = __gcd(gc, a[i]);
    }
    k = k / gc;
    for (int i = 1; i <= n; i++)
    {
        a[i] = a[i] / gc;
    }
    for (int i = 0; i < M; i++)
    {
        fill(dp[i], dp[i] + MAXN, (lint)1e9);
    }
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= k; j++)
        {
            dp[i][j] = dp[i - 1][j];
            for (int c = 1; c * a[i] <= j; c++)
            {
                dp[i][j] = min(dp[i][j], dp[i - 1][j - c * a[i]] + c);
            }
        }
    }
    cout << (dp[n][k] == (lint)1e9 ? -1 : dp[n][k]) << endl;
    return 0;
}