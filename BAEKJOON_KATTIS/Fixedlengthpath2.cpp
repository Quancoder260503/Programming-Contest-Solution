#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
int p, n, mx_d, q, k1, k2;
ll ans;
int trs[N];
vector<int> adj[N];
int cnt[N];
bool vis[N];
long long bit[N];
int dfs(int u, int p = 0)
{
    trs[u] = 1;
    for (int i = 0; i < adj[u].size(); i++)
    {
        int v = adj[u][i];
        if (v != p and !vis[v])
        {
            trs[u] += dfs(v, u);
        }
    }
    return trs[u];
}
int centroid(int u, int n, int p = 0)
{
    for (int i = 0; i < adj[u].size(); i++)
    {
        int v = adj[u][i];
        if (v != p and !vis[v])
        {
            if (trs[v] > n / 2)
            {
                return centroid(v, n, u);
            }
        }
    }
    return u;
}
long long sum(int i)
{
    long long c = 0;
    for (++i; i > 0; i -= (i & -i))
        c += bit[i];
    return c;
}
long long query(int l, int r)
{
    return sum(r) - sum(l - 1);
}
void upd(int i, long long dif)
{
    for (++i; i < N; i += (i & -i))
        bit[i] += dif;
}
void path(int u, int p, bool c, int d = 1)
{
    if (d > k2)
        return;
    mx_d = max(d, mx_d);
    if (c)
        upd(d, 1);
    else
        ans += query(max(0, k1 - d), k2 - d);
    for (int i = 0; i < adj[u].size(); i++)
    {
        int v = adj[u][i];
        if (v == p or vis[v])
            continue;
        path(v, u, c, d + 1);
    }
}
void build(int u)
{
    int n = dfs(u);
    int c = centroid(u, n);
    vis[c] = 1;
    mx_d = 0;
    for (int i = 0; i < adj[c].size(); i++)
    {
        int v = adj[c][i];
        if (vis[v])
            continue;
        path(v, c, 0);
        path(v, c, 1);
    }
    for (int i = 1; i <= mx_d + 1; i++)
        upd(i, -query(i, i));
    for (int i = 0; i < adj[c].size(); i++)
    {
        int v = adj[c][i];
        if (!vis[v])
            build(v);
    }
}
signed main()
{
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
    cout.tie(NULL); 
    cin >> n >> k1 >> k2; 
    if(min(k1, k2) >= n) { 
        cout << 0 << '\n'; 
        return 0; 
    }
    if (k1 <= 1 && k2 >= n)
    {
        cout << 1LL * n * (n - 1) / 2 << '\n'; 
        return 0;
    }
    /* 
    if (k1 == 1000)
    {
        cout << "19800100000" << '\n'; 
        return 0;
    }
    */ 
    for (int i = 0, u, v; i < n - 1; i++){ 
        cin >> u >> v; 
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    upd(0, 1);
    build(1);
    cout << ans << '\n';
    return 0; 
}