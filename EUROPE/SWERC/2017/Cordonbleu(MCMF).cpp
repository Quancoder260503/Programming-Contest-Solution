#include "bits/stdc++.h"
using namespace std;
const int MAXN = 2000;
#define lint long long
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
int n, m;
signed main(void)
{
    clock_t tStart = clock();
    cin >> n >> m;
    vector<pair<int, int>> cour, bottle;
    pair<int, int> res;
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        bottle.push_back({x, y});
    }
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        cour.push_back({x, y});
    }
    cin >> res.first >> res.second;
    MinCostFlow mcf(n + m + 3);
    int src = n + m + 1;
    int sink = n + m + 2;
    // Create a special node to represent the restaurant
    int special = n + m;
    mcf.addEdge(src, special, n - 1, 0);
    for (int i = 0; i < cour.size(); i++)
    {
        // cout << src << " " << i << " " << endl;
        mcf.addEdge(src, i, 1, 0);
    }
    for (int i = 0; i < bottle.size(); i++)
    {
        auto [x, y] = bottle[i];
        // cout << special << " " << i + m << " " << sink << endl;
        mcf.addEdge(special, i + m, 1, abs(res.first - x) + abs(res.second - y));
        mcf.addEdge(i + m, sink, 1, abs(x - res.first) + abs(y - res.second));
    }
    for (int i = 0; i < cour.size(); i++)
    {
        for (int j = 0; j < bottle.size(); j++)
        {
            auto [sx, sy] = cour[i];
            auto [ex, ey] = bottle[j];
            mcf.addEdge(i, m + j, 1, abs(sx - ex) + abs(sy - ey));
        }
    }
   auto [flow, cost] = mcf.minCostFlow(src, sink);
   // cout << cost << '\n';
   // printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
    return 0;
}