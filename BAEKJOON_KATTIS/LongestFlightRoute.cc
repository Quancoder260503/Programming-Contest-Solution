#include "bits/stdc++.h"

using namespace std;

const int64_t INF = 1e17;

int main(void)
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n), rg(n);
    for (int i = 0, u, v; i < m; i++) {
        cin >> u >> v;
        g[--u].push_back(--v);
        rg[v].push_back(u); 
    }
    vector<pair<int, int>>dyn(n, {-1, -1}); 
    vector<int>vis(n), topo; 
    function<void(int)>dfs = [&](int u) { 
        vis[u] = 1; 
        for(auto v : g[u]) if(!vis[v]) { 
            dfs(v); 
        }
        topo.push_back(u); 
    }; 
    dfs(0); 
    reverse(topo.begin(), topo.end()); 
    dyn[0].first = 0; 
    for(auto u : topo) for(auto v : rg[u]) { 
        dyn[u] = max(dyn[u], {dyn[v].first + 1, v}); 
    }
    if(dyn[n - 1].first == -1) { 
        puts("IMPOSSIBLE");
        return 0; 
    }
    cout << dyn[n - 1].first + 1 << '\n'; 
    vector<int>ret; 
    int curr = n - 1; 
    while(curr) { 
        ret.push_back(curr); 
        curr = dyn[curr].second;
    }
    ret.push_back(0); 
    reverse(ret.begin(), ret.end()); 
    for(auto r : ret) cout << r + 1 << " "; 
    cout << '\n';
    return 0;
}