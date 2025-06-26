#include "bits/stdc++.h"
using namespace std;
const int inf = 1000000000;
const int MAXN = 2000;
int n, m, h;
int cost[MAXN];
struct Edge
{
    int from, to;
    long long flow, cap;
    Edge(int _from, int _to, long long _flow, long long _cap) : from(_from), to(_to), flow(_flow), cap(_cap) {}
};
struct MaxFlow
{
    int N;
    vector<Edge> edges;
    vector<vector<int>> adj;
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
    void addEdge(int u, int v, long long flow)
    {
        // cout << u << " " << v << endl;
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
        // cout << s << " " << t << " " << flow << endl;
        for (; cur[s] != adj[s].end(); cur[s]++)
        {
            Edge &E = edges[*cur[s]];
            if (dist[E.to] != dist[s] + 1 || E.flow == E.cap)
                continue;
            long long df = dfs(E.to, t, min(flow, E.cap - E.flow));
            if (df)
            {
                // cout << E.from << " " << E.to << " " << E.flow << " " << E.cap << endl;
                E.flow += df;
                edges[*cur[s] xor 1].flow -= df;
                return df;
            }
        }
        return 0;
    }
    long long getMaxFlow(int s, int t)
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
int to(int i, int j)
{
    return (i - 1) * m + j;
}
bool inside(int i, int j)
{
    return (1 <= i && i <= n && 1 <= j && j <= m);
}
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
char g[MAXN][MAXN];
signed main(void)
{
    cin >> m >> n >> h;
    int sx, sy;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> g[i][j];
            if (g[i][j] == 'B')
            {
                sx = i, sy = j;
            }
        }
    }
    int N = n * m;
    MaxFlow mf;
    mf.init(2 * N + 3);
    int src = to(sx, sy);
    int sink = 2 * N + 1;
    mf.addEdge(sink, sink + 1, inf);
    mf.addEdge(src, src + N, inf);
    for (int i = 0; i < h; i++)
    {
        cin >> cost[i];
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (g[i][j] != 'B')
            {
                int weight = (g[i][j] == '.' ? inf : cost[g[i][j] - 'a']);
                mf.addEdge(to(i, j), to(i, j) + N, weight);
            }
            for (int k = 0; k < 4; k++)
            {
                int px = dx[k] + i;
                int py = dy[k] + j;
                if (inside(px, py))
                {
                    mf.addEdge(to(i, j) + N, to(px, py), inf);
                }
                else
                {
                    // cout << i << " " << j << " " << px << " " << py << " " << to(i, j) + N << " " << sink << endl;
                    mf.addEdge(to(i, j) + N, sink, inf);
                    mf.addEdge(sink + 1, to(i, j), inf);
                }
            }
        }
    }
    int ans = mf.getMaxFlow(src, sink + 1);
    cout << (ans >= (int)1e9 ? -1 : ans) << '\n';
    return 0;
}