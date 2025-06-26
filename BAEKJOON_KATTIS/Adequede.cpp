#include "bits/stdc++.h"
using namespace std;
#define double long double
#define lint long long
const int INF = 1e9;
template <class Flow = lint, class Cost = double>
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
        Cost dist = dis[T];
        for (int i = 0; i < n; i++)
        {
            dis[i] = dist - dis[i];
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
const int N = 700;
#define Point pair<int, int>
#define x first
#define y second
Point P[N];
int H[N];
int n, s, t;
double max_len;
int spring[N];
int town[N];
vector<pair<int, double>> adj[N];
double dist[N][N];
signed main(void)
{
    cin >> n >> s >> t >> max_len;
    for (int i = 0; i < n; i++)
    {
        cin >> P[i].x >> P[i].y >> H[i];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            dist[i][j] = INF;
            if (i == j)
                dist[i][j] = 0;
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            double cost = hypot(P[i].x - P[j].x, P[i].y - P[j].y, H[i] - H[j]);
            if (H[i] > H[j] && max_len > cost)
            {
                dist[i][j] = cost;
            }
        }
    }
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    MinCostFlow mcf(s + t + 2);
    int src = s + t;
    int sink = s + t + 1;
    for (int i = 0; i < s; i++)
    {
        cin >> spring[i];
        --spring[i];
        mcf.addEdge(src, i, 1, 0);
    }
    for (int i = 0; i < t; i++)
    {
        cin >> town[i];
        --town[i];
        mcf.addEdge(i + s, sink, 1, 0);
    }
    for (int i = 0; i < s; i++)
    {
        for (int j = 0; j < t; j++)
        {
            if (dist[spring[i]][town[j]] == INF)
                continue;
            // cout << spring[i] << "  " << s + town[j] << " " << dist[spring[i]][town[j]] << '\n';
            mcf.addEdge(i, s + j, 1, dist[spring[i]][town[j]]);
        }
    }
    auto [flow, cost] = mcf.minCostFlow(src, sink);
    if (flow == t)
    {
        cout << fixed << setprecision(10) << cost << '\n';
    }
    else
    {
        puts("IMPOSSIBLE");
    }
    return 0;
}