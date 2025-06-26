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

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
    cout.tie(NULL); 
    int n, m; 
    cin >> n >> m;  
    vector<vector<int>>rg(m), g(n);  
    for(int i = 0, sz; i < m; i++) { 
        cin >> sz; 
        for(int j = 0, x; j < sz; j++) { 
            cin >> x; 
            g[--x].push_back(i); 
            rg[i].push_back(x); 
        }
    }
    MaxFlow mf(n + m + 2); 
    int src = n + m; 
    int sink = src + 1; 
    for(int i = 0; i < n; i++) { 
        double cap = 0; 
        for(auto v : g[i]) cap += 1.0 / ((int) rg[v].size()); 
        mf.addEdge(src, i, (int) ceil(cap)); 
    }
    for(int i = 0; i < n; i++) for(auto j : g[i]) { 
        mf.addEdge(i, n + j, 1); 
    }
    for(int i = 0; i < m; i++) { 
        mf.addEdge(n + i, sink, 1); 
    }
    int ret = mf.getMaxFlow(src, sink);
    if(ret < m) cout << -1 << '\n'; 
    else { 
        vector<int>res(m); 
        for(int i = 0; i < n; i++) { 
            for(auto idx : mf.g[i]) { 
                auto edge = mf.e[idx]; 
                if(edge.b != src && edge.b != sink && edge.flow > 0) { 
                    res[edge.b - n] = i; 
                }
            }
        }
        for(int i = 0; i < m; i++) cout << res[i] + 1 << '\n'; 
    }
    return 0; 
}