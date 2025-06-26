#include "bits/stdc++.h"

using namespace std;

int main(void)
{
    map<tuple<int, int, int>, int>mp; 
    map<pair<int, int>, int>mp2; 
    int n, nodes = 0, nodesb = 0; 
    cin >> n; 
    set<pair<int, int>>edge, edgeb; 
    for(int i = 0; i < n; i++) { 
        int x1, y1, z1, x2, y2, z2; 
        cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2; 
        if(!mp2.count({x1, y1})) mp2[{x1, y1}] = nodesb++; 
        if(!mp2.count({x2, y2})) mp2[{x2, y2}] = nodesb++; 
        if(!mp.count({x1, y1, z1})) mp[{x1, y1, z1}] = nodes++; 
        if(!mp.count({x2, y2, z2})) mp[{x2, y2, z2}] = nodes++; 
        int u = mp[{x1, y1, z1}], v = mp[{x2, y2, z2}]; 
        if(u > v) swap(u, v); 
        if(u != v) edge.insert({u, v});
        u = mp2[{x1, y1}], v = mp2[{x2, y2}];
        if(u > v) swap(u, v); 
        if(u != v) edgeb.insert({u, v}); 
    }
    vector<int>fa(nodes), fab(nodesb); 
    iota(fa.begin(), fa.end(), 0);
    iota(fab.begin(), fab.end(), 0); 
    function<int(int)>find = [&](int u) { 
        return u == fa[u] ? u : fa[u] = find(fa[u]); 
    };
    function<int(int)>findb = [&](int u) { 
        return u == fab[u] ? u : fab[u] = findb(fab[u]); 
    };
    int flag = 0, flagb = 0; 
    for(const auto &[u, v] : edge) {
        if(find(u) == find(v)) {
            flag = 1; 
            break;  
        }
        fa[find(u)] = find(v);
    }
    for(const auto &[u, v] : edgeb) {
        if(findb(u) == findb(v)) {
            flagb = 1; 
            break;  
        }
        fab[findb(u)] = findb(v);
    }
    cout << (flag ? "True closed chains" : "No true closed chains") << '\n'; 
    cout << (flagb ? "Floor closed chains" : "No floor closed chains") << '\n'; 
    return 0;
}