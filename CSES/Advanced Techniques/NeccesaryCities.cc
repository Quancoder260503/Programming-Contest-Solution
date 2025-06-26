#include "bits/stdc++.h"

using namespace std;

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

int main(void)
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i = 0, u, v; i < m; i++)
    {
        cin >> u >> v;
        g[--u].push_back(--v);
        g[v].push_back(u);
    }
    UndirectedDfs graph(g);
    cout << graph.articulation_points.size() << '\n';
    for (auto u : graph.articulation_points)
    {
        cout << u + 1 << '\n';
    }
    cout << '\n'; 
    return 0;
}