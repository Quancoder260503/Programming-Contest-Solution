#include "bits/stdc++.h"
using namespace std; 
#define MAXN 1000005
#define lint long long
#define inf (lint) 1e17 + 10
int cost[MAXN];
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
     int n; 
     scanf("%d", &n); 
     MinCostFlow mcf;
     mcf.init(2 * n + 2); 
     for(int i = 1; i <= 2 * n; i++)
     {
         string s; cin >> s; 
         for(int dist = 1; dist <= s.length(); dist++)
         {
             string curr = s.substr(0, dist); 
             int good = 1;
             for(int k = dist; k + dist <= s.length(); k += dist)
             {
                   string now = s.substr(k, dist);
                   if(now != curr)
                   {
                      good = 0; 
                      break; 
                   }
             }
             if(good)
             {
                 if(dist <= s.length() / 2 || dist == s.length()) 
                 {
                    cost[i] = dist;
                    break;
                 } 
             }
         } 
     }
     for(int i = 1; i <= n; i++)
     {
         mcf.conn(0, i, 1, 0); 
         mcf.conn(n + i, 2 * n + 1, 1, 0); 
         for(int j = n + 1; j <= 2 * n; j++)
         { 
              mcf.conn(i, j, 1, (cost[i] - cost[j]) * (cost[i] - cost[j])); 
         }
     }
     printf("%lld\n", mcf.mincost(n, 0, 2 * n + 1)); 
     return 0; 
}