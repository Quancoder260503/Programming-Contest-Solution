#include "bits/stdc++.h"
using namespace std;
#define lint long long
const int INF = 1e9;
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
struct edge
{
    int u, v, w;
    edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w){};
};
signed main(void)
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<edge> Edge;
    int N = 2 * n + k;
    MinCostFlow mcf(N + 3);
    int src = N;
    int fsrc = N + 1;
    int sink = N + 2;
    vector<int> fa(n);
    vector<int> comp(n, 0);
    fill(comp.begin(), comp.end(), 1);
    iota(fa.begin(), fa.end(), 0);
    function<int(int)> find;
    vector<vector<pair<int, int>>> adj(n);
    find = [&](int u) -> int
    {
        return u == fa[u] ? u : fa[u] = find(fa[u]);
    };
    auto cmp = [&](const edge &a, const edge &b)
    {
        return a.w < b.w;
    };
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        Edge.push_back(edge(u, v, w));
    }
    sort(Edge.begin(), Edge.end(), cmp);
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        mcf.addEdge(k + i, k + n + i, 1, 0);
    }
    for (int i = 0; i < Edge.size(); i++)
    {
        auto [u, v, w] = Edge[i];
        int fu = find(u), fv = find(v);
        if (fu == fv) continue;
        if (comp[fu] < comp[fv])
        {
            swap(fu, fv);
            swap(u, v);
        }
        comp[fv] += comp[fu];
        fa[fu] = fv;
        ans += w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    if (*max_element(comp.begin(), comp.end()) < n)
    {
        puts("-1");
        return 0;
    }
    function<void(int, int)> dfs;
    dfs = [&](int u, int p) -> void
    {
        for (auto [v, cost] : adj[u])
        {
            if (v == p) continue;
            mcf.addEdge(v + k + n, sink, 1, -cost);
            mcf.addEdge(v + k + n, u + k, 1, 0);
            dfs(v, u);
        }
    };
    mcf.addEdge(k + n, sink, 1, -INF); 
    dfs(0, -1);
    for (int i = 0; i < k; i++)
    {
        int sz, to;
        cin >> sz;
        mcf.addEdge(fsrc, i, 1, 0);
        for (int j = 0; j < sz; j++)
        {
            cin >> to;
            --to;
            mcf.addEdge(i, k + to, 1, 0);
        }
    }
    mcf.addEdge(src, fsrc, k, 0);
    auto [flow, cost] = mcf.minCostFlow(src, sink);
    cout << (flow == k ? ans + cost + INF: -1) << '\n';
    return 0;
}
// Only consider MST edges 
// Reduce to the problem : Maximize the total weight of (K - 1) cut that split the MST into 
// components each conquered by a different King's Guard