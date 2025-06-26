#include "bits/stdc++.h"
using namespace std;
#define M 2000
#define inf 10000000000000
int n, m;
char MAT[M][M];
struct Dinic
{
    struct Edge
    {
        int to;
        long long flow, cap;
        Edge(int _to, long long _flow, long long _cap) : to(_to), flow(_flow), cap(_cap) {}
    };
    int N;
    vector<Edge> edges;
    vector<vector<int> > adj;
    vector<vector<int>::iterator> cur;
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
        edges.push_back(Edge(v, 0, flow));
        adj[v].push_back(edges.size());
        edges.push_back(Edge(u, 0, 0));
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
int idx(int x, int y)
{
    return x * m + y;
}
signed main(void)
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> MAT[i][j];
        }
    }
    Dinic Di;
    Di.init(m * n + 10);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (MAT[i][j] == '#')
            {
                if (MAT[i + 1][j] == '#')
                {
                    Di.conn(idx(i + 1, j), idx(i, j), 1);
                }
                else
                {
                    Di.conn(m * n + 1, idx(i, j), 1);
                }
                if (MAT[i][j + 1] == '#')
                {
                    Di.conn(idx(i, j), idx(i, j + 1), 1);
                }
                else
                {
                    Di.conn(idx(i, j), n * m + 2, 1);
                }
            }
        }
    }
    printf("%lld\n", Di.maxflow(m * n + 1, m * n + 2));
}