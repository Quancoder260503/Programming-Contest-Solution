#include "bits/stdc++.h"
using namespace std;
#define MAXN (int)1e5 + 10
const int inf = 1e9;
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
    cin >> n;
    Dinic dinic; 
    dinic.init(2 * n + 2); 
    int src = 2 * n; 
    int sink = 2 * n + 1;
    for (int i = 0; i < n; i++)
    {
        int sz;
        cin >> sz;
        for (int j = 0; j < sz; j++)
        {
            int to;
            cin >> to;
            dinic.conn(i, n + to, 1); 
        }
    }
    for(int i = 0; i < n; i++)
    {
         dinic.conn(src, i, 1);
         dinic.conn(i + n, sink, 1); 
    }
    cout << n - dinic.maxflow(src, sink) << '\n'; 
    return 0;
}