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
    pair<vector<int>, vector<vector<int>>> build_scc_dag()
    {
        vector<int> sz(scc.size());
        std::vector<std::vector<int>> dag(scc.size());
        for (int u = 0; u < n; u++)
        {
            int x = comp_ids[u];
            sz[x]++;
            for (int v : g[u])
            {
                int y = comp_ids[v];
                if (x != y)
                {
                    dag[x].push_back(y);
                }
            }
        }
        return {sz, dag};
    }
};
signed main(void)
{
    int n, K;
    cin >> n >> K;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; i++)
    {
        int to;
        cin >> to;
        adj[--to].push_back(i);
    }
    DirectedDfs dfs(adj);
    auto [_, __] = dfs.build_scc_dag();
    vector<vector<int>> dag(__.begin(), __.end());
    vector<int> sz(_.begin(), _.end());
    int N = sz.size();
    vector<vector<bool>> dyn(N, vector<bool>(K + 1, 0));
    vector<bool> vis(N);
    vector<bool> dp(K + 1);
    function<void(int)> doit;
    vector<int> topo;
    doit = [&](int u) -> void
    {
        vis[u] = 1;
        dyn[u][sz[u]] = 1;
        for (auto v : dag[u])
        {
            doit(v);
            for (int ku = K; ku >= 0; ku--)
            {
                for (int kv = 0; kv <= ku; kv++)
                {
                    dyn[u][ku] = dyn[u][ku] | (dyn[u][ku - kv] & dyn[v][kv]);
                }
            }
        }
    };
    vector<int> deg(N, 0);
    for (int i = 0; i < N; i++)
    {
        for (auto v : dag[i])
        {
            deg[v]++;
        }
    }
    dp[0] = 1;
    for (int i = 0; i < N; i++)
    {
        if (vis[i] || deg[i] > 0) continue;
        doit(i);
        for (int j = K; j >= 0; j--)
        {
            for (int k = 0; k <= j; k++)
            {
                dp[j] = dp[j] | (dp[j - k] & dyn[i][k]);
            }
        }
    }
    for (int i = K; i >= 0; i--)
    {
        if (dp[i])
        {
            cout << i << '\n';
            break;
        }
    }
    return 0;
}
/*
    We have a DAG with only thousand nodes -> since deg_in[v] = 1,
    the graph after construction will be a tree :)))
    Dyn[u][sz] = is it possible to select k nodes from the substree of u
*/