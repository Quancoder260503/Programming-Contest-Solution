#include "bits/stdc++.h"
using namespace std;
#define lint long long
#define vi vector<lint>
const double inf = 1e9;
struct MinCostFlow
{
    struct Edge
    {
        int from, to;
        lint cap;
        double cost;
        Edge(int _from, int _to, lint _cap, double _cost) : from(_from), to(_to), cap(_cap), cost(_cost) {}
    };
    int N;
    vector<Edge> edges;
    vector<vi> adj, radj;
    void init(int n)
    {
        N = n;
        adj.assign(N, vector<lint>());
        // radj.assign(N, vector<lint>());
    }
    void addEdge(int u, int v, lint cap, double cost)
    {
        adj[u].push_back((int)edges.size());
        edges.push_back(Edge(u, v, cap, cost));
        adj[v].push_back(-(int)edges.size());
        edges.push_back(Edge(v, u, 0, -cost));
        return;
    }
    void spfa(int src, vector<double> &dist, vector<int> &fa)
    {
        vector<bool> inq(N, 0);
        queue<int> q;
        fill(dist.begin(), dist.end(), inf);
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
    pair<int, double> mincost(int K, int src, int sink)
    {
        lint flow = 0;
        double cost = 0;
        vector<double> dist(N);
        vector<int> fa(N);
        while (flow < K)
        {
            spfa(src, dist, fa);
            if (dist[sink] == inf)
            {
                break;
            }
            lint f = K - flow;
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
const int N = 700;
int n;
#define x first
#define y second
pair<int, int> P[N];
signed main(void)
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> P[i].x >> P[i].y;
    }
    MinCostFlow mcf;
    mcf.init(2 * n + 2);
    int src = 0;
    int sink = 2 * n + 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (P[i].y > P[j].y)
            {
                mcf.addEdge(i, j + n, 1, hypot(P[i].x - P[j].x, P[i].y - P[j].y));
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        mcf.addEdge(src, i, 2, 0);
        mcf.addEdge(i + n, sink, 1, 0);
    }
    auto [flow, cost] = mcf.mincost(inf, src, sink);
    cout << fixed << setprecision(10) << (flow == n - 1 ? cost : -1) << '\n';
    return 0;
}