#include "bits/stdc++.h"

using namespace std;

const int64_t INF = 1e9;

struct MinCostFlow
{
    struct Edge
    {
        int from, to;
        int64_t cap, cost;
        Edge(int _from, int _to, int64_t _cap, int64_t _cost) : from(_from), to(_to), cap(_cap), cost(_cost) {}
    };
    int N;
    vector<Edge> edges;
    vector<vector<int>> adj, radj;
    void init(int n)
    {
        N = n;
        adj.assign(N, vector<int>());
    }
    void addEdge(int u, int v, int64_t cap, int64_t cost)
    {
        adj[u].push_back((int)edges.size());
        edges.push_back(Edge(u, v, cap, cost));
        adj[v].push_back(-(int)edges.size());
        edges.push_back(Edge(v, u, 0, -cost));
        return;
    }
    void spfa(int src, vector<int64_t> &dist, vector<int> &fa)
    {
        vector<bool> inq(N, 0);
        queue<int> q;
        fill(dist.begin(), dist.end(), INF);
        fill(fa.begin(), fa.end(), -1);
        dist[src] = 0;
        q.push(src);
        inq[src] = 1;
        while (q.size())
        {
            int u = q.front();
            q.pop();
            inq[u] = false;
            for (int i = 0; i < adj[u].size(); i++)
            {
                int v = adj[u][i];
                const Edge e = (v < 0 ? edges[-v] : edges[v]);
                if (e.cap > 0 && dist[e.to] > dist[e.from] + e.cost)
                {
                    dist[e.to] = dist[e.from] + e.cost;
                    fa[e.to] = v;
                    if (!inq[e.to])
                    {
                        inq[e.to] = 1;
                        q.push(e.to);
                    }
                }
            }
        }
    }
    pair<int, int64_t> mincost(int K, int src, int sink)
    {
        int64_t flow = 0;
        int64_t cost = 0;
        vector<int64_t> dist(N);
        vector<int> fa(N);
        while (flow < K)
        {
            spfa(src, dist, fa);
            if (dist[sink] == INF)
            {
                break;
            }
            int64_t f = K - flow;
            int cur = sink;
            while (cur != src)
            {
                Edge e = (fa[cur] < 0 ? edges[-fa[cur]] : edges[fa[cur]]);
                f = min(f, e.cap);
                cur = e.from;
            }
            cur = sink;
            flow += f;
            cost += f * dist[sink];
            while (cur != src)
            {
                if (fa[cur] < 0)
                {
                    edges[-fa[cur]].cap -= f;
                    edges[-fa[cur] - 1].cap += f;
                }
                else
                {
                    edges[fa[cur]].cap -= f;
                    edges[fa[cur] + 1].cap += f;
                }
                cur = fa[cur] < 0 ? edges[-fa[cur]].from : edges[fa[cur]].from;
            }
        }
        return {flow, cost};
    }
};

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    MinCostFlow mf;
    mf.init(2 * n + 2);
    int src = 2 * n;
    int sink = 2 * n + 1;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        mf.addEdge(src, i, a[i], 0);
    }
    for (int i = 0; i < n; i++)
    {
        cin >> b[i];
        mf.addEdge(n + i, sink, b[i], 0);
    }
    for (int i = 0; i < n; i++)
        for (int j = 0, cost; j < n; j++)
        {
            cin >> cost;
            mf.addEdge(i, n + j, 1, -cost);
        }
    int suma = accumulate(a.begin(), a.end(), 0);
    int sumb = accumulate(b.begin(), b.end(), 0);
    auto ret = mf.mincost(INF, src, sink);
    if (suma == sumb && suma == ret.first)
    {
        cout << -ret.second << '\n';
        vector<vector<char>> ret(n, vector<char>(n));
        for (int i = 0; i < n; i++)
        {
            for (auto e_id : mf.adj[i])
            {
                if (e_id < 0)
                    continue;
                auto e = mf.edges[e_id];
                if (e.to == src || e.to < n)
                    continue;
                ret[i][e.to - n] = (e.cap ? '.' : 'X');
            }
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                cout << ret[i][j];
            cout << '\n';
        }
    }
    else
        cout << -1 << '\n';
    return 0;
}