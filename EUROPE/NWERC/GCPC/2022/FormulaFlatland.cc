#include "bits/stdc++.h"

using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    for (int i = 0, x, y; i < n; i++) {
        cin >> x >> y; 
    }
    vector<vector<int>> g(n); 
    for (int i = 0, u, v; i < m; i++) {
        cin >> u >> v;
        g[--u].push_back(--v);
        g[v].push_back(u); 
    }
    int ret = 5;
    vector<int> ord(n), marked(n, false), deg(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int u, int v) { return int(g[u].size()) > int(g[v].size()); });
    for(auto u : ord) {
        marked[u] = true; 
        for (auto v : g[u]) if(!marked[v]) {
            deg[v] = 1; 
        }
        for(auto v : g[u]) if(!marked[v]) { 
            for(auto x : g[v]) if(x != u) { 
                if(deg[x] == 1) {
                    ret = min(ret, 3); 
                }
                else if(deg[x] == 2) {
                    ret = min(ret, 4); 
                }
                else {
                    deg[x] = 2;
                }
            }
        }
        for(auto v : g[u]) if(!marked[v]) { 
            for(auto x : g[v]) {
                deg[x] = 0;
            }
            deg[v] = 0; 
        }
    }
    cout << ret << '\n';
    return 0;
}