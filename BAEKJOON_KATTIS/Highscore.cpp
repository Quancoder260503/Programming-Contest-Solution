#include "bits/stdc++.h"
using namespace std;
int n, g, r, c, q, m;
using lint = long long;
const lint INF = 4e18;
const int MAXN = (int)2e5 + 10;
struct Edge
{
    int u, v;
    lint cost;
    Edge(int _u, int _v, lint _cost) : u(_u), v(_v), cost(_cost){};
};
pair<bool, lint> ford_bellman(int n, int start, int target, const vector<Edge> &edges)
{
    int m = edges.size();
    vector<lint> f(n, INF);
    f[start] = 0;
    for (int turn = 0; turn < m; turn++)
    {
        for (auto [u, v, cost] : edges)
        {
            if (f[u] != INF && f[v] > f[u] + cost)
            {
                f[v] = f[u] + cost;
            }
        }
    }
    auto cur_f = f;
    for (int turn = 0; turn < m; turn++)
    {
        for (auto [u, v, cost] : edges)
        {
            if (f[u] != INF && f[v] > f[u] + cost)
            {
                f[v] = f[u] + cost;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (f[i] != cur_f[i])
        {
            f[i] = -INF;
        }
    }
    for (int turn = 0; turn < m; turn++)
    {
        for (auto [u, v, cost] : edges)
        {
            if (f[u] != INF && f[v] > f[u] + cost)
            {
                f[v] = f[u] + cost;
            }
        }
    }
    return {cur_f[target] == f[target], f[target]};
}
signed main(void)
{
    cin >> n >> m;
    vector<Edge>edge;
    for(int i = 0; i < m; i++)
    {
        int u, v; lint cost ; cin >> u >> v >> cost; 
        edge.push_back(Edge(u, v, -cost)); 
    }
    auto [F, dist] = ford_bellman(n + 1, 1, n, edge);
    cout << (F ? -dist : -1) << '\n'; 
    return 0;
}