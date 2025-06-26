#include "bits/stdc++.h"
using namespace std;
#define MAXN (int)2e6 + 10
int fa[MAXN];
int n;
int g[MAXN];
signed main(void)
{
    scanf("%d", &n);
    for (int i = 2; i <= n; i++)
    {
        scanf("%d", &fa[i]);
    }
    for (int i = n; i > 0; i--)
    {
        g[fa[i]] += (g[i] == 0);
    }
    for (int i = 2; i <= n; i++)
    {
        g[i] += (g[fa[i]] == (g[i] == 0));
    }
    for (int i = 1; i <= n; i++)
    {
        if (!g[i])
            printf("%d\n", i);
    }
    return 0;
}