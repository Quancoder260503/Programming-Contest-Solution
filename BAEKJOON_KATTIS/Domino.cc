#include "bits/stdc++.h"
#pragma GCC optimize("Ofast")
using namespace std;
#define lint long long
const int M = 3001;
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
signed main(void)
{
    int n, K;
    cin >> n >> K;
    vector<vector<int>> g(n, vector<int>(n));
    lint ans = 0;
    vector<vector<pair<int, int>>> at(M);
    vector<int> occ;
    int N = n * n;
    MinCostFlow mcf(N + 3);
    int src = N;
    int fsrc = N + 1;
    int sink = N + 2;
    const int dx[4] = {-1, 1, 0, 0};
    const int dy[4] = {0, 0, -1, 1};
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> g[i][j];
            ans += g[i][j];
        }
    }
    auto to = [&](int i, int j)
    {
        return i * n + j;
    };
    auto inside = [&](int r, int c)
    {
        return (0 <= r && r < n && 0 <= c && c < n);
    };
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i > 0)
            {
                occ.push_back(g[i][j] + g[i - 1][j]);
                at[g[i][j] + g[i - 1][j]].push_back({to(i, j), to(i - 1, j)});  
            }
            if(j > 0)
            {
                occ.push_back(g[i][j] + g[i][j - 1]);
                at[g[i][j] + g[i][j - 1]].push_back({to(i, j), to(i, j - 1)});
            }
        }
    }
    vector<vector<int>>vis(n, vector<int>(n)); 
    sort(occ.begin(), occ.end());
    occ.erase(unique(occ.begin(), occ.end()), occ.end());
    int choice = 70;
    reverse(occ.begin(), occ.end());
    for (auto val : occ)
    {
        for (int i = 0; i < at[val].size(); i++)
        {
            auto [x, y] = at[val][i];
            vis[x / n][x % n] = vis[y / n][y % n] = 1;
            choice--;
            if(choice == 0) goto doit; 
        }
    }
doit: 
    // Only choose 8 times so we only need to consider roughly 32 heavies edge
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if ((i + j) & 1)
            {
                if (vis[i][j])
                {
                    mcf.addEdge(fsrc, to(i, j), 1, -g[i][j]);
                    for (int k = 0; k < 4; k++)
                    {
                        int px = i + dx[k];
                        int py = j + dy[k];
                        if (inside(px, py) && vis[px][py])
                        {
                            mcf.addEdge(to(i, j), to(px, py), 1, 0);
                        }
                    }
                }
            }
            else
            {
                if (vis[i][j])
                {
                    mcf.addEdge(to(i, j), sink, 1, -g[i][j]);
                }
            }
        }
    }
    mcf.addEdge(src, fsrc, K, 0);
    ans += mcf.minCostFlow(src, sink).second;
    cout << ans << '\n';
    return 0;
}