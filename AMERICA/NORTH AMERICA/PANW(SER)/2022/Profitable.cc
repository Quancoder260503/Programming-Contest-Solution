#include "bits/stdc++.h"
using namespace std; 
#define lint long long 
const lint INF = 1e9;
signed main(void)
{
    int n, m; 
    lint K; 
    cin >> n >> m >> K; 
    vector<vector<pair<int, int>>>adj(n); 
    for(int i = 0; i < m; i++)
    {
        int u, v; 
        lint cost; 
        cin >> u >> v >> cost; 
        adj[--u].push_back({--v, cost}); 
    }
    queue<int>q; 
    vector<lint>dist(n, -INF); 
    q.push(0);
    dist[0] = 0;
    while(q.size())
    {
        int u = q.front();
        q.pop(); 
        for(auto [v, cost] : adj[u])
        {
            if(dist[v] < min(K, cost + dist[u]))
            {
                dist[v] = min(K, cost + dist[u]);
                q.push(v);  
            }
        }
    }
    cout << dist[n - 1] << '\n';
    return 0; 
}