#include "bits/stdc++.h"
using namespace std;
#define MAXN 1000
#define lint long long
#define inf (int) 1e4 + 10
#define vi vector<lint> 
int a[MAXN]; 
int b[MAXN];
int ans[MAXN][MAXN]; 
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
signed main(void)
{
    int n, m;
    Dinic Di; 
    scanf("%d%d", &n, &m);
    Di.init(2 * n + 2);
    long long tota = 0;
    long long totb = 0;
    for(int i = 1; i <= n; i++)
    {
         scanf("%d", a + i);
         tota += a[i]; 
         Di.conn(0, i, a[i]);
    }
    for(int i = 1; i <= n; i++)
    {
         scanf("%d", b + i);
         Di.conn(n + i, 2 * n + 1, b[i]);
         totb += b[i]; 
         Di.conn(i, n + i, inf); 
    }
    for(int i = 0; i < m; i++)
    {
        int u, v; scanf("%d %d", &u, &v);
        Di.conn(u, n + v, inf); 
        Di.conn(v, u + n, inf); 
    }
    Di.maxflow(0, 2 * n + 1);
    long long currtot = 0; 
    for (int i = 0; i < (int)Di.edges.size(); i++)
    {
        if (Di.edges[i].to == 2 * n + 1 || Di.edges[i].from == 0) continue;
        if (Di.edges[i].to == 0 || Di.edges[i].from == 2 * n + 1) continue;
        int v = Di.edges[i].to;
        int u = Di.edges[i].from; 
        int f = Di.edges[i].flow; 
        if(f < 0) continue;
        currtot += f; 
        ans[u][v - n] = f; 
    }
    if(currtot != tota || currtot != totb)
    {
         puts("NO");
    }
    else
    {
        puts("YES");
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= n; j++)
            {
               printf("%d ", ans[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}