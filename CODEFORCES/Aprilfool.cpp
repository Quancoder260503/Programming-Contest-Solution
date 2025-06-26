#include "bits/stdc++.h"
using namespace std;
#define MAXN 1000005
#define lint long long
#define inf (lint)1e17 + 10
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
    vector<vector<int> > adj;
    vector<vector<int> > capacity;
    vector<vector<int> > costs;
    void init(int n)
    {
        N = n;
        adj.assign(N, vector<int>());
        capacity.assign(N, vector<int>(N, 0));
        costs.assign(N, vector<int>(N, 0));
    }
    void conn(int u, int v, lint cap, lint cost)
    {
        edges.push_back(Edge(u, v, cap, cost));
        return;
    }
    void spfa(int src, vector<lint> &dist, vector<int> &fa)
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
                if (capacity[u][v] > 0 && dist[v] > dist[u] + costs[u][v])
                {
                    dist[v] = dist[u] + costs[u][v];
                    fa[v] = u;
                    if (!inq[v])
                    {
                        inq[v] = 1;
                        q.push(v);
                    }
                }
            }
        }
    }
    lint mincost(int K, int src, int sink)
    {
        for (int i = 0; i < edges.size(); i++)
        {
            Edge e = edges[i];
            costs[e.from][e.to] = e.cost;
            costs[e.to][e.from] = -e.cost;
            capacity[e.from][e.to] = e.cap;
            adj[e.to].push_back(e.from);
            adj[e.from].push_back(e.to);
        }
        lint flow = 0;
        lint cost = 0;
        vector<lint> dist(N);
        vector<int> fa(N);
        while (flow < K)
        {
            spfa(src, dist, fa);
            if (dist[sink] == inf)
            {
                break;
            }
            int f = K - flow;
            int cur = sink;
            while (cur != src)
            {
                f = min(f, capacity[fa[cur]][cur]);
                cur = fa[cur];
            }
            cur = sink;
            flow += f;
            cost += f * dist[sink];
            while (cur != src)
            {
                capacity[fa[cur]][cur] -= f;
                capacity[cur][fa[cur]] += f;
                cur = fa[cur];
            }
        }
        return flow < K ? -1 : cost;
    }
};
int a[MAXN], b[MAXN];
signed main(void)
{
    int n, k;
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", a + i);
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", b + i);
    }
    MinCostFlow mcf;
    mcf.init(n + 3);
    int src = n + 1; 
    int sink = n + 2; 
    mcf.conn(src, 0, k, 0); 
    for (int i = 1; i <= n; i++)
    {
        mcf.conn(0, i, 1, a[i]);
        mcf.conn(i, sink, 1, b[i]);
        if(i + 1 <= n)
        {
             mcf.conn(i, i + 1, i, 0); 
        }
    }
    printf("%lld\n", mcf.mincost(k, n + 1, n + 2));
    return 0;
}