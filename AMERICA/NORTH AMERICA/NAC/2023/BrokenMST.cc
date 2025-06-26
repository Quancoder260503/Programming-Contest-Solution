#include "bits/stdc++.h"

using namespace std;

int main(void)
{
    int n, m;
    cin >> n >> m;
    vector<int>fa(n); 
    vector<int>marka(m), markb(m); 
    function<int(int)>find = [&](int u){ return fa[u] == u ? u : fa[u] = find(fa[u]); }; 
    auto kruskal = [&](vector<tuple<int, int, int, int>> edge)
    {
        sort(edge.begin(), edge.end());
        iota(fa.begin(), fa.end(), 0);
        int ctr = 0;   
        for(auto [_, id, u, v] : edge)
        {
            if(find(u) == find(v)) continue;
            fa[find(u)] = find(v); 
            markb[id] = 1; 
        }
        return;
    };
    vector<tuple<int, int, int, int>> edge;
    int cost = 0; 
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v; 
        edge.push_back({w, i, u, v});
    }
    fill(marka.begin(), marka.begin() + n - 1, 1);
    kruskal(edge); 
    vector<pair<int, int>>ret; 
    for(int i = 0; i < n - 1; i++) if(!markb[i])
    {
        iota(fa.begin(), fa.end(), 0); 
        for(int j = 0; j < m; j++) if(i != j && marka[j])
        {
            auto [_, id, u, v] = edge[j]; 
            if(find(u) == find(v)) continue; 
            fa[find(u)] = find(v); 
        }
        for(int j = n - 1; j < m; j++) if(markb[j])
        {
            auto [_, id, u, v] = edge[j]; 
            if(find(u) == find(v)) continue; 
            fa[find(u)] = find(v); 
            ret.push_back({i, j}); 
            marka[i] = markb[j] = 0; 
            marka[j] = 1; 
            break; 
        }
    } 
    cout << ret.size() << '\n'; 
    for(auto [u, v] : ret) cout << u + 1 << " " << v + 1 << '\n'; 
    return 0;
}