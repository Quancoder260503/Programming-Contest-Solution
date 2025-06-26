#include "bits/stdc++.h"
using namespace std;
#define MAXN (int) 1e3 + 1
#define lint long long
#define inf (lint)1e17 + 10
#define vi vector<lint>
int c[MAXN][MAXN]; 
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
    void conn(int u, int v, lint cap, lint cost)
    {
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
    lint mincost(int K, int src, int sink)
    {
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
        return flow < K ? -1 : cost;
    }
};
signed main(void)
{
    int n; 
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
         for(int j = 1; j <= n; j++)
         {
             scanf("%d", &c[i][j]); 
         }
    }
    MinCostFlow mcf; 
    mcf.init(2 * n + 2); 
    for(int i = 1; i <= n; i++)
    {
         mcf.conn(0, i, 1, 0);
         mcf.conn(n + i, 2 * n + 1, 1, 0); 
         for(int j = 1; j <= n; j++)
         {
             mcf.conn(i, n + j, 1, c[i][j]); 
         }
    }
    printf("%lld\n", mcf.mincost(n, 0, 2 * n + 1));
    /* 
    for(int i = 0; i < (int) mcf.edges.size(); i++)
    {
        if(mcf.edges[i].cap == 0 && mcf.edges[i].from != 0 & mcf.edges[i].to != 2 * n + 1 && mcf.edges[i].cost > 0)
         {
             printf("%d %d\n", mcf.edges[i].from, mcf.edges[i].to - n);
         }
    }
    */
    return 0;
}