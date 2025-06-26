#include "bits/stdc++.h"
using namespace std;
#define lint long long
const int MAXN = 2000;
template <class Flow = lint, class Cost = lint>
struct MinCostFlow
{
    const Flow INF_FLOW = 1000111000;
    const Cost INF_COST = 1000111000111000LL;

    int n, t, S, T;
    Flow totalFlow;
    Cost totalCost;
    vector<int> last, visited;
    vector<Cost> dis;
    struct Edge
    {
        int to;
        Flow cap;
        Cost cost;
        int next;
        Edge(int _to, Flow _cap, Cost _cost, int _next) : to(_to), cap(_cap), cost(_cost), next(_next) {}
    };
    vector<Edge> edges;

    MinCostFlow(int _n) : n(_n), t(0), totalFlow(0), totalCost(0), last(n, -1), visited(n, 0), dis(n, 0)
    {
        edges.clear();
    }

    int addEdge(int from, int to, Flow cap, Cost cost)
    {
        edges.push_back(Edge(to, cap, cost, last[from]));
        last[from] = t++;
        edges.push_back(Edge(from, 0, -cost, last[to]));
        last[to] = t++;
        return t - 2;
    }

    pair<Flow, Cost> minCostFlow(int _S, int _T)
    {
        S = _S;
        T = _T;
        SPFA();
        while (1)
        {
            while (1)
            {
                std::fill(visited.begin(), visited.end(), 0);
                if (!findFlow(S, INF_FLOW))
                    break;
            }
            if (!modifyLabel())
                break;
        }
        return make_pair(totalFlow, totalCost);
    }

private:
    void SPFA()
    {
        std::fill(dis.begin(), dis.end(), INF_COST);
        priority_queue<pair<Cost, int>> Q;
        Q.push(make_pair(dis[S] = 0, S));
        while (!Q.empty())
        {
            int x = Q.top().second;
            Cost d = -Q.top().first;
            Q.pop();
            // For double: dis[x] > d + EPS
            if (dis[x] != d)
                continue;
            for (int it = last[x]; it >= 0; it = edges[it].next)
                if (edges[it].cap > 0 && dis[edges[it].to] > d + edges[it].cost)
                    Q.push(make_pair(-(dis[edges[it].to] = d + edges[it].cost), edges[it].to));
        }
        Cost disT = dis[T];
        for (int i = 0; i < n; i++)
        {
            dis[i] = disT - dis[i];
        }
    }

    Flow findFlow(int x, Flow flow)
    {
        if (x == T)
        {
            totalCost += dis[S] * flow;
            totalFlow += flow;
            return flow;
        }
        visited[x] = 1;
        Flow now = flow;
        for (int it = last[x]; it >= 0; it = edges[it].next)
            // For double: fabs(dis[edges[it].to] + edges[it].cost - dis[x]) < EPS
            if (edges[it].cap && !visited[edges[it].to] && dis[edges[it].to] + edges[it].cost == dis[x])
            {
                Flow tmp = findFlow(edges[it].to, min(now, edges[it].cap));
                edges[it].cap -= tmp;
                edges[it ^ 1].cap += tmp;
                now -= tmp;
                if (!now)
                    break;
            }
        return flow - now;
    }

    bool modifyLabel()
    {
        Cost d = INF_COST;
        for (int i = 0; i < n; i++)
            if (visited[i])
                for (int it = last[i]; it >= 0; it = edges[it].next)
                    if (edges[it].cap && !visited[edges[it].to])
                        d = min(d, dis[edges[it].to] + edges[it].cost - dis[i]);

        // For double: if (d > INF_COST / 10)     INF_COST = 1e20
        if (d == INF_COST)
            return false;
        for (int i = 0; i < n; i++)
            if (visited[i])
                dis[i] += d;
        return true;
    }
};
int a[MAXN];
int b[MAXN];
int ca[MAXN][MAXN];
int cb[MAXN][MAXN];
int n, msb;
void solve()
{
    msb = 13;
    int N = n * msb;
    MinCostFlow mcf(2 * N + 3);
    auto to = [&](int i, int j)
    {
        return i * msb + j;
    };
    int src = 2 * N + 1;
    int sink = 2 * N + 2;
    int in, out;
    in = out = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        for (int j = 0; j < msb; j++)
        {
            ca[i][j] = ((a[i] & (1 << j)) > 0);
            in += ca[i][j];
            if (ca[i][j])
            {
                mcf.addEdge(src, to(i, j), 1, 0);
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        cin >> b[i];
        for (int j = 0; j < msb; j++)
        {
            cb[i][j] = ((b[i] & (1 << j)) > 0);
            out += cb[i][j];
            if (cb[i][j])
            {
                mcf.addEdge(to(i, j) + N, sink, 1, 0);
            }
        }
    }
    for (int fx = 0; fx < n; fx++)
    {
        for (int fy = 0; fy < msb; fy++)
        {
            if (ca[fx][fy])
            {
                for (int ex = 0; ex < n; ex++)
                {
                    for (int ey = 0; ey < msb; ey++)
                    {
                        if (cb[ex][ey])
                        {
                            int cost = abs(fx - ex) + abs(fy - ey);
                            mcf.addEdge(to(fx, fy), to(ex, ey) + N, 1, cost);
                        }
                    }
                }
            }
        }
    }
    auto [flow, cost] = mcf.minCostFlow(src, sink);
    if (in == flow && out == flow)
    {
        cout << cost << '\n';
    }
    else
    {
        puts("Impossible");
    }
    return;
}
signed main(void)
{
    while (cin >> n)
    {
        if(n == 0) break;
        solve();
    }
    return 0;
}