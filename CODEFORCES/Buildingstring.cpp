#include "bits/stdc++.h"
using namespace std;
#define MAXN 1000005
#define lint long long
#define inf (lint)1e17 + 10
#define MAXALPHA 26
char s[MAXN];
int arr[MAXN];
int mcap[MAXN]; 
int dp[MAXN][MAXALPHA + 1]; 
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
signed main(void)
{
    scanf(" %s", &s); 
    int n = strlen(s);
    for(int i = 0; i < n ; i++)
    {
         arr[s[i] - 'a' + 1] += 1; 
    }
    int q; 
    scanf("%d", &q);
    for(int i = 1; i <= q; i++)
    {
         char t[MAXN];  
         scanf("%s%d", &t, mcap + i); 
         for(int j = 0; j < strlen(t); j++)
         {
             dp[i][t[j] - 'a' + 1] += 1; 
         }
    }
    MinCostFlow mcf;
    mcf.init(MAXALPHA + q + 2); 
    for(int i = 1; i <= MAXALPHA; i++)
    {
         if(!arr[i]) continue; 
         mcf.conn(0, i, arr[i], 0);
         for(int j = 1; j <= q; j++)
         {
             if(!dp[j][i]) continue; 
             mcf.conn(i, j + MAXALPHA, dp[j][i], j); 
         } 
    }
    int sink = MAXALPHA + q + 1; 
    for(int i = 1; i <= q; i++)
    {
         mcf.conn(i + MAXALPHA, sink, mcap[i], 0); 
    }
    printf("%lld\n", mcf.mincost(n, 0, sink));
    return 0;
}