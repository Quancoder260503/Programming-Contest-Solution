#include "bits/stdc++.h"
using namespace std;
const int INF = 1000000000;
struct Edge
{
    int a, b, cap, flow;
};
int n, s, t;
vector<int> d, ptr, q;
vector<Edge> e;
vector<vector<int>> g;

void init(int _n)
{
    n = _n;
    d.resize(_n);
    ptr.resize(_n);
    g.resize(_n);
    q.resize(_n);
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
int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int N;
    while (cin >> N)
    {
        int src = N;
        int sink = N + 1;
        init(N + 2);
        for (int i = 0; i < N; i++)
        {
            int x;
            cin >> x;
            if (x == 1)
                addEdge(src, i, INF);
            else if (x == 2)
                addEdge(i, sink, INF);
        }
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
            {
                int x;
                cin >> x;
                if (i == j)
                    continue;
                addEdge(i, j, x);
            }
        cout << getMaxFlow(src, sink) << '\n';
        for (int i = 0; i < N; i++)
            if (d[i] != -1)
                cout << i + 1 << ' ';
        cout << '\n';
        for (int i = 0; i < N; i++)
            if (d[i] == -1)
                cout << i + 1 << ' ';
        cout << '\n';
    }
    return 0;
}