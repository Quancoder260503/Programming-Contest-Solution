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

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); 
    int n, m;
    cin >> n >> m;
    vector<vector<array<int64_t, 3>>> g(n);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        int64_t w;
        cin >> u >> v >> w;
        --u, --v;
        g[u].push_back({v, w, i});
    }
    using T = pair<int64_t, int>;
    vector<int64_t> dist(n, LLONG_MAX);
    priority_queue<T, vector<T>, greater<T>> pq;
    vector<vector<pair<int, int>>> fa(n);
    pq.push({0, 0});
    dist[0] = 0;
    while (pq.size())
    {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) continue;
        for (auto [v, w, idx] : g[u]) {
            if (dist[v] == dist[u] + w) {
                fa[v].push_back({u, idx});
            }
            else if (dist[v] > dist[u] + w) {
                fa[v].clear();
                fa[v].push_back({u, idx});
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    vector<vector<int>> adj(n); 
    vector<int>vis(n);
    function<void(int)>trace = [&](int u) { 
        if(u == 0 || vis[u]) return;
        vis[u] = true; 
        for (auto [f, idx] : fa[u]) {
            adj[f].push_back(u);
            adj[u].push_back(f);
            trace(f); 
        }
    };
    trace(n - 1); 
    UndirectedDfs graph(adj); 
    vector<int>ret(graph.articulation_points); 
    ret.push_back(0);
    ret.push_back(n - 1);
    sort(ret.begin(), ret.end());
    cout << ret.size() << '\n'; 
    for(auto c : ret) cout << c + 1 << ' '; 
    cout << '\n'; 
    return 0;
}