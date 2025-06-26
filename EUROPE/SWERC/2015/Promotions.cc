#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    int a, b, n, m; 
    cin >> a >> b >> n >> m; 
    vector<vector<int>>g(n); 
    for(int i = 0; i < m; i++) { 
        int u, v; cin >> u >> v;
        g[u].push_back(v); 
    }
    vector<int> vis(n), pred(n), succ(n);
    function<void(int)>dfs = [&](int u) { 
        vis[u] = 1; 
        for(auto v : g[u]) if(!vis[v]) dfs(v);
        return; 
    }; 
    for(int i = 0; i < n; i++) { 
        dfs(i); 
        for(int j = 0; j < n; j++) if(i != j && vis[j]) { 
            succ[i]++;
            pred[j]++; 
        }
        fill(vis.begin(), vis.end(), 0); 
    }
    int reta = 0, retb = 0, retc = 0; 
    for(int i = 0; i < n; i++) { 
        if(pred[i] >= b) { retc++; continue;} 
        if(succ[i] >= n - a) reta++; 
        if(succ[i] >= n - b) retb++;  
    }
    cout << reta << "\n" << retb << "\n" << retc << '\n'; 
    return 0; 
}