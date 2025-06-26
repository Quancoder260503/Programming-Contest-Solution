#include "bits/stdc++.h"
using namespace std;
#define MAXN (int) 20
#define lint long long
vector<int> adj[MAXN];
int n, m;
lint dp[MAXN][1 << MAXN];
int lowbit(int mask)
{
    return mask & (-mask); 
}
signed main(void)
{
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        --u; --v; 
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 0; i < n; i++)
    {
        dp[i][(1 << i)] = 1;
    }
    lint ans = 0;
    for (int mask = 0; mask < (1 << n); mask++)
    {
        for (int i = 0; i < n; i++)
        {
            if (mask & (1 << i))
            {
                for (int j = 0; j < adj[i].size(); j++)
                {
                    int v = adj[i][j];
                    if( (1 << v) < lowbit(mask)) continue;
                    if( (mask & (1 << v)) && ((1 << v) == lowbit(mask)))
                    {
                         ans += dp[i][mask]; 
                    }
                    else 
                    {
                        dp[v][mask + (1 << v)] += dp[i][mask];  
                    }
                }
            }
        }
    }
    ans = (ans - m) / 2;
    printf("%lld\n", ans);
    return 0; 
}