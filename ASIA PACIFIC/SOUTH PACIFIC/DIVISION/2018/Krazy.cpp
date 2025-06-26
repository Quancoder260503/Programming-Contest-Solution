#include "bits/stdc++.h"
using namespace std;
const int MAXN = (int)2e5 + 10;
vector<int> adj[MAXN];
int n, m, k;
int fa[MAXN];
int vis[MAXN];
int find(int u)
{
    return u == fa[u] ? u : fa[u] = find(fa[u]);
}
void dfs(int u)
{
    vis[u] = 1;
    for (int i = 0; i < adj[u].size(); i++)
    {
        int v = adj[u][i];
        if (vis[v]) continue;
        dfs(v);
    }
    return;
}
signed main(void)
{
    cin >> n >> m >> k;
    iota(fa + 1, fa + n + 1, 1);
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        if (find(u) != find(v))
        {
            fa[find(u)] = find(v);
        }
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 1; i <= k; i++)
    {
        int u, v;
        cin >> u >> v;
        if (find(u) != find(v))
        {
            fa[find(u)] = find(v);
        }
        adj[u].push_back(v);
    }
    dfs(1);
    for (int i = 1; i <= n; i++)
    {
        if(find(1) == find(i)) 
        {
            if(vis[i])
            {
                puts("No Ticket"); 
            }
            else 
            {
                puts("Ticket"); 
            }
        }
        else 
        {
            puts("Impossible"); 
        }
    }
    return 0;
}