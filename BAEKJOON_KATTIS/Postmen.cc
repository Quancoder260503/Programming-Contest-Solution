#include "bits/stdc++.h"
using namespace std;
int n, m, cyc;
vector<int> itr;
vector<bool> vis;
vector<bool> vise;
vector<int> ans;
vector<vector<pair<int, int>>> adj;
void dfs(int u)
{
    vis[u] = 1;
    while (itr[u] < adj[u].size())
    {
        auto [v, idx] = adj[u][itr[u]++];
        if (!vise[idx])
        {
            vise[idx] = 1;
            if (vis[v])
            {
                ans.push_back(u);
                cyc = v;
                return;
            }
            dfs(v);
            ans.push_back(u);
            if (u == cyc)
            {
                for (auto v : ans)
                {
                    cout << v + 1 << ' ';
                    vis[v] = 0;
                }
                cout << '\n';
                ans.clear();
                cyc = -1;
                vis[u] = 1;
            }
            else if (cyc > -1)
            {
                return;
            }
        }
    }
    return;
};
signed main(void)
{
    cin >> n >> m;
    cyc = -1;
    adj.resize(n);
    vise.resize(m, 0);
    vis.resize(n, 0);
    itr.resize(n, 0);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
    }
    for (int i = 0; i < n; i++)
    {
        if (itr[i] < adj[i].size())
        {
            dfs(i);
        }
    }
    return 0;
}