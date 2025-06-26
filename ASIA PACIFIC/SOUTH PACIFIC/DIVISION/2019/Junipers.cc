#include "bits/stdc++.h"

using namespace std;

const int64_t INF = 1e18;

int N, G, R, C;

struct Edge {
    int u, v;
    int64_t cost;
    Edge(int _u, int _v, int64_t _cost) : u(_u), v(_v), cost(_cost) {}; 
}; //one-direction

vector<Edge>edges; 

std::pair<bool, vector<int64_t>>
ford_bellman(int n, int start, int target)
{
    int m = edges.size();
    std::vector<int64_t> f(n, INF);
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
    int good = 1; 
    for(int i = 0; i < n; i++)
    {
        good = good & (f[i] == cur_f[i]); 
    }
    return {good, f};
}
int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    while (cin >> N >> G >> R >> C) {
        for (int i = 0, x, y, l, r; i < R; i++) {
            cin >> x >> y >> l >> r;
            edges.push_back(Edge(x, y, -l));
            edges.push_back(Edge(y, x, r));
        }
        for (int i = 1; i <= N; i++) {
            edges.push_back(Edge(N + 1, i, G));
        } 
        auto [state, dist] = ford_bellman(N + 2, N + 1, -1); 
        if (!state) {
            puts("-1");
            return 0;
        }
        edges.clear(); 
        for (int i = 0, x, y, l, r; i < C; i++) {
            cin >> x >> y >> l >> r;
            edges.push_back(Edge(x, y, -l));
            edges.push_back(Edge(y, x, r));
        }
        for (int i = 1; i <= N; i++) {
            edges.push_back(Edge(N + 1, i, G));
        }
        auto [state2, dist2] = ford_bellman(N + 2, N + 1, -1);
        if (!state2) {
            puts("-1");
            return 0;
        }
        for (int i = 1; i <= N; i++) {
           cout << dist[i] << " " << dist2[i] << endl;
        }
    }
    return 0;
}