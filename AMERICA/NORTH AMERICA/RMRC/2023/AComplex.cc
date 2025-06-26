#include "bits/stdc++.h"

using namespace std;

struct DirectedDfs
{
    vector<vector<pair<int, int>>> g;
    int n;
    vector<int> num, low, current, S;
    int counter;
    vector<int> comp_ids;
    vector<vector<int>> scc;

    DirectedDfs(const vector<vector<pair<int, int>>> &_g) : g(_g), n(g.size()),
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
        for (auto [v, _] : g[u])
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
    int get_min()
    {
        vector<vector<pair<int, int>>> dag(scc.size());
        vector<int>dist(scc.size(), 0); 
        vector<int>deg(scc.size(), 0); 
        for (int u = 0; u < n; u++)
        {
            int x = comp_ids[u];
            for (auto [v, w] : g[u])
            {
                int y = comp_ids[v];
                if (x != y)
                {
                    deg[y]++; 
                    dag[x].push_back({y, w});
                }
            }
        }
        queue<int>q; 
        for(int i = 0; i < scc.size(); i++) if(!deg[i])
        {
            q.push(i); 
        }
        while(q.size())
        {
            int u = q.front(); 
            q.pop(); 
            for(auto [v, w] : dag[u])
            {
                dist[v] = max(dist[v], dist[u] + w); 
                deg[v]--; 
                if(!deg[v]) q.push(v); 
            }
        }
        return *max_element(dist.begin(), dist.end()) + 1; 
    }
};

int main(void)
{
    map<string, int>str;
    int N, M, ctr = 0; 
    cin >> N >> M; 
    vector<pair<int, int>>edge, edge2; 
    for(int i = 0; i < N; i++)
    {
        string U, V; 
        cin >> U >> V; 
        if(str.count(U) == 0) str[U] = ctr++; 
        if(str.count(V) == 0) str[V] = ctr++;
        edge.push_back({str[U], str[V]}); 
    }
    for (int i = 0; i < M; i++)
    {
        string U, V;
        cin >> U >> V;
        if (str.count(U) == 0) str[U] = ctr++;
        if (str.count(V) == 0) str[V] = ctr++;
        edge2.push_back({str[U], str[V]});
    }
    vector<vector<pair<int, int>>>g(ctr); 
    for(auto [U, V] : edge)
    {
        g[U].push_back({V, 0}); 
    }
    for(auto [U, V] : edge2)
    {
        g[U].push_back({V, 1}); 
    }
    DirectedDfs strc(g); 
    cout << strc.get_min() << " " << strc.scc.size() << '\n'; 
    return 0; 
}