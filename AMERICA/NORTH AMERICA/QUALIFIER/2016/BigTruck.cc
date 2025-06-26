#include "bits/stdc++.h"

using namespace std; 

const int inf = 1e9;

int main(void) {
    ios_base::sync_with_stdio(0); 
    cin.tie(0); 
    cout.tie(0);  
    int n, m; 
    cin >> n; 
    vector<int>a(n);
    for(int i = 0; i < n; i++) { 
        cin >> a[i]; 
    } 
    cin >> m; 
    vector<vector<pair<int, int>>>g(n); 
    for(int i = 0, u, v, w; i < m; i++) { 
        cin >> u >> v >> w; 
        g[--u].push_back({--v, w}); 
        g[v].push_back({u, w}); 
    }
    using T = pair<int, int>; 
    priority_queue<T, vector<T>, greater<T>>pq; 
    vector<int>dist(n, inf); 
    vector<vector<int>>par(n); 
    dist[0] = 0; 
    pq.push({dist[0], 0}); 
    while(pq.size()) { 
        auto [pdist, u] = pq.top(); 
        pq.pop(); 
        if(pdist != dist[u]) continue; 
        for(auto &[v, w] : g[u]) {
            if(dist[v] == dist[u] + w) { 
                par[v].push_back(u); 
            } 
            else if(dist[v] > dist[u] + w) { 
                par[v].clear(); 
                par[v].push_back(u); 
                dist[v] = dist[u] + w; 
                pq.push({dist[v], v}); 
            }
        }
    }
    vector<vector<int>>gg(n);
    function<void(int)> trace = [&](int u) { 
        if(!u) return; 
        for(auto &v : par[u]) { 
            gg[u].push_back(v); 
            trace(v); 
        }
    }; 
    trace(n - 1);
    int64_t ret = 0;  
    vector<int>dyn(n, -1); 
    function<int(int)> doit = [&](int u) { 
        if(!u) return a[u]; 
        int &ret = dyn[u]; 
        if(ret != -1) return ret;
        ret = 0;  
        for(auto &v : gg[u]) { 
            ret = max(ret, doit(v) + a[u]); 
        }
        return ret;
    };
    if(dist[n - 1] == inf) { cout << "impossible\n"; } 
    else { 
        cout << dist[n - 1] << " " << doit(n - 1) << '\n'; 
    }
    return 0; 
}