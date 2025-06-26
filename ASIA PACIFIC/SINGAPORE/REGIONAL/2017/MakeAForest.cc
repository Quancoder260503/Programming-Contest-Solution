#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    ios_base::sync_with_stdio(0); 
    cin.tie(0); 
    cout.tie(0); 
    int n, m; 
    cin >> n >> m; 
    vector<tuple<int, int, int>>edge; 
    for(int i = 0, u, v, w; i < n; i++) { 
        cin >> u >> v >> w; 
        edge.push_back({w, u, v}); 
    }
    sort(edge.begin(), edge.end());
    map<int, int>cap; 
    int ret = 0; 
    for(int i = 0; i < n; i++) { 
        auto [w, u, v] = edge[i]; 
        if(cap[u] == 0) { 
            cap[u] += m - 1; 
            cap[v] += m;
            ret++;  
        }
        else {
            cap[u]--; 
            cap[v] += m; 
        }
    } 
    cout << ret << '\n'; 
    return 0; 
}