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
    int build_scc_dag() {
        vector<int>sz(scc.size()), par(scc.size()), ctr(scc.size()); 
        vector<vector<int>>comp(scc.size()); 
        iota(par.begin(), par.end(), 0); 
        function<int(int)>find = [&](int u) { 
            return par[u] == u ? u : par[u] = find(par[u]); 
        };
        for (int u = 0; u < n; u++) {
            int x = comp_ids[u];
            ctr[x]++; sz[x]++; 
        }
        for (int u = 0; u < n; u++) {
            int x = comp_ids[u];
            for (int v : g[u]) {
                int y = comp_ids[v];
                if (x != y) {
                    x = find(x), y = find(y);
                    if(x == y) continue; 
                    if(sz[x] < sz[y]) swap(x, y); 
                    par[y] = x; 
                    sz[x] += sz[y]; 
                }
            }
        }
        int ret = 0; 
        for(int i = 0; i < scc.size(); i++) comp[par[i]].push_back(i); 
        for(int i = 0; i < scc.size(); i++) if(par[i] == i) { 
            int flag = false; 
            for(auto c : comp[i]) { 
                if(ctr[c] > 1) { 
                    flag = true; 
                    break; 
                }
            }
            ret += (flag ? sz[i] : sz[i] - 1); 
        }
        return ret;
    }
};

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); 
    int n, m; 
    cin >> n >> m;
    vector<vector<int>>g(n); 
    for(int i = 0, u, v; i < m; i++) { 
        cin >> u >> v; 
        g[--u].push_back(--v); 
    }
    DirectedDfs scc(g);
    cout << scc.build_scc_dag() << '\n'; 
    return 0; 
}