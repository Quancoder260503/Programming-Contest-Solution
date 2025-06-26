#include "bits/stdc++.h"

using namespace std;

const int64_t INF = 1e17;

int main(void)
{
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n);
    for (int i = 0, u, v, w; i < m; i++) {
        cin >> u >> v >> w;
        g[--u].push_back({--v, w});
    }
    vector<int64_t> dist(n, INF);
    dist[0] = 0;
    using T = pair<int64_t, int>;
    priority_queue<T, vector<T>, greater<T>> pq;
    pq.push({0, 0});
    while (pq.size()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) continue;
        for (auto [v, w] : g[u]) if (dist[v] > dist[u] + w) {
            dist[v] = dist[u] + w;
            pq.push({dist[v], v});
        }
    }
    for (int i = 0; i < n; i++) cout << dist[i] << " ";
    cout << '\n';
    return 0;
}