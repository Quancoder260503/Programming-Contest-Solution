#include "bits/stdc++.h"
using namespace std;
#define lint long long
const int MAXN = 2000;
const int INF = 1000000000;
const int inf = 1e8;
int n, m;
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
       //cout << s << " " << t << " " << flow << endl;
        if (s == t)
            return flow;
        for (; cur[s] != adj[s].end(); cur[s]++)
        {
            Edge &E = edges[*cur[s]];
            if (dist[E.to] != dist[s] + 1 || E.flow == E.cap) continue;
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
            while (long long df = dfs(s, t, INF))
            {
                ans += df;
            }
        }
        return ans;
    }
};
int arr[MAXN];
int src, sink;
signed main(void)
{
    cin >> n >> m;
    cin >> src >> sink;
    MaxFlow max_flow;
    max_flow.init(2 * n + 2);
    // DFS to see how many edges can be connected with src and sink
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
        max_flow.addEdge(i, n + i, arr[i]);
    }
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v;
        //cout << u << " " << v << endl;
        max_flow.addEdge(n + v, u, inf);
        max_flow.addEdge(n + u, v, inf);
    }
    max_flow.maxflow(src, sink + n);
    max_flow.bfs(src, sink + n); 
    for (int i = 1; i <= n; i++)
    {
        //cout << max_flow.dist[i] << " " << max_flow.dist[n + i] << endl;
        if (max_flow.dist[i] >= 0 && max_flow.dist[n + i] < 0)
        {
            cout << i << " ";
        }
        if (max_flow.dist[i] < 0 && max_flow.dist[n + i] >= 0)
        {
            cout << i << " ";
        }
    }
    cout << '\n';
    return 0;
}
// Remember if we want the Flow to be distinc, connect it to itself