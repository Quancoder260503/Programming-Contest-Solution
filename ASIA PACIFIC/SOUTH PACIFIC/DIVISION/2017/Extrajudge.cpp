#include "bits/stdc++.h"
using namespace std;
const int MAXN = (int)2e5 + 10;
int fa[MAXN];
struct UndirectedDfs
{
    vector<vector<int>> g;
    int n;
    vector<int> low, num, parent;
    vector<bool> is_articulation;
    int counter, root, children;

    vector<pair<int, int>> bridges;
    vector<int> articulation_points;
    map<pair<int, int>, int> cnt_edges;

    UndirectedDfs(const vector<vector<int>> &_g) : g(_g), n(g.size()),
                                                   low(n, 0), num(n, -1), parent(n, 0), is_articulation(n, false),
                                                   counter(0), children(0)
    {
        for (int u = 0; u < n; u++)
        {
            for (int v : g[u])
            {
                cnt_edges[{u, v}] += 1;
            }
        }
        for (int i = 0; i < n; ++i)
            if (num[i] == -1)
            {
                root = i;
                children = 0;
                dfs(i);
                is_articulation[root] = (children > 1);
            }
        for (int i = 0; i < n; ++i)
            if (is_articulation[i])
                articulation_points.push_back(i);
    }

private:
    void dfs(int u)
    {
        low[u] = num[u] = counter++;
        for (int v : g[u])
        {
            if (num[v] == -1)
            {
                parent[v] = u;
                if (u == root)
                    children++;
                dfs(v);
                if (low[v] >= num[u])
                    is_articulation[u] = true;
                if (low[v] > num[u])
                {
                    if (cnt_edges[{u, v}] == 1)
                    {
                        bridges.push_back(make_pair(u, v));
                    }
                }
                low[u] = min(low[u], low[v]);
            }
            else if (v != parent[u])
                low[u] = min(low[u], num[v]);
        }
    }
};
int deg[MAXN];
bool vis[MAXN];
int find(int u)
{
    return u == fa[u] ? u : fa[u] = find(fa[u]);
}
vector<int> ke[MAXN];
signed main(void)
{
    int n;
    cin >> n;
    vector<vector<int>> adj(n, vector<int>());
    vector<pair<int, int>> edge;
    for (int i = 0; i < n; i++)
    {
        int sz;
        cin >> sz;
        for (int j = 0; j < sz; j++)
        {
            int x;
            cin >> x;
            adj[i].push_back(x);
            adj[x].push_back(i);
            edge.push_back({i, x});
        }
    }
    UndirectedDfs dfs_tree(adj);
    auto bridge = dfs_tree.bridges;
    iota(fa, fa + n, 0);
    int ans = 0;
    map<pair<int, int>, int> mp;
    for (auto [u, v] : bridge)
    {
        mp[{u, v}] = mp[{v, u}] = 1;
    }
    for (auto [u, v] : edge)
    {
        if (mp[{u, v}] == 1)
            continue;
        if (find(u) == find(v))
            continue;
        fa[find(u)] = find(v);
    }
    for (auto [u, v] : bridge)
    {
        ke[find(u)].push_back(find(v));
        ke[find(v)].push_back(find(u));
    }
    for (int i = 0; i < n; i++)
    {
        if (!vis[fa[i]])
        {
            ans += (ke[fa[i]].size() == 1);
            vis[fa[i]] = 1;
        }
    }
    cout << max(ans - 1, 0) << '\n';
    return 0;
}