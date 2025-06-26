#include "bits/stdc++.h"
using namespace std;
#pragma GCC target("popcnt")
#define MAXN (int)1e5
#define M 52
bitset<MAXN> dp[M];
int n, m;
signed main(void)
{
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        int len;
        scanf("%d", &len);
        for (int j = 0; j < len; j++)
        {
            int x;
            scanf("%d", &x);
            dp[i][x] = 1;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if ((dp[i] & dp[j]).count() == 0)
            {
                puts("impossible");
                return 0;
            }
        }
    }
    puts("possible");
    return 0;
}