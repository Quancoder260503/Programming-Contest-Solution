#include "bits/stdc++.h"
using namespace std;
const int mod = 1e9 + 7; 
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
    std::vector<std::vector<int>> build_scc_dag()
    {
        std::vector<std::vector<int>> dag(scc.size());
        for (int u = 0; u < n; u++)
        {
            int x = comp_ids[u];
            for (int v : g[u])
            {
                int y = comp_ids[v];
                if (x != y)
                {
                    dag[x].push_back(y);
                }
            }
        }
        return dag;
    }
};
int main(void)
{
    int N; 
    while(cin >> N)
    {
        vector<vector<int>>adj(N);
        for(int i = 0; i < N; i++)
        {
            int x;
            cin >> x; 
            --x; 
            adj[i].push_back(x); 
        }
        DirectedDfs scc(adj);
        auto dag = scc.build_scc_dag(); 
        N = dag.size(); 
        vector<vector<int>>rdag(N);
        for(int i = 0; i < N; i++) for(auto v : dag[i])
        {
            rdag[v].push_back(i); 
        }
        vector<int64_t>f(N, -1); 
        for(int i = 0; i < N; i++) if(rdag[i].size() == 0)
        {
            f[i] = 2; 
        }
        function<int64_t(int)>doit = [&](int u) -> int64_t 
        {
            if(f[u] != -1) return f[u];
            int64_t ret = 1;  
            for(auto v : rdag[u])
            {
                ret = ret * doit(v) % mod; 
            }
            return f[u] = (++ret) % mod; 
        }; 
        int64_t ret = 1;
        for(int i = 0; i < N; i++) if(dag[i].size() == 0)
        { 
            ret = ret % mod * doit(i) % mod;  
        }
        ret = (ret - 1 + mod) % mod;
        cout << ret << '\n'; 
    }
    return 0;
}