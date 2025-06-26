#include "bits/stdc++.h"
using namespace std;
#define N 1000005
vector<int> adj[N];
int n;
int dep[N];
int vis[N];
void dfs(int u, int p)
{
    for (int i = 0; i < adj[u].size(); i++)
    {
        int v = adj[u][i];
        if (v == p)
            continue;
        dep[v] = dep[u] + 1;
        dfs(v, u);
    }
    return;
}
void dfs_t(int u, int p)
{
    if (!vis[u])
        printf("%d ", u);
    for (int i = 0; i < adj[u].size(); i++)
    {
        int v = adj[u][i];
        if (v == p)
            continue;
        dfs_t(v, u);
    }
    return;
}
signed main(void)
{
    scanf("%d", &n);
    for (int i = 1; i < n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 0);
    int curr = 1;
    for (int i = 1; i <= n; i++)
    {
        if (dep[i] > dep[curr])
        {
            curr = i;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        dep[i] = 0;
    }
    dfs(curr, 0);
    int d = 0;
    for (int i = 1; i <= n; i++)
    {
        d = max(d, dep[i]);
    }
    if (d < 3)
    {
        puts("NO");
        return 0;
    }
    int st = 0;
    int nxt = 0;
    for (int i = 1; i <= n; i++)
    {
        if (adj[i].size() <= 1)
            continue;
        for (int j = 0; j < adj[i].size(); j++)
        {
            int u = adj[i][j];
            if (adj[u].size() > 1)
            {
                st = i;
                nxt = u;
            }
        }
    }
    puts("YES");
    for (int i = 0; i < adj[st].size(); i++)
    {
        int u = adj[st][i];
        if (u != nxt)
        {
            nxt = u;
            break;
        }
    }
    vis[st] = vis[nxt] = 1;
    printf("%d %d ", st, nxt);
    dfs_t(nxt, -1);
    return 0;
}