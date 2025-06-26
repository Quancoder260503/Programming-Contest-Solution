#include "bits/stdc++.h"

using namespace std;

template <class Flow = int64_t, class Cost = int64_t>
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
int main(void)
{
    int tc; 
    cin >> tc; 
    for(int _ = 0; _ < tc; _++) {
        int n, p; 
        cin >> n >> p; 
        vector<vector<int>>cost(n, vector<int>(n, 0)), dem(n, vector<int>(n, 0)), oo(n, vector<int>(n, 0));
        vector<int>offs(n); 
        for(int i = 0; i < n - 1; i++) for(int j = i + 1; j < n; j++) {
            cin >> cost[i][j]; 
        }
        for(int i = 0; i < n - 1; i++) for(int j = i + 1; j < n; j++) {
            cin >> dem[i][j]; 
        }
        for(int i = 0; i < n - 1; i++) for(int j = i + 1; j < n; j++)  {
            cin >> oo[i][j]; 
        }
        map<pair<int, int>, int>idx;
        int nodes = 0; 
        for(int i = 0; i < n; i++) for(int j = i + 1; j < n; j++) {
            idx[{i, j}] = nodes++; 
        }
        int src = nodes + n;
        int sink = nodes + n + 1;  
        MinCostFlow mcf(nodes + n + 2); 
        for(int i = 0; i < n - 1; i++) for(int j = i + 1; j < n; j++) {
            mcf.addEdge(src, idx[{i, j}], dem[i][j], 0);
            mcf.addEdge(idx[{i, j}], nodes + i, dem[i][j], -cost[i][j]); 
            mcf.addEdge(idx[{i, j}], nodes + j, dem[i][j], 0); 
            mcf.addEdge(nodes + j, sink, dem[i][j], 0); 
        }
        for(int i = 0; i < n - 1; i++) for(int j = i + 1; j < n; j++) for(int k = i; k < j; k++)
        {
            offs[k] += oo[i][j]; 
        }
        for(int i = 0; i < n - 1; i++)
        {
            mcf.addEdge(nodes + i, nodes + i + 1, p - offs[i], 0); 
        }
        cout << -mcf.minCostFlow(src, sink).second << '\n'; 
    }
    return 0;
}