#include "bits/stdc++.h"

using namespace std;

const int maxf = 2e5 + 2; 
const int LOG = 20; 

int dep[maxf], up[LOG][maxf], g[LOG][maxf]; 
vector<pair<int, int>>adj[maxf]; 

void dfs(int u, int p)
{
    for (int i = 1; i < LOG; i++) {
        up[i][u] = up[i - 1][up[i - 1][u]];
    }
    for (auto [v, w] : adj[u]){
        if (v == p) continue;
        g[0][v] = w;
        dep[v] = dep[up[0][v] = u] + 1;
        dfs(v, u);
    }
    return;
} 

int LCA(int u, int v)
{
    if (dep[u] < dep[v]) swap(u, v);
    int d = dep[u] - dep[v];
    for (int i = 0; i < LOG; i++)
    {
        if (d & (1 << i))
        {
            u = up[i][u];
        }
    }
    if (u == v) return u;
    for (int i = LOG - 1; i >= 0; i--)
    {
        int tu = up[i][u], tv = up[i][v];
        if (tu != tv) u = tu, v = tv;
    }
    return up[0][u];
}

int max_path(int x, int d) { 
    int ret = 0; 
    for(int i = 0; i < LOG; i++) if(d & (1 << i)) { 
        ret = max(ret, g[i][x]); 
        x = up[i][x]; 
    }
    return ret; 
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL); 
    int n, m, q; 
    cin >> n >> m; 
    vector<tuple<int, int, int>>edge; 
    map<pair<int, int>, int>idx;
    for(int i = 0, u, v, w; i < m; i++) { 
        cin >> u >> v >> w;
        edge.push_back({w, --u, --v});  
        idx[{u, v}] = w; 
    }
    sort(edge.begin(), edge.end()); 
    vector<int>par(n);
    iota(par.begin(), par.end(), 0); 
    function<int(int)>find = [&](int u) { 
        return u == par[u] ? u : par[u] = find(par[u]); 
    }; 
    int mst = 0; 
    for(auto [w, u, v] : edge) { 
        if(find(u) == find(v)) continue; 
        par[find(v)] = find(u); 
        mst += w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); 
    }
    dfs(0, -1); 
    for(int j = 1; j < LOG; j++) for(int i = 0; i < n; i++) { 
        g[j][i] = max(g[j - 1][i], g[j - 1][up[j - 1][i]]);  
    }
    cin >> q; 
    for(int i = 0, u, v; i < q; i++) { 
        cin >> u >> v; 
        --u, --v; 
        int anc = LCA(u, v); 
        cout << mst + idx[{u, v}] - max(max_path(u, dep[u] - dep[anc]), max_path(v, dep[v] - dep[anc])) << '\n'; 
    }
    return 0; 
}