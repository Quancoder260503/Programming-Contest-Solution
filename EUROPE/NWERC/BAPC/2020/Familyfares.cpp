#include "bits/stdc++.h"
using namespace std;
const int MAXN = (int)1e3 + 10;
#define mp make_pair
#define lint long long
const lint inf = 1e12;
#define pii pair<int, int>
lint dist[MAXN][MAXN];
vector<pii> adj2[MAXN];
vector<int> adj[MAXN];
lint opt[MAXN][MAXN];
bool vis[MAXN];
int n, m, p, c;
int st[MAXN];
int deg[MAXN];
bitset<MAXN> dp[MAXN];
vector<int> fa[MAXN][MAXN];
void djsktra(int src)
{
    using T = pair<lint, int>;
    priority_queue<T, vector<T>, greater<T> > pq;
    pq.push(mp(0, src));
    dist[src][src] = 0;
    while (pq.size())
    {
        int w = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if (dist[src][u] != w)
            continue;
        for (int i = 0; i < adj2[u].size(); i++)
        {
            int v = adj2[u][i].second;
            int cost = adj2[u][i].first;
            if (dist[src][v] > dist[src][u] + cost)
            {
                dist[src][v] = dist[src][u] + cost;
                fa[src][v].clear();
                fa[src][v].push_back(u);
                pq.push(mp(dist[src][v], v));
            }
            else if (dist[src][v] == dist[src][u] + cost)
            {
                fa[src][v].push_back(u);
            }
        }
    }
    return;
}
signed main(void)
{
    cin >> n >> m >> p >> c;
    for (int i = 1; i <= p; i++)
    {
        cin >> st[i];
    }
    for (int i = 1; i <= m; i++)
    {
        int u, v, cost;
        cin >> u >> v >> cost;
        adj2[u].push_back(mp(cost, v));
        adj2[v].push_back(mp(cost, u));
    }
    memset(dist, 63, sizeof(dist));
    for (int i = 1; i <= n; i++)
    {
        djsktra(i);
    }
    int root = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < fa[root][i].size(); j++)
        {
            int v = fa[root][i][j];
            deg[v]++;
            adj[i].push_back(v);
        }
    }
    for (int i = 1; i <= p; i++)
    {
        dp[st[i]][i] = 1;
    }
    queue<int> q;
    for (int i = 1; i <= n; i++)
    {
        if (deg[i] == 0)
            q.push(i);
    }
    while (q.size())
    {
        int u = q.front();
        q.pop();
        for (int i = 0; i < adj[u].size(); i++)
        {
            int v = adj[u][i];
            dp[v] |= dp[u];
            deg[v]--;
            if (!deg[v])
                q.push(v);
        }
    }
    lint ans = inf;
    for (int i = 1; i <= n; i++)
    {
        lint res = 0;
        for (int j = 1; j <= p; j++)
        {
            if (dp[i][j]) res += min(1LL * (c + dist[st[j]][i]), dist[st[j]][root]);
            else res += dist[st[j]][root];
        }
        ans = min(res, ans); 
    }
    cout << ans << '\n';
    return 0;
}
/*
        // mindist is fixed
        // Let S be the set of members travel by group -> min(k * mindist + sum(dist[1][u])) where S \ {u} = S
        // dist[i][j] = {consider the optimal options for the first ith people with exact j people form a group}
        // dist[i][j] = (dist[i - 1][j - 1] + min_dist,  dist[i - 1][j] + dist[1][i]);
*/