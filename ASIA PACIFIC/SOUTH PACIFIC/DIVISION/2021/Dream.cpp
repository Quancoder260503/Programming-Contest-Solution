#include "bits/stdc++.h"
using namespace std;
const int MAXN = (int)2e5 + 10;
vector<pair<int, int>> adj[MAXN];
int dep[MAXN];
bool vis[MAXN];
void dfs(int u)
{
    vis[u] = 1;
    for (int i = 0; i < adj[u].size(); i++)
    {
        int v = adj[u][i].first;
        int cost = adj[u][i].second;
        if (vis[v])
        {
            if (dep[v] != dep[u] + cost)
            {
                puts("wake up");
                exit(0);
            }
        }
        else
        {
            dep[v] = dep[u] + cost;
            dfs(v);
        }
    }
}
int n, m;
signed main(void)
{
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }
    for(int i = 1; i <= n; i++)
    {
        fill(vis + 1, vis + n + 1, 0); 
        dfs(i); 
    }
    puts("we live in a society"); 
    return 0;
}
