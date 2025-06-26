#include "bits/stdc++.h"
using namespace std;
const int MAXN = (int)2e5 + 10;
vector<int> adj[MAXN];
vector<int> fadj[MAXN];
int in[MAXN], low[MAXN], fa[MAXN];
bool vis[MAXN];
int deg[MAXN];
vector<int> S;
int component;
vector<int> comp[MAXN];
int n, m;
int timer = 1;
char ans[MAXN];
int flip(int x)
{
    return x & 1 ? x + 1 : x - 1;
}
void dfs(int u)
{
    in[u] = low[u] = timer++;
    S.push_back(u);
    for (int i = 0; i < adj[u].size(); i++)
    {
        int v = adj[u][i];
        if (vis[v])
            continue;
        if (!in[v])
        {
            dfs(v);
            low[u] = min(low[u], low[v]);
        }
        else
            low[u] = min(low[u], in[v]);
    }
    if (in[u] == low[u])
    {
        component++;
        while (true)
        {
            int v = S.back();
            S.pop_back();
            fa[v] = component;
            comp[fa[v]].push_back(v);
            vis[v] = 1;
            if (u == v)
                break;
        }
    }
}
signed main(void)
{
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        char usign, vsign, wsign;
        int u, v, w;
        cin >> u >> usign >> v >> vsign >> w >> wsign;
        u = 2 * u - (usign == 'B');
        v = 2 * v - (vsign == 'B');
        w = 2 * w - (wsign == 'B'); 
        adj[flip(u)].push_back(v);
        adj[flip(u)].push_back(w); 
        adj[flip(v)].push_back(u);
        adj[flip(v)].push_back(w); 
        adj[flip(w)].push_back(u); 
        adj[flip(w)].push_back(v); 
    }
    for (int i = 1; i <= 2 * n; i++)
    {
        if (!vis[i])
        {
            dfs(i);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (fa[2 * i] == fa[2 * i - 1])
        {
            puts("-1");
            return 0;
        }
    }
    for (int i = 1; i <= 2 * n; i++)
    {
        for (int j = 0; j < adj[i].size(); j++)
        {
            int v = adj[i][j];
            if (fa[i] == fa[v])
                continue;
            fadj[fa[i]].push_back(fa[v]);
            deg[fa[v]]++;
        }
    }
    queue<int> q;
    vector<int> ord;
    for (int i = 1; i <= component; i++)
    {
        if (deg[i] == 0)
        {
            ord.push_back(i);
            q.push(i);
        }
    }
    memset(vis, 0, sizeof(vis));
    while (q.size())
    {
        int u = q.front();
        q.pop();
        for (int i = 0; i < fadj[u].size(); i++)
        {
            int v = fadj[u][i];
            deg[v]--;
            if (deg[v] == 0)
            {
                q.push(v);
                ord.push_back(v);
            }
        }
    }
    reverse(ord.begin(), ord.end());
    for (int i = 0; i < ord.size(); i++)
    {
        int u = ord[i];
        for (int j = 0; j < comp[u].size(); j++)
        {
            int v = comp[u][j];
            int w = (v + 1) / 2;
            if (!vis[w])
            {
                ans[w] = (v & 1 ? 'B' : 'R');
                vis[w] = 1;
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}