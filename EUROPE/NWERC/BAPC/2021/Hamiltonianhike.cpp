#include "bits/stdc++.h"
using namespace std;
const int MAXN = (int)2e5 + 10;
bool vis[MAXN];
int dep[MAXN];
int ans[MAXN];
vector<int> adj[MAXN];
int timer = 1;
int n, m;
void dfs(int u)
{
    if (! (dep[u] & 1))
    {
        ans[timer++] = u;
    }
    vis[u] = 1;
    for (int i = 0; i < adj[u].size(); i++)
    {
        int v = adj[u][i];
        if (vis[v])
            continue;
        dep[v] = dep[u] + 1;
        dfs(v);
    }
    if (dep[u] & 1)
    {
        ans[timer++] = u;
    }
    return;
}
signed main(void)
{
    cin >> n >> m; 
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1); 
    for(int i = 1; i <= n; i++)
    {
        cout << ans[i] << " "; 
    }
    cout << '\n'; 
    return 0;
}