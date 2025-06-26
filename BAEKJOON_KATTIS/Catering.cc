#include "bits/stdc++.h"
using namespace std;
#define lint long long
const lint INF = 1e12;
const int inf = 1e7;
#define vi vector<lint>
struct MinCostFlow
{
    struct Edge
    {
        int from, to;
        lint cap, cost;
        Edge(int _from, int _to, lint _cap, lint _cost) : from(_from), to(_to), cap(_cap), cost(_cost) {}
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
    void addEdge(int u, int v, lint cap, lint cost)
    {
        //cout << u << " " << v << " " << cap << '\n'; 
        adj[u].push_back((int)edges.size());
        edges.push_back(Edge(u, v, cap, cost));
        adj[v].push_back(-(int)edges.size());
        edges.push_back(Edge(v, u, 0, -cost));
        return;
    }
    void spfa(int src, vector<lint> &dist, vector<int> &fa)
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
    pair<int, lint> minCostFlow(int K, int src, int sink)
    {
        lint flow = 0;
        lint cost = 0;
        vector<lint> dist(N);
        vector<int> fa(N);
        while (flow < K)
        {
            spfa(src, dist, fa);
            if (dist[sink] == INF)
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
signed main(void)
{
    int n, k;
    cin >> n >> k;
    int src  = 2 * n + 1;
    int sink = 2 * n + 2;
    MinCostFlow mcf;
    mcf.init(2 * n + 3);
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            int x; cin >> x;
            mcf.addEdge(i, j + n, 1, x); 
        }
    }
    mcf.addEdge(src, 0, k, 0);
    for(int i = 1; i < n; i++)
    {
        mcf.addEdge(src, i, 1, 0); 
    }
    for(int i = 0; i < n; i++)
    {
        mcf.addEdge(i + n + 1, sink, 1, 0); 
    }
    auto [flow , cost] = mcf.minCostFlow(inf, src, sink); 
    cout << cost << '\n';
    return 0;
}