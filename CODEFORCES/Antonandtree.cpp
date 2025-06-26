#include "bits/stdc++.h"
using namespace std;
#define MAXN (int)2e5 + 10
#define mp make_pair
#define pii pair<int, int>
vector<int> adj[MAXN];
vector<int> tadj[MAXN];
int fa[MAXN];
int col[MAXN];
int dep[MAXN];
int n;
pii ans = mp(0, 0);
void dfs(int u, int p, int curr)
{
    fa[u] = curr;
    for (int i = 0; i < adj[u].size(); i++)
    {
        int v = adj[u][i];
        if (v == p || col[u] != col[v]) continue;
        dfs(v, u, curr);
    }
}
void dfs2(int u, int p)
{
    for (int i = 0; i < tadj[u].size(); i++)
    {
        int v = tadj[u][i];
        if (v == p) continue;
        dep[v] = dep[u] + 1;
        ans = max(ans, mp(dep[v], v)); 
        dfs2(v, u);
    }
}
signed main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> col[i];
    }
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int comp = 0;
    memset(fa, 0, sizeof(fa)); 
    for (int i = 1; i <= n; i++)
    {
        if (fa[i] == 0)
        {
            ++comp;
            dfs(i, -1, comp);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < adj[i].size(); j++)
        {
            int u = i;
            int v = adj[i][j];
            if (fa[u] == fa[v])
                continue;
            tadj[fa[u]].push_back(fa[v]);
        }
    }
    dfs2(1, 0);
    dep[ans.second] = 0;
    dfs2(ans.second, 0);
    cout << (ans.first + 1) / 2 << '\n';
    return 0;
}
/*
   We divide the white nodes into a connected components and turn it into
   a big node --> Our tree now is special -> child color is different to
   the node -> now we can change the color by synchronize the parents node
   color to its child node and then swap it again (back in fourth).

   This strategy can be computed directly however the answer to these
   process is actually (d + 1) / 2 where d is the diameter of the special tree
   (as we span the process from the root to two furthest node of the tree)
*/