#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int maxf = 1e5 + 10; 
const int LOG = 23;

vector<int>g[maxf]; 
vector<int> adj[maxf];
int up[LOG][maxf], dep[maxf], path[maxf], a[maxf], visited[maxf];
set<pair<int, int>>ms[maxf]; 

void dfs(int u, int c) {
    if(!sz(adj[u])) g[c].push_back(u); 
    for (int i = 1; i < LOG; i++) {
        up[i][u] = up[i - 1][up[i - 1][u]];
    }
    visited[u] = true; 
    for (auto &v : adj[u]) {
        dep[v] = dep[up[0][v] = u] + 1;
        path[v] = path[u] + a[v]; 
        dfs(v, c);
    }
    return;
}

int LCA(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    int d = dep[u] - dep[v];
    for (int i = 0; i < LOG; i++) if (d & (1 << i)) {
        u = up[i][u];
    }
    if (u == v) return u;
    for (int i = LOG - 1; i >= 0; i--) {
        int tu = up[i][u], tv = up[i][v];
        if (tu != tv) u = tu, v = tv;
    }
    return up[0][u];
}

int dist(int u, int v) {
    return path[u] + path[v] - path[LCA(u, v)];
}

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int n, m; 
    cin >> n >> m; 
    for(int i = 1; i <= n; i++) { 
        cin >> a[i]; 
    }
    for(int i = 0, u, v; i < m; i++) { 
        cin >> u >> v; 
        adj[u].push_back(v); 
    }
    int id = 0; 
    for(int i = 1; i <= n; i++) if(!visited[i]) { 
        path[i] = a[i]; 
        dfs(i, id++); 
    }
    int ret = int(1e9);
    vector<int>cc;  
    for(int i = 0; i < id; i++) { 
        for(auto x : g[i]) for(auto y : g[i]) if(x != y) { 
            ret = min(ret, dist(x, y)); 
        }
        if(sz(g[i]) == 1) { 
            cc.push_back(path[g[i].back()]); 
        }
    }
    sort(cc.begin(), cc.end()); 
    if(sz(cc) > 1) ret = min(ret, cc[0] + cc[1]); 
    cout << ret << '\n'; 
    return 0; 
}