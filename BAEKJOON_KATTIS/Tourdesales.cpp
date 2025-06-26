#include "bits/stdc++.h"
using namespace std;
#define MAXN 1500000
#define lint long long
#define mp make_pair
#define vi vector<int>
#define pii pair<int, int>
#define x first
#define y second
typedef pair<long long, long long> Vec;
const lint inf = 1e14;
typedef long double ldb;
const int mod = 1e9 + 7;
const double eps = 1e-10;
int n, k;
using Point = Vec;
vector<Point> tour[MAXN];
struct MinCostFlow
{
    struct Edge
    {
        int from, to;
        lint cap;
        double cost;
        Edge(int _from, int _to, lint _cap, double _cost) : from(_from), to(_to), cap(_cap), cost(_cost) {}
    };
    int N;
    vector<Edge> edges;
    vector<vi> adj, radj;
    void init(int n)
    {
        N = n;
        adj.assign(N, vector<int>());
    }
    void conn(int u, int v, lint cap, double cost)
    {
        adj[u].push_back((int)edges.size());
        edges.push_back(Edge(u, v, cap, cost));
        adj[v].push_back(-(int)edges.size());
        edges.push_back(Edge(v, u, 0, -cost));
        return;
    }
    void spfa(int src, vector<double> &dist, vector<int> &fa)
    {
        vector<bool> inq(N, 0);
        queue<int> q;
        fill(dist.begin(), dist.end(), inf);
        fill(fa.begin(), fa.end(), -1);
        dist[src] = 0;
        q.push(src);
        inq[src] = true;
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
    double mincost(int K, int src, int sink)
    {
        lint flow = 0;
        double cost = 0;
        vector<double> dist(N);
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
        return cost;
    }
};
double tsp(const vector<Point> &pset)
{
    int N = pset.size() - 1;
    vector<vector<double>> dp(N, vector<double>((1 << N), inf));
    vector<vector<double>> dist(N + 1, vector<double>(N + 1, 0));
    for (int i = 0; i < N + 1; i++)
    {
        for (int j = i + 1; j < N + 1; j++)
        {
            dist[i][j] = hypot(pset[i].x - pset[j].x, pset[i].y - pset[j].y);
            dist[j][i] = dist[i][j];
        }
    }
    for (int i = 0; i < N; i++)
    {
        dp[i][(1 << i)] = dist[N][i];
    }
    for (int mask = 0; mask < (1 << N); mask++)
    {
        for (int i = 0; i < N; i++)
        {
            if (mask & (1 << i))
            {
                for (int j = 0; j < N; j++)
                {
                    if (mask & (1 << j))
                        continue;
                    if (dp[j][mask | (1 << j)] > dp[i][mask] + dist[i][j])
                    {
                        dp[j][mask | (1 << j)] = dp[i][mask] + dist[i][j];
                    }
                }
            }
        }
    }
    double ans = 1e9;
    for (int i = 0; i < N; i++)
    {
        ans = min(ans, dp[i][(1 << N) - 1] + dist[N][i]);
    }
    return ans;
}
signed main(void)
{
    scanf("%d", &n);
    double resb, resa;
    for (int i = 0; i < n; i++)
    {
        int m;
        scanf("%d", &m);
        for (int j = 0; j < m; j++)
        {
            int tx, ty;
            scanf("%d %d", &tx, &ty);
            tour[i].push_back(mp(tx, ty));
        }
        resb += tsp(tour[i]);
    }
    MinCostFlow mcf;
    mcf.init(n + 2);
    int src = n;
    int sink = n + 1;
    for (int i = 0; i < n / 2; i++)
    {
        mcf.conn(src, i, 1, 0);
    }
    for (int i = n / 2; i < n; i++)
    {
        mcf.conn(i, sink, 1, 0);
    }
    for (int i = 0; i < n / 2; i++)
    {
        vector<Point> pset(tour[i].begin(), tour[i].end());
        for (int j = n / 2; j < n; j++)
        {
            pset.insert(pset.end(), tour[j].begin(), tour[j].end());
            double curr = tsp(pset);
            mcf.conn(i, j, 1, curr);
            while (pset.size() > tour[i].size())
                pset.pop_back();
        }
    }
    resa = mcf.mincost(mod, src, sink);
    printf("%.7lf %.7lf\n", resb, resa);
    return 0;
}