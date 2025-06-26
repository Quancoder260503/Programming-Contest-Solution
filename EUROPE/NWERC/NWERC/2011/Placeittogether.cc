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
    int n, m, tc;
    cin >> tc;
    for (int _ = 0; _ < tc; _++)
    {
        cin >> n >> m;
        vector<vector<char>> g(n, vector<char>(m));
        int w = 0, b = 0;
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) 
        {
            cin >> g[i][j];
            w += (g[i][j] == 'W');
            b += (g[i][j] == 'B');
        }
        auto idx = [&](int i, int j){ return i * m + j; };
        MaxFlow mf(2 * n * m + 2);
        int src =  2 * n * m;
        int sink = 2 * n * m + 1;
        const int dx[4] = {-1, 1, 0, 0};
        const int dy[4] = {0,  0, 1, -1};
        auto inside = [&](int i, int j){ return 0 <= i && i < n && 0 <= j && j < m; }; 
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++)
        {
            if (g[i][j] == 'B')
            {
                mf.addEdge(src, idx(i, j), 1);
                mf.addEdge(src, n * m + idx(i, j), 1);  
                for (int k = 0; k < 4; k++) 
                {
                    int px = dx[k] + i, py = dy[k] + j;
                    if (inside(px, py) && g[px][py] == 'W') 
                    {
                       if(k < 2) mf.addEdge(idx(i, j), idx(px, py), 1);
                       else      mf.addEdge(idx(i, j) + n * m, idx(px, py), 1);  
                    }
                }
            }
            else if(g[i][j] == 'W')
            {
                mf.addEdge(idx(i, j), sink, 1); 
            }
        }
        auto ret = mf.getMaxFlow(src, sink); 
        cout << (ret == 2 * b && ret == w ? "YES" : "NO") << '\n'; 
    }
    return 0;
}