#include "bits/stdc++.h"

using namespace std;

#define double long double

const int N = 200010;
const int INF = 1e8 + 5;
const double EPS = 1e-6;

bool vis[N], vis2[N];
int n, m, where[N], match[N], dist[N], arr[N];
vector<int> g[N], h[N], paths[N], ord;
bool bfs()
{
    queue<int> q;
    for (int i = 1; i <= n; ++i)
    {
        if (!match[i])
            dist[i] = 0, q.emplace(i);
        else
            dist[i] = INF;
    }
    dist[0] = INF;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        if (!u)
            continue;
        for (int v : g[u])
        {
            if (dist[match[v]] == INF)
            {
                dist[match[v]] = dist[u] + 1,
                q.emplace(match[v]);
            }
        }
    }
    return dist[0] != INF;
}

bool dfs(int u)
{
    if (!u)
        return 1;
    for (int v : g[u])
    {
        if (dist[match[v]] == dist[u] + 1 and dfs(match[v]))
        {
            match[u] = v, match[v] = u;
            return 1;
        }
    }
    dist[u] = INF;
    return 0;
}

int hopcroftKarp()
{
    int ret = 0;
    while (bfs())
    {
        for (int i = 1; i <= n; ++i)
        {
            ret += !match[i] and dfs(i);
        }
    }
    return ret;
}
int main(void)
{
    double S, V;
    while (cin >> n >> m >> S >> V)
    {
        memset(dist, 0, sizeof(dist)); 
        memset(match, 0, sizeof(match)); 
        for(int i = 0; i < N; i++) g[i].clear(); 
        vector<double> sx(n), sy(n), rx(m), ry(m);
        for (int i = 0; i < n; i++) cin >> sx[i] >> sy[i];
        for (int i = 0; i < m; i++) cin >> rx[i] >> ry[i];
        auto sqr = [&](double x)
        {
            return x * x; 
        };
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++)
        {
            if (sqr(sx[i] - rx[j]) + sqr(sy[i] - ry[j]) <= sqr(S * V))
            {
                g[i + 1].push_back(j + n + 1);
            }
        }
        cout << n - hopcroftKarp() << '\n';
    }
    return 0;
}