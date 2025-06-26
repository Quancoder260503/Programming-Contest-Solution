#include "bits/stdc++.h"

using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
    cout.tie(NULL); 
    int n; 
    cin >> n; 
    vector<int>trs(n, 1); 
    vector<double>ret(n); 
    vector<vector<int>>adj(n); 
    for(int i = 1, x; i < n; i++) { 
        cin >> x;
        adj[--x].push_back(i); 
    }
    function<void(int)>dfs = [&](int u) { 
        for(auto v : adj[u]) {
            dfs(v);  
            trs[u] += trs[v]; 
        }
        return; 
    };
    dfs(0); 
    function<void(int, double)>dfs2 = [&](int u, double x) { 
        x += 2; 
        ret[u] = x; 
        for(auto v : adj[u]) { 
            dfs2(v, x + trs[u] - trs[v] - 1); 
        }
        return; 
    }; 
    dfs2(0, 0); 
    for(int i = 0; i < n; i++) cout << ret[i] / 2 << " "; 
    return 0;
}