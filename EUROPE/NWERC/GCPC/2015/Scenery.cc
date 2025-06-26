#include "bits/stdc++.h"
using namespace std;
const int64_t INF = 1e12; 
const int mod = 1e9 + 7; 
int main(void)
{
    int n, m, k;
    while(cin >> n >> m >> k)
    {
        vector<vector<pair<int, int64_t>>> adj(n); 
        vector<int>path(k);
        for(int i = 0; i < k; i++)
        {
            cin >> path[i];
            path[i]--; 
        }
        for (int i = 0; i < m; i++)
        {
            int u, v, cost;
            cin >> u >> v >> cost;
            --u, --v;
            adj[u].push_back({v, cost});
            adj[v].push_back({u, cost}); 
        }
        vector<int64_t> dist(n);
        vector<int64_t> fa(n);
        auto dijsktra = [&](int src)
        {
            using T = pair<int64_t, int>;
            priority_queue<T, vector<T>, greater<T>> pq;
            fill(dist.begin(), dist.end(), INF);
            dist[src] = 0;
            fa[src]   = 1; 
            pq.push({0, src});
            while (pq.size())
            {
                auto [tdist, u] = pq.top();
                pq.pop();
                if (tdist != dist[u]) continue;
                for (auto [v, cost] : adj[u])
                {
                    if (dist[v] == 1LL * (dist[u] + cost))
                    {
                        fa[v] = (fa[v] + fa[u] + mod) % mod;
                    }
                    else if (dist[v] > 1LL * (dist[u] + cost))
                    {
                        dist[v] = 1LL * (dist[u] + cost);
                        fa[v] = fa[u]; 
                        pq.push({dist[v], v});
                    }
                }
            }
        };
        dijsktra(0);
        cout << (fa[n - 1] > 1 ? "yes" : "no") << '\n'; 
    }
    return 0;
}