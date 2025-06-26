#include "bits/stdc++.h"
using namespace std;
#define lint long long
#define MAXN 105
lint dp[MAXN][MAXN];
lint C[MAXN][MAXN]; 
lint n, m;
int k;
lint f(lint val, int bit, int j)
{
    if (bit < 0 || j < 0)
        return 0;
    if (bit < j)
        return 0;
    if (dp[bit][j] != -1)
        return dp[bit][j];
    if (val & (1LL << bit))
    {
        return dp[bit][j] = C[bit][j] + f(val, bit - 1, j - 1);
    }
    else
    {
        return dp[bit][j] = f(val, bit - 1, j);
    }
}
int cntbit(lint x)
{
    return x == 0 ? 0 : cntbit(x / 2) + (x & 1);
}
bool good(lint n)
{
    memset(dp, -1, sizeof(dp));
    lint upper = f(2 * n, 60, k) + (cntbit(2 * n) == k);
    memset(dp, -1, sizeof(dp));
    lint lower = f(n, 60, k) + (cntbit(n) == k); 
    return (upper - lower >= m);
}
signed main(void)
{
    cin >> m >> k;
    C[0][0] = 1;
    for(int i = 1; i < MAXN; i++)
    {
        for(int j = 0; j <= i; j++)
        {
            C[i][j] = C[i - 1][j] + (j > 0 ? C[i - 1][j - 1] : j); 
        }
    }
    lint lo = 1;
    lint hi = (lint)1e18;
    while (lo < hi)
    {
        lint mid = (hi - lo) / 2 + lo;
        if (good(mid))
        {
            hi = mid;
        }
        else
        {
            lo = mid + 1;
        }
    }
    cout << lo << '\n'; 
    return 0;
}