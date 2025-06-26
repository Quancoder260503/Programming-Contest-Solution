#include "bits/stdc++.h"
using namespace std;
#define lint long long
const int MAXN = 2000;
const lint inf = 1e9;
const int INF = 1000000000;
struct Edge
{
    int a, b, cap, flow;
};
struct MaxFlow
{
    int n, s, t;
    vector<int> d, ptr, q;
    vector<Edge> e;
    vector<vector<int>> g;

    MaxFlow(int _n) : n(_n), d(_n), ptr(_n), q(_n), g(_n)
    {
        e.clear();
        for (int i = 0; i < n; i++)
        {
            g[i].clear();
            ptr[i] = 0;
        }
    }

    void addEdge(int a, int b, int cap)
    {
        Edge e1 = {a, b, cap, 0};
        Edge e2 = {b, a, 0, 0};
        g[a].push_back((int)e.size());
        e.push_back(e1);
        g[b].push_back((int)e.size());
        e.push_back(e2);
    }
    int getMaxFlow(int _s, int _t)
    {
        s = _s;
        t = _t;
        int flow = 0;
        for (;;)
        {
            if (!bfs())
                break;
            std::fill(ptr.begin(), ptr.end(), 0);
            while (int pushed = dfs(s, INF))
                flow += pushed;
        }
        return flow;
    }

private:
    bool bfs()
    {
        int qh = 0, qt = 0;
        q[qt++] = s;
        std::fill(d.begin(), d.end(), -1);
        d[s] = 0;

        while (qh < qt && d[t] == -1)
        {
            int v = q[qh++];
            for (int i = 0; i < (int)g[v].size(); i++)
            {
                int id = g[v][i], to = e[id].b;
                if (d[to] == -1 && e[id].flow < e[id].cap)
                {
                    q[qt++] = to;
                    d[to] = d[v] + 1;
                }
            }
        }
        return d[t] != -1;
    }

    int dfs(int v, int flow)
    {
        if (!flow)
            return 0;
        if (v == t)
            return flow;
        for (; ptr[v] < (int)g[v].size(); ++ptr[v])
        {
            int id = g[v][ptr[v]],
                to = e[id].b;
            if (d[to] != d[v] + 1)
                continue;
            int pushed = dfs(to, min(flow, e[id].cap - e[id].flow));
            if (pushed)
            {
                e[id].flow += pushed;
                e[id ^ 1].flow -= pushed;
                return pushed;
            }
        }
        return 0;
    }
};
int n, m;
int to(int i, int j)
{
    return (i - 1) * m + j;
}
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, -1, 1};
char g[MAXN][MAXN];
bool valid(int i, int j)
{
    return (1 <= i && i <= n && 1 <= j && j <= m && g[i][j] != '.');
}
signed main(void)
{
    int tc = 0;
    map<char, int> fl;
    fl['C'] = 4;
    fl['N'] = 3;
    fl['O'] = 2;
    fl['H'] = 1;
    while (cin >> n >> m)
    {
        if (n == 0 && m == 0) break;
        tc++;
        MaxFlow dinic(n * m + 2);
        //memset(g, '0', sizeof(g));
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                cin >> g[i][j];
            }
        }
        int src = 0, sink = n * m + 1;
        int even, odd;
        even = odd = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (g[i][j] == '.')
                    continue;
                if ((i + j) % 2 == 0)
                {
                    dinic.addEdge(src, to(i, j), fl[g[i][j]]);
                    even += fl[g[i][j]];
                    for (int k = 0; k < 4; k++)
                    {
                        int px = i + dx[k];
                        int py = j + dy[k];
                        if (valid(px, py))
                        {
                            dinic.addEdge(to(i, j), to(px, py), 1);
                        }
                    }
                }
                else
                {
                    odd += fl[g[i][j]];
                    dinic.addEdge(to(i, j), sink, fl[g[i][j]]);
                }
            }
        }
        lint res = dinic.getMaxFlow(src, sink);
        printf("Molecule %d is ", tc);
        if (res == even && res == odd)
        {
            puts("valid.");
        }
        else
        {
            puts("invalid.");
        }
    }
    return 0;
}