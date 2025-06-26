#include "bits/stdc++.h"
using namespace std;
#define N 1000005
#define MAXN 3005
int dp[N];
#define mp make_pair
#define pii pair<int, int>
vector<int> adj[N];
int fa[N];
int n, m;
int dist[MAXN];
int dep[MAXN];
int vis[MAXN];
int cnt[MAXN];
vector<pii> edge;
void dfs(int u)
{
    vis[u] = 1;
    for (int i = 0; i < adj[u].size(); i++)
    {
        int v = adj[u][i];
        if (vis[v])
        {
            if (fa[u] == v || dep[u] + 1 - dep[v] <= 1)
                continue;
            dp[v] = min(dp[v], dep[u] + 1 - dep[v]);
        }
        else
        {
            fa[v] = u;
            dep[v] = dep[u] + 1;
            dfs(v);
        }
    }
}
long long dist_calc(int src, int target)
{
    memset(dist, -1, sizeof(dist));
    memset(cnt, 0, sizeof(cnt));
    queue<int> q;
    q.push(src);
    dist[src] = 0;
    cnt[src] = 1;
    while (q.size())
    {
        int node = q.front();
        q.pop();
        for (int i = 0; i < adj[node].size(); i++)
        {
            int u = adj[node][i];
            if (dist[u] == -1)
            {
                dist[u] = dist[node] + 1;
                cnt[u] = cnt[node];
                q.push(u);
            }
            else if (dist[u] == dist[node] + 1)
            {
                cnt[u] += cnt[node];
            }
        }
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (dist[i] == target)
            ans += 1LL * cnt[i] * (cnt[i] - 1) / 2;
    }
    return ans;
}
long long dist_calc2(int src, int target)
{
    memset(dist, -1, sizeof(dist));
    memset(cnt, 0, sizeof(cnt));
    queue<int> q;
    q.push(src);
    dist[src] = 0;
    cnt[src] = 1;
    while (q.size())
    {
        int node = q.front();
        q.pop();
        for (int i = 0; i < adj[node].size(); i++)
        {
            int u = adj[node][i];
            if (dist[u] == dist[node] + 1)
            {
                cnt[u] += cnt[node];
            }
            else if (dist[u] == -1)
            {
                dist[u] = dist[node] + 1;
                cnt[u] = cnt[node];
                q.push(u);
            }
        }
    }
    long long ans = 0;
    for (int i = 0; i < edge.size(); i++)
    {
        int u = edge[i].first;
        int v = edge[i].second;
        if (dist[u] == target && dist[v] == target)
        {
            ans += 1LL * cnt[u] * cnt[v];
        }
    }
    return ans;
}
signed main(void)
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
        edge.push_back(mp(u, v));
    }
    fill(dp, dp + n + 1, INT_MAX);
    for (int i = 1; i <= n; i++)
    {
        memset(vis, 0, sizeof(vis));
        memset(dep, 0, sizeof(dep));
        dfs(i);
    }
    int ans = INT_MAX;
    for (int i = 1; i <= n; i++)
    {
        if (dp[i] < 1 || dp[i] == INT_MAX)
            continue;
        ans = min(ans, dp[i]);
    }
    long long res = 0;
    for (int i = 1; i <= n; i++)
    {
        int st = i;
        if (ans & 1)
            res += dist_calc2(st, (ans - 1) / 2);
        else
            res += dist_calc(st, ans / 2);
    }
    res = res / ans;
    printf("%lld\n", res);
    return 0;
}