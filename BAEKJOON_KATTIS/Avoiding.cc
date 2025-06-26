#include "bits/stdc++.h"

using namespace std;

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

int main(void)
{
    int N, F, M, P, T, S, R; 
    cin >> T;
    while(T--, cin >> N >> P >> F >> S >> M) 
    {
        --P; 
        S++; 
        auto to = [&](int t, int node)
        {
            return N * t + node; 
        }; 
        int src  = N * S + 1; 
        int sink = N * S + 2; 
        MaxFlow mf(N * S + 3); 
        mf.addEdge(src, to(0, P), F);
        for (int i = 0; i < M; i++)
        {
            int dst; 
            cin >> dst; 
            --dst; 
            mf.addEdge(to(S - 1, dst), sink, INF); 
        }
        cin >> R; 
        for(int i = 0; i < R; i++)
        {
            int U, V, C, Ts; 
            cin >> U >> V >> C >> Ts; 
            --U, --V; 
            for(int j = 0; j < S - Ts; j++) 
            {
                mf.addEdge(to(j, U), to(j + Ts, V), C); 
            }
        }
        for(int i = 0; i < N; i++) for(int j = 1; j < S; j++)
        {
            mf.addEdge(to(j - 1, i), to(j, i), INF); 
        }
        cout << mf.getMaxFlow(src, sink) << '\n'; 
    }
    return 0; 
}