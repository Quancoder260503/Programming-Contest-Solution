#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

struct Tree {
    map<vector<int>, int>mp; 
    vector<vector<int>> g;
    vector<int>label; 
    vector<int> par, centroid;
    int n, nodes;
    Tree(vector<vector<int>> &_g) {
        g = _g;
        n = g.size();
        nodes = 0; 
        label.resize(n); 
        par.resize(n);
        return; 
    }
    int dfs(int u, int p) {
        vector<int> ret;
        for (auto v : g[u]) if (v != p) {
            ret.push_back(dfs(v, u));
        }
        sort(ret.begin(), ret.end());
        if (mp.count(ret) == 0) mp[ret] = ++nodes;
        return label[u] = mp[ret];
    }
    void dfs2(int u, int p, int sz) {
        par[u] = 1; 
        bool is_centroid = true; 
        for (auto v : g[u]) if (v != p) {
            dfs2(v, u, sz);
            par[u] += par[v]; 
            if(par[v] > sz / 2) is_centroid = false; 
        }
        if(sz - par[u] > sz / 2) is_centroid = false; 
        if(is_centroid) centroid.push_back(u); 
        return;
    }

    int dfs3(int u, int p) { 
        int ret = 1; 
        map<int, int>gg; 
        for(auto &v : g[u]) if (v != p) { 
            gg[label[v]] = v; 
        }    
        for(const auto [x, y] : gg) { 
            ret += dfs3(y, u); 
        }
        return ret; 
    }

    int doit(void) {
        dfs2(0, -1, n - 1);
        int root = centroid[0]; 
        if(sz(centroid) % 2 == 0) { 
            root = n - 1; 
            int a = centroid[0], b = centroid[1]; 
            g[a].erase(find(g[a].begin(), g[a].end(), b)); 
            g[b].erase(find(g[b].begin(), g[b].end(), a)); 
            g[root].push_back(a); 
            g[a].push_back(root); 
            g[root].push_back(b); 
            g[b].push_back(root); 
        } 
        dfs(root, -1);
        return dfs3(root, -1) - (sz(centroid) % 2 == 0); 
    }
};

int main(void) { 
    ios_base::sync_with_stdio(0);
    cin.tie(0); 
    int n; 
    cin >> n; 
    vector<vector<int>>g(n + 1); 
    for(int i = 0, u, v; i < n - 1; i++) { 
        cin >> u >> v;
        g[--u].push_back(--v);
        g[v].push_back(u); 
    }
    Tree tree(g); 
    cout << tree.doit() << '\n'; 
    return 0;
}