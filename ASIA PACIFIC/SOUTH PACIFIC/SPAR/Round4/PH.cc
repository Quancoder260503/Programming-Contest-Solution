#include "bits/stdc++.h"

using namespace std; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    int n; 
    cin >> n; 
    map<string, int>mp; 
    int idx = 0;  
    vector<pair<int, int>>edge; 
    for(int i = 0; i < n; i++) { 
        string name, toya, toyb;
        cin >> name >> toya >> toyb; 
        if(!mp.count(toya)) mp[toya] = idx++; 
        if(!mp.count(toyb)) mp[toyb] = idx++;   
        edge.push_back({mp[toya], mp[toyb]}); 
    }
    vector<vector<int>>g(idx); 
    vector<int>deg(idx);
    for(auto [u, v] : edge) {
        g[u].push_back(v); 
        g[v].push_back(u); 
        deg[u]++; 
    }
    int chk = true;
    vector<int>vis(idx);  
    int curr_ret = 0, ret = 0;  
    function<void(int, int)> doit = [&](int u, int d) { 
        vis[u] = true; 
        if(deg[u] != 1) chk = false; 
        for(auto v : g[u]) { 
            if(vis[v]) { 
                curr_ret = max(curr_ret, d + 1); 
            }
            else { 
                doit(v, d + 1); 
            }
        }
        return; 
    }; 
    for(int i = 0; i < idx; i++) { 
        fill(vis.begin(), vis.end(), false); 
        curr_ret = 0, chk = true; 
        doit(i, 0); 
        if(chk) ret = max(ret, curr_ret); 
    }
    if(!ret) { 
        cout << "No trades possible\n";  
    }
    else cout << ret << '\n'; 
    return 0; 
}