#include "bits/stdc++.h"
using namespace std;
const int MAXN = 600;
const int inf = 1e9;
vector<int> adj[MAXN];
string s[MAXN];
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
int mod2[MAXN];
signed main(void)
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }
    int len = s[1].length();
    Dinic dinic;
    dinic.init(2 * n + 3);
    int src = 0;
    int sink = 2 * n + 1;
    for (int i = 1; i <= n; i++)
    {
        int inversions = 0;
        for (int j = 0; j < len; j++)
        {
            for (int l = 0; l < j; l++)
            {
                inversions += (s[i][j] < s[i][l]);
            }
            mod2[i] = inversions % 2;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (mod2[i])
            dinic.conn(src, i, 1);
        else
            dinic.conn(i, sink, 1);
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            int diff = 0;
            pair<int, int> dpos = make_pair(-1, -1);
            for (int k = 0; k < len; k++)
            {
                diff += (s[i][k] != s[j][k]);
                if (s[i][k] != s[j][k])
                {
                    if (dpos.first == -1)
                        dpos.first = k;
                    else if (dpos.second == -1)
                        dpos.second = k;
                }
            }
            if (diff == 2 && s[i][dpos.first] == s[j][dpos.second] && s[i][dpos.second] == s[j][dpos.first])
            {
                if (mod2[i])
                {
                    dinic.conn(i, j, inf);
                }
                else
                {
                    dinic.conn(j, i, inf);
                }
            }
        }
    }
    int ans = dinic.maxflow(src, sink);
    cout << max(ans, n - ans) << endl;
    return 0;
}