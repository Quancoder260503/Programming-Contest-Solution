#include "bits/stdc++.h"
using namespace std;
const int N = 4e5 + 10;
const int mod = 1e9;
int n, q;
vector<int> adj[N];
int trs[N], dep[N];
int up[23][N];
int in[N], top[N], a[N];
int timer = 1;
int rig[N], lef[N], at[N];
struct node
{
    vector<int> doLeft;  // go from the left  side
    vector<int> doRight; // go from the right side
};
node operator+(const node &a, const node &b)
{
    node ret;
    ret.doLeft = a.doLeft;
    ret.doRight = b.doRight;
    for (auto value : b.doLeft)
    {
        if (value > ret.doLeft.back())
        {
            ret.doLeft.push_back(value);
        }
    }
    for (auto value : a.doRight)
    {
        if (value > ret.doRight.back())
        {
            ret.doRight.push_back(value);
        }
    }
    return ret;
}
node segtree[N * 4];
void build(int L, int R, int p = 1)
{
    if (L == R)
    {
        segtree[p].doLeft.push_back(a[at[L]]);
        segtree[p].doRight.push_back(a[at[L]]);
        return;
    }
    int mid = (L + R) / 2;
    build(L, mid, 2 * p);
    build(mid + 1, R, 2 * p + 1);
    segtree[p] = segtree[2 * p] + segtree[2 * p + 1];
}
int queryL(int L, int R, int &en, int l = 1, int r = n, int p = 1)
{
    if (L > r || R < l) return 0;
    if (L <= l && r <= R) 
    {
        int ret = segtree[p].doLeft.end() - upper_bound(segtree[p].doLeft.begin(), segtree[p].doLeft.end(), en); 
        if(ret) en = segtree[p].doLeft.back(); 
        return ret; 
    }
    int mid = (l + r) / 2;
    return queryL(L, R, en, l, mid, 2 * p) + queryL(L, R, en, mid + 1, r, 2 * p + 1);
}
int queryR(int L, int R, int &en, int l = 1, int r = n, int p = 1)
{
    if (L > r || R < l) return 0;
    if (L <= l && r <= R) 
    {
        int ret = segtree[p].doRight.end() - upper_bound(segtree[p].doRight.begin(), segtree[p].doRight.end(), en);
        if (ret) en = segtree[p].doRight.back();
        return ret;
    }
    int mid = (l + r) / 2;
    return queryR(L, R, en, mid + 1, r, 2 * p + 1) + queryR(L, R, en, l, mid, 2 * p);
}
long long dfs(int u, int p)
{
    trs[u] = 1;
    for (int i = 1; i < 23; i++)
    {
        up[i][u] = up[i - 1][up[i - 1][u]];
    }
    for (int i = 0; i < adj[u].size(); i++)
    {
        int v = adj[u][i];
        if (v == p) continue;
        dep[v] = dep[up[0][v] = u] + 1;
        trs[u] += dfs(v, u);
    }
    return trs[u];
}
void dfs_hld(int u, int anc)
{
    in[u] = timer++;
    at[in[u]] = u;
    top[u] = anc;
    int hchi = 0;
    int hsize = 0;
    for (int i = 0; i < adj[u].size(); i++)
    {
        int v = adj[u][i];
        if (v == up[0][u])
            continue;
        if (hsize < trs[v])
        {
            hsize = trs[v];
            hchi = v;
        }
    }
    if (hchi == 0) return;
    dfs_hld(hchi, anc);
    for (int i = 0; i < adj[u].size(); i++)
    {
        int v = adj[u][i];
        if (v == up[0][u] or v == hchi) continue;
        dfs_hld(v, v);
    }
}
int jump(int x, int d)
{
    for (int i = 0; i < 23; i++)
    {
        if ((d >> i) & 1)
            x = up[i][x];
    }
    return x;
}
int LCA(int a, int b)
{
    if (dep[a] < dep[b]) swap(a, b);
    a = jump(a, dep[a] - dep[b]);
    if (a == b)
        return a;
    for (int i = 22; i >= 0; i--)
    {
        int tA = up[i][a];
        int tB = up[i][b];
        if (tA != tB)
        {
            a = tA;
            b = tB;
        }
    }
    return up[0][a];
}
int path(int u, int v)
{
    int anc = LCA(u, v);
    vector<pair<int, int>> path;
    int en = 0; 
    while (top[u] != top[anc])
    {
        path.push_back({in[top[u]], in[u]});
        u = up[0][top[u]];
    }
    if (in[anc] <= in[u])
    {
        path.push_back({in[anc], in[u]});
    }
    int ret = 0;
    for (auto [L, R] : path)
    {
        ret = ret + queryR(L, R, en);
    }
    path.resize(0);
    while (top[v] != top[anc])
    {
        path.push_back({in[top[v]], in[v]});
        v = up[0][top[v]];
    }
    if (in[anc] <= in[v])
    {
        path.push_back({in[anc], in[v]});
    }
    reverse(path.begin(), path.end());
    for (auto [L, R] : path)
    {
        ret = ret + queryL(L, R, en);
    }
    return ret;
}
signed main(void)
{
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 0);
    dfs_hld(1, 1);
    build(1, n);
    int ans = 0;
    for (int i = 0; i < q; i++)
    {
        int u, v;
        cin >> u >> v;
        u = (u + ans) % n + 1;
        v = (v + ans) % n + 1;
        ans = path(u, v); 
        cout << ans << '\n';
    }
    return 0;
} 