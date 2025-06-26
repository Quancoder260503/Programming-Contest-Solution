#include "bits/stdc++.h"

using namespace std; 

const int mod = 1e9 + 7; 

int main(void)
{
    int n, m; 
    cin >> n >> m; 
    vector<vector<array<int64_t, 3>>>g(n); 
    vector<array<int, 3>>edge; 
    for(int i = 0; i < m; i++) {
        int u, v;
        int64_t w; 
        cin >> u >> v >> w;
        --u, --v; 
        g[u].push_back({v, w, i});
        edge.push_back({u, v, i});   
    }
    using T = pair<int64_t, int>; 
    vector<int64_t>dist(n, LLONG_MAX); 
    priority_queue<T, vector<T>, greater<T>>pq; 
    vector<vector<pair<int, int>>>fa(n); 
    pq.push({0, 0}); 
    dist[0] = 0; 
    while(pq.size())
    {
        auto [d, u] = pq.top();
        pq.pop();
        if(d != dist[u]) continue; 
        for(auto [v, w, idx] : g[u]) {
            if(dist[v] == dist[u] + w){
                fa[v].push_back({u, idx}); 
            }
            else if(dist[v] > dist[u] + w) {
                fa[v].clear(); 
                fa[v].push_back({u, idx}); 
                dist[v] = dist[u] + w; 
                pq.push({dist[v], v}); 
            }
        }
    }
    vector<int>marked(m); 
    vector<vector<int>>dag(n), rdag(n); 
    for(int i = 0; i < n; i++) for(auto [f, idx] : fa[i]) {
        marked[idx] = 1; 
        dag[f].push_back(i); 
        rdag[i].push_back(f); 
    }
    int src = 0, dst = n - 1; 
    vector<int64_t>dyn(n), rdyn(n);
    dyn[src] = rdyn[dst] = 1; 
    function<int64_t(int)> calc = [&](int u) {
        if(dyn[u]) return dyn[u];
        for(auto v : rdag[u]) {
            dyn[u] = (dyn[u] + calc(v)) % mod; 
        } 
        return dyn[u]; 
    };
    function<int64_t(int)> calc2 = [&](int u)
    {
        if (rdyn[u]) return rdyn[u];
        for (auto v : dag[u]) {
            rdyn[u] = (rdyn[u] + calc2(v)) % mod;
        }
        return rdyn[u];
    }; 
    for(int i = 0; i < n; i++) calc(i), calc2(i); 
    for(auto [u, v, id] : edge){
        if(marked[id])
        {
            if(dist[u] > dist[v]) swap(u, v); 
            cout << (dyn[dst] - 1LL * dyn[u] % mod * rdyn[v] % mod + mod) % mod << '\n'; 
        }
        else 
        {
            cout << dyn[dst] << '\n'; 
        }
    }
    return 0;
}