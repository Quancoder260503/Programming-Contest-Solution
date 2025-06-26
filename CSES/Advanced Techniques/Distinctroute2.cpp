#include "bits/stdc++.h"
using namespace std;
#define MAXN 1000005
#define lint long long
#define inf (lint)1e17 + 10
#define vi vector<int>
vector<int>comp[MAXN];
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
        adj.assign(N, vector<int>());
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
bool vis[MAXN];
MinCostFlow mcf;
void dfs(int u, int curr)
{
     comp[curr].push_back(u);
     for(int i = 0; i < (int) mcf.adj[u].size(); i++)
     {
         int v = mcf.adj[u][i];
         if(v < 0) continue;
         if(!vis[v] && mcf.edges[v].cap == 0)
         {
            vis[v] = 1; 
             dfs(mcf.edges[v].to, curr);
             break;
         }
     } 
}
signed main(void)
{
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    mcf.init(n + 1);
    for(int i = 0; i < m; i++)
    { 
         int u,v; scanf("%d %d", &u, &v);
         mcf.conn(u, v, 1, 1); 
    } 
    printf("%lld\n", mcf.mincost(k, 1, n)); 
    int sz = 0;
    for(int i = 0; i < k; i++)
    {
        dfs(1, sz);
        sz += 1;
    }
    for(int i = 0; i < k; i++)
    {
         printf("%d\n", (int) comp[i].size());
         for(int j = 0; j < (int) comp[i].size(); j++)
         {
             printf("%d ", comp[i][j]); 
         }
         printf("\n"); 
    }
    return 0;
}
