#include "bits/stdc++.h"
using namespace std;
#define lint long long
const lint INF = 1e16;
signed main(void)
{
    int n, m, d;
    cin >> n >> m >> d;
    vector<vector<pair<int, int>>> adj(n);
    vector<vector<pair<int, int>>> adj2(n);
    for (int i = 0; i < m; i++)
    {
        int u, v, cost;
        cin >> u >> v >> cost;
        --u, --v;
        adj[u].push_back({v, cost});
        //adj[v].push_back({u, cost});
    }
    vector<lint> dist(n);
    vector<vector<int>> fa(n);
    map<lint, int> table;
    auto dijsktra = [&](int src, vector<vector<pair<int, int>>> &adj)
    {
        using T = pair<lint, int>;
        priority_queue<T, vector<T>, greater<T>> pq;
        fill(dist.begin(), dist.end(), INF);
        dist[src] = 0;
        pq.push({0, src});
        while (pq.size())
        {
            auto [tdist, u] = pq.top();
            pq.pop();
            if (tdist != dist[u])
                continue;
            for (auto [v, cost] : adj[u])
            {
                if (dist[v] == 1LL * (dist[u] + cost))
                {
                    fa[v].push_back(u);
                }
                else if (dist[v] > 1LL * (dist[u] + cost))
                {
                    dist[v] = 1LL * (dist[u] + cost);
                    fa[v].clear();
                    fa[v].push_back(u);
                    pq.push({dist[v], v});
                }
            }
        }
    };
    dijsktra(0, adj);
    for (int i = 0; i < n; i++)
    {
        table[dist[i]]++;
    }
    vector<lint> ord(d);
    for (int i = 0; i < d; i++)
    {
        cin >> ord[i];
        if (table.count(ord[i]) == 0)
        {
            puts("0");
            return 0;
        }
    }
    for (int at = 0; at < n; at++)
    {
        for (auto [v, cost] : adj[at])
        {
            if (dist[v] == dist[at] + cost)
            {
                int geta = lower_bound(ord.begin(), ord.end(), dist[at] + 1) - ord.begin();
                int getb = lower_bound(ord.begin(), ord.end(), dist[v]) - ord.begin();
                if (geta == getb)
                {
                    adj2[at].push_back({v, 1});
                }
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        fa[i].clear();
    }
    dijsktra(0, adj2);
    if (dist[n - 1] == INF)
    {
        puts("0");
        return 0;
    }
    int maxx = 0;
    for (int i = 0; i < n; i++)
    {
        maxx = max(maxx, (int)fa[i].size());
    }
    if (maxx > 1)
    {
        puts("1");
    }
    else
    {
        int at = n - 1;
        vector<int> res;
        while (at > 0)
        {
            res.push_back(at);
            at = fa[at][0];
        }
        res.push_back(0);
        cout << res.size() << '\n';
        reverse(res.begin(), res.end());
        for (auto city : res)
        {
            cout << city + 1 << '\n';
        }
    }
    return 0;
}