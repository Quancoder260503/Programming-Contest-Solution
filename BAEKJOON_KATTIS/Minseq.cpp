#include "bits/stdc++.h"
using namespace std;
int n, g, r, c, q;
using lint = long long;
const lint INF = 4e18;
const int MAXN = (int)2e5 + 10;
struct Edge
{
    int u, v;
    lint cost;
    Edge(int _u, int _v, lint _cost) : u(_u), v(_v), cost(_cost){};
};
pair<bool, vector<lint>> ford_bellman(int n, int start, int target, const vector<Edge> &edges)
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
    bool good = 1;
    for (int i = 0; i < n; i++)
    {
        good = good & (cur_f[i] == f[i]);
    }
    return {good, f};
}
signed main(void)
{
    cin >> n >> q;
    vector<Edge> edge;
    for (int i = 0; i < q; i++)
    {
        int l, r;
        lint x, y;
        cin >> x >> y >> l >> r;
        edge.push_back(Edge(x, y + 1, r));
        edge.push_back(Edge(y + 1, x, -l));
    }
    for (int i = 1; i <= n; i++)
    {
        edge.push_back(Edge(i + 1, i, 0));
    }
    int N = n + 2;
    auto [good, dist] = ford_bellman(N, N - 1, -1, edge);
    if (!good)
    {
        puts("-1");
        return 0;
    }
    vector<lint> ans;
    for (int i = 1; i <= n; i++)
    {
        ans.push_back(dist[i + 1] - dist[i]);
    }
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }
    cout << '\n';
    return 0;
}