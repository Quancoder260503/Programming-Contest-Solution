#include "bits/stdc++.h"
using namespace std;
struct DirectedDfs
{
    vector<vector<int>> g;
    int n;
    vector<int> num, low, current, S;
    int counter;
    vector<int> comp_ids;
    vector<vector<int>> scc;

    DirectedDfs(const vector<vector<int>> &_g) : g(_g), n(g.size()),
                                                 num(n, -1), low(n, 0), current(n, 0), counter(0), comp_ids(n, -1)
    {
        for (int i = 0; i < n; i++)
        {
            if (num[i] == -1)
                dfs(i);
        }
    }

    void dfs(int u)
    {
        low[u] = num[u] = counter++;
        S.push_back(u);
        current[u] = 1;
        for (auto v : g[u])
        {
            if (num[v] == -1)
                dfs(v);
            if (current[v])
                low[u] = min(low[u], low[v]);
        }
        if (low[u] == num[u])
        {
            scc.push_back(vector<int>());
            while (1)
            {
                int v = S.back();
                S.pop_back();
                current[v] = 0;
                scc.back().push_back(v);
                comp_ids[v] = ((int)scc.size()) - 1;
                if (u == v)
                    break;
            }
        }
    }

    // build DAG of strongly connected components
    // Returns: adjacency list of DAG
    pair<vector<vector<int>>, vector<int>> build_scc_dag()
    {
        vector<vector<int>> dag(scc.size()), comp(scc.size());
        vector<int>idx(dag.size()); 
        for (int u = 0; u < n; u++)
        {
            int x = comp_ids[u];
            idx[x] = u; 
            for (int v : g[u])
            {
                int y = comp_ids[v];
                if (x != y)
                {
                    dag[x].push_back(y);
                }
            }
        }
        return {dag, idx};
    }
};
signed main(void)
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
    }
    DirectedDfs Dfs(adj);
    auto [dag, idx] = Dfs.build_scc_dag();
    if (dag.size() == 1)
    {
        cout << 0 << '\n';
        return 0; 
    }
    vector<int> indeg(dag.size());
    vector<int> outdeg(dag.size());
    vector<vector<int>>rdag(dag.size()); 
    for (int i = 0; i < dag.size(); i++)
    {
        outdeg[i] = dag[i].size();
        for (auto v : dag[i])
        {
            indeg[v]++;
            rdag[v].push_back(i); 
        }
    }
    int in = 0, out = 0; 
    vector<int>src, sink; 
    for(int i = 0; i < dag.size(); i++) {
        out += (outdeg[i] == 0);
        in  += (indeg[i] == 0);
        if(outdeg[i] == 0) sink.push_back(i); 
        if(indeg[i]  == 0) src.push_back(i); 
    }
    int fsink = false;
    bool rev = false; 
    if(src.size() > sink.size()) { 
        swap(src, sink);
        swap(rdag, dag); 
        swap(indeg, outdeg); 
        rev = true;  
    }
    vector<int>vis(dag.size(), false), used(dag.size(), false); 
    int nodes; 
    function<void(int)> dfs = [&](int u) {
        if(vis[u] || fsink) return; 
        vis[u] = true; 
        if(!outdeg[u]) { 
            fsink = true; 
            nodes = u; 
        }
        for(auto v : dag[u]) dfs(v); 
        return; 
    };
    int ret = 0;
    vector<int>osrc, osink; 
    vector<pair<int, int>>edge; 
    for(int i = 0; i < src.size(); i++) { 
        if(!vis[src[i]]) { 
            fsink = false, nodes = -1; 
            dfs(src[i]); 
            if(fsink) { 
                ret++; 
                osrc.push_back(src[i]) ; 
                osink.push_back(nodes); 
                used[src[i]] = used[nodes] = true; 
            }
        }
    }
    for(int i = 0; i < src.size(); i++) if(!used[src[i]]) { 
        osrc.push_back(src[i]); 
    }
    for(int i = 0; i < sink.size(); i++) if(!used[sink[i]]) { 
        osink.push_back(sink[i]); 
    }
    for(int i = 0; i < ret - 1; i++) { 
        edge.push_back({idx[osink[i]], idx[osrc[i + 1]]}); 
    }
    int diff = sink.size() - src.size();
    for(int i = 0; i + ret < src.size(); i++) {
        edge.push_back({idx[osink[i + ret]], idx[osrc[i + ret]]}); 
    }
    if(src.size() == sink.size()) { 
        edge.push_back({idx[osink[ret - 1]], idx[osrc[0]]});
    }
    else { 
        edge.push_back({idx[osink[ret - 1]], idx[osink[osink.size() - diff]]}); 
        for(int i = osink.size() - diff; i + 1 < osink.size(); i++) { 
            edge.push_back({idx[osink[i]], idx[osink[i + 1]]}); 
        }
        edge.push_back({idx[osink.back()], idx[osrc[0]]});
    }
    cout << edge.size() << '\n'; 
    for(auto [u, v] : edge) { 
        if(rev) cout << v + 1 << " " << u + 1 << '\n'; 
        else cout << u + 1 << " " << v + 1 << '\n'; 
    }
    return 0;
}