#include "bits/stdc++.h"

using namespace std; 

const int maxf = 300002;

bitset<maxf>dyn; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k; 
    cin >> n >> k;
    vector<multiset<pair<int, int>>>g(2 * n); 
    for(int i = 0, u, v, s; i < 2 * n; i++) { 
        cin >> u >> v >> s;
        --u, --v;
        g[u].insert({n + v,  s}); 
        g[n + v].insert({u, -s}); 
    } 
    queue<int>q; 
    for(int i = 0; i < 2 * n; i++) { 
        if(g[i].empty()) { 
            cout << "NO\n";
            return 0; 
        }
        if(g[i].size() == 1) q.push(i); 
    }
    int64_t cc = 0; 
    while(q.size()) { 
        int u = q.front(); 
        q.pop(); 
        if(g[u].empty()) { 
            cout << "NO\n";
            return 0; 
        }
        auto [v, cost] = *g[u].begin(); 
        cc += cost;
        g[u].clear(); 
        g[v].erase(g[v].find({u, -cost}));
        if(g[v].size() == 1) q.push(v); 
    }
    vector<int>w; 
    w.push_back(abs(cc)); 
    vector<int>vis(2 * n);
    function<void(int)>doit = [&](int u) { 
        if(vis[u] || g[u].empty()) return; 
        vis[u] = true; 
        auto [v, cost] = *g[u].begin(); 
        cc += cost; 
        g[u].erase(g[u].begin());
        if(!vis[v]) { 
            g[v].erase(g[v].find({u, -cost})); 
            g[u].clear(); 
            doit(v); 
        } 
        return; 
    }; 
    for(int i = 0; i < 2 * n; i++) if(!vis[i] && g[i].size()) { 
        cc = 0;
        g[i].erase(g[i].begin());  
        doit(i); 
        w.push_back(abs(cc)); 
    }
    dyn[0] = 1; 
    for(auto ws : w) dyn |= dyn << ws; 
    int64_t acc = accumulate(w.begin(), w.end(), 0LL);
    for(int i = 0; i <= acc; i++) { 
        if(dyn[i] && abs(2 * i - acc) <= k) { 
            cout << "YES\n"; 
            return 0; 
        }
    }
    cout << "NO\n"; 
    return 0; 
}