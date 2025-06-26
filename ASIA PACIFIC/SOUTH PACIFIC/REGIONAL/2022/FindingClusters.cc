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
    void build_scc_dag(void)
    {
        vector<int>deg(scc.size());
        vector<vector<int>>comp(scc.size());
        vector<int>rate(scc.size(), n + 1);  
        for (int u = 0; u < n; u++)
        {
            int x = comp_ids[u];
            rate[x] = min(rate[x], u); 
            comp[x].push_back(u); 
            for (int v : g[u])
            {
                int y = comp_ids[v];
                if (x != y)
                {
                    deg[x]++; 
                }
            }
        }
        pair<int, int> ret;
        for (int i = 0; i < scc.size(); i++) if (deg[i] == 0)
        {
                ret = max(ret, {rate[i], i});
        }
        int node = ret.second;
        for (auto c : comp[node])
            cout << c + 1 << " ";
        cout << '\n';
        return; 
    }
};

int main(void)
{
    int n; 
    cin >> n; 
    vector<vector<int>>g(n); 
    for(int i = 0; i < n; i++) {
        int m, x; 
        cin >> m; 
        for(int j = 0; j < m; j++) { 
            cin >> x; 
            g[i].push_back(--x); 
        }
    }
    DirectedDfs scc(g); 
    scc.build_scc_dag(); 
    return 0; 
}