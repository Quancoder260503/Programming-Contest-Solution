#include "bits/stdc++.h"
using namespace std;
const int M = 16; 
const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {-1, 0, 1, 0};
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
    int N, M;
    while(cin >> N >> M)
    {
        auto to = [&](int i, int j)
        {
            return i * M + j;
        }; 
        int fin, fout; 
        fin = fout = 0; 
        vector<vector<string>> g(N, vector<string>(M));
        vector<vector<int>> cost(N * M, vector<int>(4, 0));
        int sz = 0; 
        vector<int>H(N * M); 
        vector<int>V(N * M); 
        for (int i = 0; i < N; i++) for (int j = 0; j < M; j++)
        {
            cin >> g[i][j];
            int ctr = 0; 
            for(int k = 0; k < g[i][j].size(); k++) ctr += (g[i][j][k] == '1'); 
            if(ctr == 2)
            {
                H[to(i, j)] = sz++; 
                V[to(i, j)] = sz++; 
            }
            else
            {
                H[to(i, j)] = V[to(i, j)] = sz++;             
            }
        }
        int src  = sz++; 
        int sink = sz++; 
        MinCostFlow mcf(sz); 
        for(int i = 0; i < N; i++) for(int j = 0; j < M; j++)
        {
            int ctr = 0;
            for (int k = 0; k < g[i][j].size(); k++) ctr += (g[i][j][k] == '1');
            if(ctr == 2)
            {
                for(int k = 0; k < 4; k++) cost[to(i, j)][k] = 3 * (g[i][j][k] == '0'); 
                if((i + j) % 2 == 0)
                {
                    mcf.addEdge(src, H[to(i, j)], 1, 0);
                    mcf.addEdge(src, V[to(i, j)], 1, 0); 
                    fin += 2; 
                }
                else 
                {
                    mcf.addEdge(H[to(i, j)], sink, 1, 0); 
                    mcf.addEdge(V[to(i, j)], sink, 1, 0); 
                    fout += 2; 
                }
            }
            else 
            {
                if(ctr == 1)
                {
                    int at = -1; 
                    for(int k = 0; k < 4; k++) 
                    {
                        if(g[i][j][k] == '1') at = k; 
                        cost[to(i, j)][k] = 3; 
                    }
                    cost[to(i, j)][at] = 0; 
                    cost[to(i, j)][at xor 2] = 6; 
                }
                else if(ctr == 3)
                {
                    int at = -1;
                    for (int k = 0; k < 4; k++)
                    {
                        if (g[i][j][k] == '0') at = k;
                        cost[to(i, j)][k] = 1;
                    }
                    cost[to(i, j)][at] = 4;
                    cost[to(i, j)][at xor 2] = -2;
                }
                if ((i + j) % 2 == 0)
                {
                    fin += ctr; 
                    mcf.addEdge(src, H[to(i, j)], ctr, 0);
                }
                else
                {
                    fout += ctr; 
                    mcf.addEdge(H[to(i, j)], sink, ctr, 0);
                }
            }
        }
        if(fin != fout)
        {
            cout << -1 << '\n'; 
            continue; 
        }
        for(int i = 0; i < N; i++) for(int j = 0; j < M; j++)
        {
            if((i + j) % 2 == 0)
            {
                if(i + 1 < N)
                {
                    int C = cost[to(i, j)][2] + cost[to(i + 1, j)][0];
                    mcf.addEdge(V[to(i, j)], V[to(i + 1, j)], 1, C); 
                }
                if(j + 1 < M)
                {
                    int C = cost[to(i, j)][1] + cost[to(i, j + 1)][3]; 
                    mcf.addEdge(H[to(i, j)], H[to(i, j + 1)], 1, C); 
                }
            }
            else 
            {
                if (i + 1 < N)
                {
                    int C = cost[to(i, j)][2] + cost[to(i + 1, j)][0];
                    mcf.addEdge(V[to(i + 1, j)], V[to(i, j)], 1, C);
                }
                if (j + 1 < M)
                {
                    int C = cost[to(i, j)][1] + cost[to(i, j + 1)][3];
                    mcf.addEdge(H[to(i, j + 1)], H[to(i, j)], 1, C);
                }
            }
        }
        auto ret = mcf.minCostFlow(src, sink);
        if(fin == ret.first) 
        {
            cout << ret.second / 3 << '\n'; 
        }
        else 
        {
            cout << -1 << '\n'; 
        }
    }
    return 0; 
}