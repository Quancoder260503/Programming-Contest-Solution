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
    pair<vector<int>, vector<std::vector<int>>> build_scc_dag()
    {
        std::vector<std::vector<int>> dag(scc.size());
        vector<int> comp(dag.size());
        for (int u = 0; u < n; u++)
        {
            int x = comp_ids[u];
            comp[x]++;
            for (int v : g[u])
            {
                int y = comp_ids[v];
                if (x != y)
                {
                    dag[x].push_back(y);
                }
            }
        }
        return {comp, dag};
    }
};
signed main(void)
{
    int n, m;
    int T;
    cin >> T;
    while (T--)
    {
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
        auto [comp, dag] = Dfs.build_scc_dag();
        if(dag.size() == 1) {cout << 0 << '\n'; continue;}
        vector<int> indeg(dag.size());
        vector<int> outdeg(dag.size());
        for (int i = 0; i < dag.size(); i++)
        {
            outdeg[i] = dag[i].size();
            for (auto v : dag[i])
            {
                indeg[v]++;
            }
        }
        int in, out; 
        in = out = 0;
        for (int i = 0; i < dag.size(); i++)
        {
            out  += (outdeg[i] == 0) ; 
            in   += (indeg[i] == 0) ;  
        }
        cout << max(out, in) << '\n'; 
    }
    return 0;
}