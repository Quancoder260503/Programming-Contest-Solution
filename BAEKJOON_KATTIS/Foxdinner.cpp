#include "bits/stdc++.h"
using namespace std;
#define MAXN 100005
#define lint long long
#define inf (lint) 1e9 + 10
#define vi vector<lint>
bool vis[MAXN];  
int arr[MAXN];
int n;
struct Dinic
{
    struct Edge
    {
        int from, to;
        long long flow, cap;
        Edge(int _from, int _to, long long _flow, long long _cap) : from(_from), to(_to), flow(_flow), cap(_cap) {}
    };
    int N;
    vector<Edge> edges;
    vector<vector<int> > adj;
    vector<vector<int>::iterator> cur;
    void reset()
    {
        // cur.clear();
        edges.clear();
        for (int i = 0; i < N; i++)
            adj[i].clear();
    }
    void init(int _N)
    {
        N = _N;
        adj.resize(N);
        cur.resize(N);
    }
    vector<int> dist;
    void conn(int u, int v, long long flow)
    {
        adj[u].push_back(edges.size());
        edges.push_back(Edge(u, v, 0, flow));
        adj[v].push_back(edges.size());
        edges.push_back(Edge(v, u, 0, 0));
    }
    bool bfs(int s, int t)
    {
        dist = vector<int>(N, -1);
        queue<int> q;
        q.push(s);
        dist[s] = 0;
        for (int i = 0; i < N; i++)
            cur[i] = adj[i].begin();
        while (q.size())
        {
            int node = q.front();
            q.pop();
            for (int i = 0; i < adj[node].size(); i++)
            {
                const Edge &E = edges[adj[node][i]];
                int v = E.to;
                if (dist[v] < 0 && E.flow < E.cap)
                {
                    dist[v] = dist[node] + 1;
                    q.push(v);
                }
            }
        }
        return dist[t] + 1 > 0;
    }
    long long dfs(int s, int t, long long flow)
    {
        if (s == t)
            return flow;
        for (; cur[s] != adj[s].end(); cur[s]++)
        {
            Edge &E = edges[*cur[s]];
            if (dist[E.to] != dist[s] + 1 || E.flow == E.cap)
                continue;
            long long df = dfs(E.to, t, min(flow, E.cap - E.flow));
            if (df)
            {
                E.flow += df;
                edges[*cur[s] xor 1].flow -= df;
                return df;
            }
        }
        return 0;
    }
    long long maxflow(int s, int t)
    {
        long long ans = 0;
        while (bfs(s, t))
        {
            while (long long df = dfs(s, t, inf))
            {
                ans += df;
            }
        }
        return ans;
    }
};
Dinic dinic;
vector<int>comp[MAXN]; 
void dfs(int u, int id)
{
    comp[id].push_back(u); 
    vis[u] = 1;
    for(int i = 0; i < dinic.adj[u].size(); i++)
    {
         int curr = dinic.adj[u][i];
         if(dinic.edges[curr].to != 0 && dinic.edges[curr].to != n + 1)
         {
             if(!vis[dinic.edges[curr].to] && abs(dinic.edges[curr].flow) == 1)
             {
                 dfs(dinic.edges[curr].to, id); 
             }
         }
    }
}
signed main(void)
{
    scanf("%d", &n); 
    vis[1] = 1; 
    vector<int>even, odd;
    dinic.init(n + 2); 
    for(int i = 1; i < MAXN; i++)
    {
        if(vis[i]) continue; 
        for(int j = 2 * i; j < MAXN; j += i)
        {
             vis[j] = 1; 
        }
    }
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", arr + i); 
        if(arr[i] & 1) odd.push_back(i);
        else even.push_back(i); 
    }
    for(int i = 0; i < odd.size(); i++)
    {
         dinic.conn(0, odd[i], 2); 
    }
    for (int i = 0; i < even.size(); i++)
    {
         dinic.conn(even[i], n + 1, 2);
    }
    for(int i = 0; i < odd.size(); i++)
    {
        for(int j = 0; j < even.size(); j++)
        {
             int u = odd[i];
             int v = even[j];
             if(!vis[arr[u] + arr[v]])
             {
                dinic.conn(u, v, 1);
             }
        }
    }
    long long ans = dinic.maxflow(0, n + 1); 
    if(ans != n)
    {
         puts("Impossible");
         return 0;
    }
    memset(vis,0,sizeof(vis));
    int sz = 0;  
    for(int i = 1; i <= n; i++)
    {
        if(!vis[i])
        {
             dfs(i, sz);
             sz += 1;  
        }
    }
    printf("%d\n", sz);
    for(int i = 0; i < sz; i++)
    {
         printf("%d ",(int) comp[i].size());
         for(int j = 0; j < comp[i].size(); j++)
         {
             printf("%d ", comp[i][j]); 
         }
         printf("\n"); 
    }
    return 0;
}