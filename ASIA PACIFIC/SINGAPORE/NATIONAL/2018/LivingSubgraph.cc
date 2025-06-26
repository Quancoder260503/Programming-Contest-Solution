#include "bits/stdc++.h"

using namespace std;

const int maxf = 2e4 + 10;
const int LOG = 19;
const int T = 150;

int par[LOG][maxf], h[maxf], n, m, vis[maxf];
vector<int> g[maxf];

void dfs(int u, int p)
{
    vis[u] = 1;
    for (int i = 1; i < LOG; i++)
    {
        par[i][u] = par[i - 1][par[i - 1][u]];
    }
    for (auto v : g[u])
        if (v != p)
        {
            h[v] = h[par[0][v] = u] + 1;
            dfs(v, u);
        }
    return;
}
int LCA(int u, int v)
{
    if (h[u] < h[v])
        swap(u, v);
    int d = h[u] - h[v];
    for (int i = 0; i < LOG; i++)
    {
        if (d & (1 << i))
            u = par[i][u];
    }
    if (u == v)
        return u;
    for (int i = LOG - 1; i >= 0; i--)
    {
        int tu = par[i][u], tv = par[i][v];
        if (tu != tv)
            u = tu, v = tv;
    }
    return par[0][u];
}
int dist(int u, int v)
{
    return h[u] + h[v] - 2 * h[LCA(u, v)];
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    srand(time(NULL));
    cin >> n >> m;
    vector<pair<int, int>> edge;
    vector<int> fa(n);
    iota(fa.begin(), fa.end(), 0);
    function<int(int)> find = [&](int u)
    {
        return (u == fa[u] ? u : fa[u] = find(fa[u]));
    };
    int flag = false;
    for (int i = 0, u, v; i < m; i++)
    {
        cin >> u >> v;
        --u, --v;
        edge.push_back({u, v});
        if (find(u) == find(v))
        {
            flag = true;
            continue;
        }
        fa[find(u)] = find(v);
    }
    if (!flag)
    {
        cout << -1 << '\n';
        return 0;
    }
    int ans = n + 100;
    for (int i = 0; i < T; i++)
    {
        for (int i = 0; i < n; i++)
        {
            vis[i] = 0;
            g[i].clear();
        }
        iota(fa.begin(), fa.end(), 0);
        random_shuffle(edge.begin(), edge.end());
        vector<pair<int, int>> non_tree;
        for (auto [u, v] : edge)
        {
            if (find(u) == find(v))
            {
                non_tree.push_back({u, v});
                continue;
            }
            fa[find(u)] = find(v);
            g[u].push_back(v);
            g[v].push_back(u);
        }
        for (int i = 0; i < n; i++)
        {
            if (!vis[i])
                dfs(i, -1);
        }
        for (auto [u, v] : non_tree)
        {
            ans = min(ans, dist(u, v) + 1);
        }
        if (ans == 3)
            break;
    }
    cout << ans << '\n';
    return 0;
}