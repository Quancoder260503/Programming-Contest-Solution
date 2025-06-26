#include "bits/stdc++.h"

using namespace std;

int
main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int i = 0, u, v; i < m; i++) {
        cin >> u >> v;
        adj[--u].push_back(--v);
        adj[v].push_back(u);
    }
    vector<int> dist(n, -1);
    queue<int>q;
    dist[0] = 0;
    q.push(0); 
    while(q.size()) {
        int u = q.front();
        q.pop();
        for (auto v : adj[u])
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
    }
    int ret = 0;
    for(int i = 0; i < n; i++) {
        if(dist[i] == -1) {
            cout << dist[i] << '\n';
            return 0; 
        }
        ret = max(ret, dist[i]); 
    }
    cout << int(ceil(log2(ret))) + 1 << '\n'; 
    return 0;
}