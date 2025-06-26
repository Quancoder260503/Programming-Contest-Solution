#include "bits/stdc++.h"

using namespace std;

const int N = 200010;
const int INF = 1e8 + 5;

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
    while (cin >> n >> m)
    { 
        for(int i = 0; i < m; i++)
        {
            int U, V; 
            cin >> U >> V; 
            g[U].push_back(V + n); 
        }
        cout << n - hopcroftKarp() << '\n'; 
    }
    return 0;
}