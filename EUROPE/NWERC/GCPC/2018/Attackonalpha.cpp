#include "bits/stdc++.h"
using namespace std;
#define M 1004
#define MAXN (int)1e6 + 10
#define MASK 22
int n, m, q;
string s[M];
int fa[MAXN];
vector<int> adj[MAXN];
int up[MASK][MAXN];
int dep[MAXN];
int comp[MAXN];
int hsh(int i, int j)
{
    return (i - 1) * m + j;
}
int find(int u)
{
    return u == fa[u] ? u : fa[u] = find(fa[u]);
}
void dfs(int u, int p)
{
    for (int i = 1; i < MASK; i++)
    {
        up[i][u] = up[i - 1][up[i - 1][u]];
    }
    for (int i = 0; i < (int)adj[u].size(); i++)
    {
        int v = adj[u][i];
        if (v == p)
            continue;
        dep[v] = dep[up[0][v] = u] + 1;
        dfs(v, u);
    }
}
int lca(int u, int v)
{
    if (dep[u] < dep[v])
        swap(u, v);
    int dist = dep[u] - dep[v];
    for (int i = 0; i < MASK; i++)
    {
        if (dist & (1 << i))
            u = up[i][u];
    }
    if (u == v)
        return u;
    for (int i = MASK - 1; i >= 0; i--)
    {
        int tu = up[i][u];
        int tv = up[i][v];
        if (tu != tv)
        {
            u = tu;
            v = tv;
        }
    }
    return up[0][u];
}
signed main(void)
{
    scanf("%d%d",&n,&m); 
    for (int i = 1; i <= n * m; i++)
    {
        comp[i] += 1;
        fa[i] = i;
    }
    getchar();
    for (int i = 0; i < n + 1; i++)
    {
        getline(cin,s[i]); 
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < 2 * m; j++)
        {
            if ((j & 1))
            {
                int tx = i;
                int ty = (j + 1) / 2;
                if (s[i][j] == ' ')
                {
                    int u = hsh(tx, ty);
                    int v = hsh(tx + 1, ty);
                    if (find(u) == find(v))
                        continue;
                    fa[find(u)] = find(v);
                    comp[find(u)] += comp[find(v)];
                    adj[u].push_back(v);
                    adj[v].push_back(u);
                }
            }
            else
            {
                int tx = i;
                int ty = j / 2;
                if (s[i][j] == ' ')
                {
                    int u = hsh(tx, ty);
                    int v = hsh(tx, ty + 1);
                    if (find(u) == find(v))
                        continue;
                    fa[find(u)] = find(v);
                    comp[find(u)] += comp[find(v)];
                    adj[u].push_back(v);
                    adj[v].push_back(u);
                }
            }
        }
    }
    scanf("%d", &q);
    int stx, sty;
    scanf("%d%d", &stx, &sty);
    long long ans = 0;
    dfs(1, 0);
    for (int i = 1; i < q; i++)
    {
        int nxtx, nxty;
        scanf("%d%d", &nxtx, &nxty);
        int u = hsh(stx, sty);
        int v = hsh(nxtx, nxty);
        ans += dep[u] + dep[v] - 2 * dep[lca(u, v)];
        stx = nxtx;
        sty = nxty;
    }
    printf("%lld\n", ans);
    return 0;
}