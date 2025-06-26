#include "bits/stdc++.h"

using namespace std; 

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL); 
    int n; 
    cin >> n; 
    vector<pair<int, int>>arr(n); 
    vector<vector<int>>adj(n);
    for(int i = 0; i < n; i++) { 
        cin >> arr[i].first >> arr[i].second; 
        adj[--arr[i].first].push_back(i);
        adj[--arr[i].second].push_back(i); 
    }
    vector<int>tvis(n), vis(n); 
    function<void(int, int)> dfs = [&](int u, int x) { 
        vis[u] = true; 
        for(auto v : adj[u]) if(!vis[v] && v != x) { 
            dfs(v, x); 
        }
        return; 
    };
    for(int i = 0; i < n; i++) { 
        fill(tvis.begin(), tvis.end(), true); 
        for(auto src : {i, arr[i].first, arr[i].second}) {
            fill(vis.begin(), vis.end(), false);
            dfs(src, i);
            for (int j = 0; j < n; j++) tvis[j] &= vis[j];
        }
        int ret = false; 
        for(int j = 0; j < n; j++) { 
            if(tvis[j]) { 
                ret = true; 
                break; 
            }
        }
        cout << (ret ? 'Y' : 'N'); 
    }
    cout << '\n'; 
    return 0; 
}