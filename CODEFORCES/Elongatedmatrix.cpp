#include "bits/stdc++.h"
using namespace std;
#define MAXN (int)17
#define mp make_pair
#define pii pair<int, int>
#define M (int)1e4 + 10
#define INF (int)1e9
int n, m;
int dp[MAXN][(1 << MAXN)];
int mat[MAXN][M];
int dist[MAXN][MAXN];
int dist2[MAXN][MAXN];
signed main(void)
{
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &mat[i][j]);
        }
    }
    memset(dist, 63, sizeof(dist));
    memset(dist2, 63, sizeof(dist2));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < m; k++)
            {
                dist[i][j] = min(dist[i][j], abs(mat[i][k] - mat[j][k]));
            }
            for (int k = 0; k < m - 1; k++)
            {
                /* i to j */
                dist2[i][j] = min(dist2[i][j], abs(mat[i][k + 1] - mat[j][k]));
            }
        }
    }
    long long ans = 0;
    if (n == 1)
    {
        ans = LLONG_MAX;
        for (int i = 0; i < m - 1; i++)
        {
            ans = min(ans, 1LL * abs(mat[0][i] - mat[0][i + 1]));
        }
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            memset(dp, -63, sizeof(dp));
            for (int j = 0; j < n; j++)
            {
                if (j == i) continue;
                dp[j][(1 << j)] = dist[i][j];
                if(n == 2)
                {
                     ans = max(ans, 1LL * min(dist[i][j], dist2[i][j])); 
                }
            }
            for (int mask = 0; mask < (1 << n); mask++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (!(mask & (1 << j)) || i == j)
                        continue;
                    for (int k = 0; k < n; k++)
                    {
                        if (mask & (1 << k) || k == i || dp[j][mask] > INF)
                            continue;
                        int fmask = mask xor (1 << k);
                        dp[k][fmask] = max(dp[k][fmask], min(dp[j][mask], dist[j][k]));
                        if (__builtin_popcount(fmask) == n - 1 && dp[k][mask] <= INF)
                        {
                            ans = max(ans, 1LL * min(dp[k][fmask], dist2[i][k]));
                        }
                    }
                }
            }
        }
    }
    printf("%lld\n", ans);
    return 0;
}
/*
    Maximum hamiltonian path
*/