#include "bits/stdc++.h"
using namespace std;
const int MAXN = (int)1e5 + 10;
const int K = 23;
vector<int> adj[MAXN];
int up[K][MAXN];
int dep[MAXN];
void dfs(int u, int p)
{
    for(int i = 1; i < K; i++)
    {
         up[i][u] = up[i - 1][up[i - 1][u]]; 
    }
    for(int i = 0; i < adj[u].size(); i++)
    {
         int v = adj[u][i];
         if(v == p) continue; 
         dep[v] = dep[up[0][v] = u] + 1; 
         dfs(v, u); 
    }
    return;
}
int LCA(int u, int v)
{
    if (dep[u] < dep[v]) swap(u, v);
    int d = dep[u] - dep[v];
    for (int i = 0; i < K; i++)
    {
        if (d & (1 << i))
        {
            u = up[i][u];
        }
    }
    if (u == v)  return u;
    for (int i = K - 1; i >= 0; i--)
    {
        int tu = up[i][u], tv = up[i][v];
        if (tu != tv) u = tu, v = tv;
    }
    return up[0][u];
}
int dist(int u, int v)
{
    return dep[u] + dep[v] - 2 * dep[LCA(u, v)]; 
}
int p[MAXN];
int n; 
void solve()
{
     cin >> n; 
     for(int i = 1; i <= n; i++)
     {
        adj[i].clear(); 
     }
     for(int i = 1; i < n; i++)
     {
         int u, v; cin >> u >> v; 
         adj[u].push_back(v);
         adj[v].push_back(u); 
     }
     dfs(1, 0); 
     for(int i = 1; i <= n; i++)
     {
        cin >> p[i]; 
     }
     int good = 1; 
     for(int i = 1; i < n; i++)
     {
        good = good & (dist(p[i], p[i + 1]) <= 3); 
     }
     cout << good << '\n';
     return;
}
signed main(void)
{
    int t; cin >> t;
    while(t--)
    {
        solve(); 
    }
}