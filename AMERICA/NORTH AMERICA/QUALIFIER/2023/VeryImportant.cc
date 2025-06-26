#include "bits/stdc++.h"

using namespace std; 

const int INF = 1e9; 

int main(void) {
    int n, m; 
    cin >> n >> m; 
    vector<vector<pair<int, int>>>g(n); 
    vector<int>weight(n), depth(n), fa(n), par(n), vis(m); 
    vector<tuple<int, int, int, int>>edge;
    for(int i = 0, u, v, w; i < m; i++) { 
        cin >> u >> v >> w; 
        --u, --v; 
        edge.push_back({w, u, v, i}); 
    }
    iota(par.begin(), par.end(), 0); 
    function<int(int)>find = [&](int u) { 
        return par[u] == u ? u : par[u] = find(par[u]); 
    }; 
    sort(edge.begin(), edge.end()); 
    int64_t ret = 0; 
    for(auto [w, u, v, idx] : edge) { 
        if(find(u) == find(v)) continue; 
        par[find(u)] = find(v); 
        g[u].push_back({v, w});
        g[v].push_back({u, w});
        vis[idx] = 1; 
        ret += w; 
    }
    function<void(int, int)>dfs = [&](int u, int p) { 
        for(auto [v, w] : g[u]) if(v != p) { 
            depth[v]  = depth[u] + 1; 
            weight[v] = w;
            fa[v] = u;  
            dfs(v, u);  
        }
    }; 
    dfs(0, -1); 
    int dist = 0; 
    for(auto [w, u, v, idx] : edge) { 
        if(vis[idx]) continue; 
        int ca = u, cb = v;
        while(ca != cb) { 
            if(depth[ca] > depth[cb]) ca = fa[ca]; 
            else  cb = fa[cb]; 
        }
        int curr = u; 
        while(curr != ca) { 
            dist = max(dist, w - weight[curr]);
            int cc = curr; 
            weight[curr] = INF;
            curr = fa[curr];  
            fa[cc] = ca; 
        }
        curr = v; 
        while(curr != cb) { 
            dist = max(dist, w - weight[curr]);
            int cc = curr; 
            weight[curr] = INF;
            curr = fa[curr];  
            fa[cc] = cb; 
        }
    }
    ret += dist; 
    cout << ret << '\n'; 
    return 0; 
}