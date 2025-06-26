#include "bits/stdc++.h"
using namespace std;
#define lint long long
const lint inf = 1e17;
struct MinCostFlow
{
    struct Edge
    {
        int from, to;
        lint cap, cost;
        Edge(int _from, int _to, lint _cap, lint _cost) : from(_from), to(_to), cap(_cap), cost(_cost) {}
    };
    int N;
    vector<Edge> edges;
    vector<vector<lint>> adj, radj;
    void init(int n)
    {
        N = n;
        adj.assign(N, vector<lint>());
        // radj.assign(N, vector<lint>());
    }
    void addEdge(int u, int v, lint cap, lint cost)
    {
        adj[u].push_back((int)edges.size());
        edges.push_back(Edge(u, v, cap, cost));
        adj[v].push_back(-(int)edges.size());
        edges.push_back(Edge(v, u, 0, -cost));
        return;
    }
    void spfa(int src, vector<lint> &dist, vector<int> &fa)
    {
        vector<bool> inq(N, 0);
        queue<int> q;
        fill(dist.begin(), dist.end(), inf);
        fill(fa.begin(), fa.end(), -1);
        dist[src] = 0;
        q.push(src);
        inq[src] = 1;
        while (q.size())
        {
            int u = q.front();
            q.pop();
            inq[u] = false;
            for (int i = 0; i < adj[u].size(); i++)
            {
                int v = adj[u][i];
                const Edge e = (v < 0 ? edges[-v] : edges[v]);
                if (e.cap > 0 && dist[e.to] > dist[e.from] + e.cost)
                {
                    dist[e.to] = dist[e.from] + e.cost;
                    fa[e.to] = v;
                    if (!inq[e.to])
                    {
                        inq[e.to] = 1;
                        q.push(e.to);
                    }
                }
            }
        }
    }
    pair<lint, lint> mincost(int K, int src, int sink)
    {
        lint flow = 0;
        lint cost = 0;
        vector<lint> dist(N);
        vector<int> fa(N);
        while (flow < K)
        {
            spfa(src, dist, fa);
            if (dist[sink] == inf)
            {
                break;
            }
            lint f = K - flow;
            int cur = sink;
            while (cur != src)
            {
                Edge e = (fa[cur] < 0 ? edges[-fa[cur]] : edges[fa[cur]]);
                f = min(f, e.cap);
                cur = e.from;
            }
            cur = sink;
            flow += f;
            cost += f * dist[sink];
            while (cur != src)
            {
                if (fa[cur] < 0)
                {
                    edges[-fa[cur]].cap -= f;
                    edges[-fa[cur] - 1].cap += f;
                }
                else
                {
                    edges[fa[cur]].cap -= f;
                    edges[fa[cur] + 1].cap += f;
                }
                cur = fa[cur] < 0 ? edges[-fa[cur]].from : edges[fa[cur]].from;
            }
        }
        return {flow, cost};
    }
};
const int MAXN = 20;
char g[MAXN][MAXN];
char gt[MAXN][MAXN];
signed main(void)
{
    int T, n, m, F, C;
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        cin >> n >> m >> F >> C;
        int N = n * m;
        auto to = [&](int i, int j)
        {
            return i * m + j;
        };
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cin >> g[i][j];
            }
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cin >> gt[i][j];
            }
        }
        auto solve = [&](int fl)
        {
            MinCostFlow mcf;
            mcf.init(N + 3);
            int src = N + 1;
            int sink = N + 2;
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {
                    if (g[i][j] == 'G' && gt[i][j] == 'M')
                    {
                        mcf.addEdge(to(i, j), sink, 1, 0);
                    }
                    else if (g[i][j] == 'M' && gt[i][j] == 'G')
                    {
                        mcf.addEdge(src, to(i, j), 1, 0);
                    }
                }
            }
            for (int fx = 0; fx < n; fx++)
            {
                for (int fy = 0; fy < m; fy++)
                {
                    if (g[fx][fy] == 'M' && gt[fx][fy] == 'G')
                    {
                        for (int ex = 0; ex < n; ex++)
                        {
                            for (int ey = 0; ey < m; ey++)
                            {
                                if (g[ex][ey] == 'G' && gt[ex][ey] == 'M')
                                {
                                    int cost = abs(fx - ex) + abs(fy - ey);
                                    // cout << to(fx, fy) << " " << to(ex, ey) << '\n';
                                    mcf.addEdge(to(fx, fy), to(ex, ey), 1, cost);
                                }
                            }
                        }
                    }
                }
            }
            return mcf.mincost(fl, src, sink);
        };
        int f = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                f += (g[i][j] != gt[i][j]);
            }
        }
        lint ans = 1e12;
        for (int fl = 0; fl <= n * m; fl++)
        {

            auto [flow, cost] = solve(fl);
            if (fl == flow)
            {
                ans = min(ans, 1LL * (C * cost + (f - 2 * flow) * F));
            }
        }
        printf("Case #%d: %lld\n", t, ans);
    }
    return 0;
}
// Solve : we can consider the swap first then change the value later (The above solution is just brute force)
// Experience : we can combine pairity of two map 