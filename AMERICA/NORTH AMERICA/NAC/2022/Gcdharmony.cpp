#include "bits/stdc++.h"
#include <algorithm>
using namespace std;
#define N 1000005
#define mp make_pair
#define MAXN 10005
#define inf 1000000000000
#define M 5001
int n;
vector<int> adj[N];
int vis[N];
int A[N];
vector<int> divi[N];
long long dp[M][MAXN];
int gcd(int a, int b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}
void dfs(int u, int p)
{
    for (int k = 0; k < adj[u].size(); k++)
    {
        int v = adj[u][k];
        if (v == p)
            continue;
        dfs(v, u);
        for (int i = 2; i < MAXN; i++)
        {
            long long curr = inf;
            for (int j = 0; j < divi[i].size(); j++)
            {
                curr = min(curr, dp[v][divi[i][j]]);
            }
            dp[u][i] += curr;
        }
    }
    for (int i = 2; i < MAXN; i++)
    {
        if (i == A[u])
            continue;
        dp[u][i] += i;
    }
    for (int i = 2; i < MAXN; i++)
    {
        for (int j = 0; j < divi[i].size(); j++)
        {
            dp[u][divi[i][j]] = min(dp[u][divi[i][j]], dp[u][i]);
        }
    }
    return;
}
void sieve()
{
    vis[1] = 1;
    for (int i = 1; i < MAXN; i++)
    {
        if (vis[i])
            continue;
        for (int j = i; j < MAXN; j += i)
        {
            vis[j] = 1;
            divi[j].push_back(i);
        }
    }
    return;
}
signed main(void)
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &A[i]);
    }
    sieve();
    for (int i = 1; i < n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int root = 1;
    dfs(root, 0);
    long long ans = inf;
    for (int i = 2; i < MAXN; i++)
    {
        ans = min(ans, dp[root][i]);
    }
    printf("%lld\n", ans);
    return 0;
}