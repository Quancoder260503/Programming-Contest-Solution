#include "bits/stdc++.h"

using namespace std;

const int INF = 1e9; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m, l, r;
    cin >> n >> m >> l >> r;
    vector<vector<pair<int, int>>>adj(n);
    for (int i = 0, u, v, w; i < m; i++) {
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); 
    }
    vector<int64_t> dist(n); 
    auto dijsktra = [&](int src, vector<vector<pair<int, int>>> &adj) {
        using T = pair<int64_t, int>;
        priority_queue<T, vector<T>, greater<T>> pq;
        fill(dist.begin(), dist.end(), INF);
        dist[src] = 0;
        pq.push({0, src});
        while (pq.size()) {
            auto [tdist, u] = pq.top();
            pq.pop();
            if (tdist != dist[u]) continue;
            for (auto [v, cost] : adj[u]) {
                if (dist[v] > 1LL * (dist[u] + cost)) {
                    dist[v] = 1LL * (dist[u] + cost);
                    pq.push({dist[v], v});
                }
            }
        }
    };
    dijsktra(0, adj);
    map<pair<int, int>, int> vis;
    int ret = 0; 
    for (int u = 0; u < n; u++) {
        if (dist[u] * 2 >= r) continue;
        for(auto [v, cost] : adj[u]) {
            int xu = u, xv = v;
            if (xu > xv) swap(xu, xv); 
            if (vis[{xu, xv}]) continue;
            vis[{xu, xv}]++;
            ret++; 
        }
    }
    cout << ret << '\n'; 
    return 0;
}





