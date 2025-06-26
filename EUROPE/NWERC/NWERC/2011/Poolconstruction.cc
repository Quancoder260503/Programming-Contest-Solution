#include "bits/stdc++.h"
using namespace std;
const int INF = 1000000000;
const int L = 10000000;
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
const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};
int main(void)
{
    int N, M, T;
    int D, F, B;
    cin >> T;
    while (T--)
    {
        cin >> M >> N;
        cin >> D >> F >> B;
        vector<vector<char>> g(N, vector<char>(M));
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
            {
                cin >> g[i][j];
            }
        int src = N * M;
        int sink = N * M + 1;
        MaxFlow mf(N * M + 2);
        auto to = [&](int i, int j)
        {
            return i * M + j;
        };
        int ret = 0;
        for (int i = 0; i < N; i++) for (int j = 0; j < M; j++)
        {
                if (i == 0 || j == 0 || i == N - 1 || j == M - 1)
                {
                    mf.addEdge(src, to(i, j), INF);
                }
                if (g[i][j] == '#') mf.addEdge(src, to(i, j),  D);
                if (g[i][j] == '.') mf.addEdge(to(i, j), sink, F);
                for (int dir = 0; dir < 4; dir++)
                {
                    int px = i + dx[dir];
                    int py = j + dy[dir];
                    if (0 < px && px < N && 0 < py && py < M)
                    {
                        mf.addEdge(to(i, j), to(px, py), B);
                    }
                }
        }
        ret += mf.getMaxFlow(src, sink);
        cout << ret << '\n';
    }
    return 0;
}