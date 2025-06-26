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
    int N, H, K;
    // create a graph of h layer
    while(cin >> N >> K >> H && N)
    {
        ++H; 
        vector<vector<int>>g(N, vector<int>(N)); 
        for(int i = 0; i < N; i++) for(int j = 0; j < N; j++) cin >> g[i][j]; 
        auto in = [&](int i, int j, int k)
        {
            return k * N * N + i * N + j; 
        };
        auto out = [&](int i, int j, int k)
        {
            return N * N * H + k * N * N + i * N + j;
        };
        MaxFlow mf(2 * N * N * H + 2); 
        int src  = 2 * H * N * N; 
        int sink = 2 * H * N * N + 1; 
        for(int i = 0; i < K; i++)
        {
            int r, c; 
            cin >> r >> c;  
            mf.addEdge(src, in(r, c, 0), 1); 
            mf.addEdge(in(r, c, 0), out(r, c, 0), 1); 
        }
        const int dx[5] = {0, 0, 0, -1, 1}; 
        const int dy[5] = {0, 1, -1, 0, 0}; 
        for(int k = 1; k < H; k++) 
        {
            int h; 
            cin >> h; 
            for(int i = 0; i < N; i++) for(int j = 0; j < N; j++)
            {
                if(k == H - 1)
                {
                    mf.addEdge(out(i, j, k), sink, 1); 
                }
                mf.addEdge(in(i, j, k), out(i, j, k), 1); 
                for(int _ = 0; _ < 5; _++)
                {
                    int px = dx[_] + i;
                    int py = dy[_] + j;
                    if (0 <= px && px < N && 0 <= py && py < N && g[px][py] > h)
                    {
                        mf.addEdge(out(i, j, k - 1), in(px, py, k), 1);
                    }
                }
            }
        }
        cout << mf.getMaxFlow(src, sink) << '\n'; 
    }
    return 0;
}