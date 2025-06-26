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
int n, t;
signed main(void)
{
    while (cin >> n)
    {
        if(n == 0) break; 
        vector<pair<int, int>> edge;
        string s;
        getline(cin, s);
        for (int i = 0; i < n; i++)
        {
            getline(cin, s);
            string acc;
            for (int at = 0; at < s.length(); at++)
            {
                if (s[at] == ' ')
                {
                    assert(acc != ""); 
                    edge.push_back({i, stoi(acc)});
                    acc = "";
                }
                else
                {
                    acc += s[at];
                }
            }
            if(acc == "") continue; 
            edge.push_back({i, stoi(acc)});
        }
        auto solve = [&](int s, int t)
        {
            MaxFlow mf(n + 2);
            int src = n;
            int sink = n + 1;
            mf.addEdge(src, s, INF);
            mf.addEdge(t, sink, INF);
            for (auto [u, v] : edge)
            {
                mf.addEdge(u, v, 1);
            }
            return mf.getMaxFlow(src, sink);
        };
        int ans = 0; 
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if(i == j) continue; 
                ans = max(ans, solve(i, j));
            }
        }
        cout << ans << '\n'; 
    }
    return 0;
}