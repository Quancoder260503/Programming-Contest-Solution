#include "bits/stdc++.h"
using namespace std;
const int MAXN = (int)3e5 + 10;
vector<pair<int, int>> adj[MAXN];
const int LOG = 24; 
int up[LOG][MAXN]; 
int dp[LOG][MAXN][2];
int dep[MAXN]; 
void dfs(int u)
{
    for (int i = 1; i < LOG; i++)
    {
        up[i][u] = up[i - 1][up[i - 1][u]];
    }
    for (int i = 0; i < adj[u].size(); i++)
    {
        int v = adj[u][i].second;
        int ch = adj[u][i].first;
        dep[v] = dep[up[0][v] = u] + 1;
        dp[0][v][ch == 'P']++;
        dfs(v);
    }
    return;
}
int jump(int dist, int u)
{
    for (int i = 0; i < LOG; i++)
    {
        if (dist & (1 << i)) u = up[i][u];
    }
    return u;
}

int calc(int dist, int u, int p)
{
    int tot = 0; 
    for (int i = 0; i < LOG; i++)
    {
        if (dist & (1 << i))
        {
            tot += dp[i][u][p];
            u = up[i][u];
        }
    }
    return tot;
}
int LCA(int u, int v)
{
    if (dep[u] < dep[v]) swap(u, v);
    int dist = dep[u] - dep[v];
    u = jump(dist, u); 
    if (u == v) return u;
    for (int i = LOG - 1; i >= 0; i--)
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
    int n, q;
    cin >> n >> q;
    for (int i = 2; i <= n + 1; i++)
    {
        char t; int pa;
        cin >> t >> pa;
        adj[pa].push_back({t, i});
    }
    dfs(1);
    int ans = 0;
    for (int i = 1; i < LOG; i++)
    {
        for(int j = 1; j <= n + 1; j++)
        {
            for(int k = 0; k < 2; k++)
            {
                dp[i][j][k] = dp[i - 1][j][k] + dp[i - 1][up[i - 1][j]][k];
            }
        }
    }
    for(int i = 0; i < q; i++)
    {
        int u, v; cin >> u >> v;
        int anc = LCA(u, v);
        if(dep[u] < dep[v]) swap(u, v);
        if(v == anc)
        {
             u = jump(dep[u] - dep[v] - 1, u); 
             ans += dp[0][u][0]; 
        }
        else 
        {
            int good = 0;
            int fu = jump(dep[u] - dep[anc] - 1, u);
            int fv = jump(dep[v] - dep[anc] - 1, v); 
            good = good || (dp[0][fu][0] && dp[0][fv][0]);
            good = good || (fu > fv && dp[0][fv][0] && dp[0][fu][1]);
            good = good || (fv > fu && dp[0][fu][0] && dp[0][fv][1]);
            ans += good;
        }
    }
    cout << ans << '\n';
    return 0;
}
// there is a path from anc to a node iff the first edge on the tree path to that node is L
// there is a path from v to children node of anc iff L is inserted before P
// 
