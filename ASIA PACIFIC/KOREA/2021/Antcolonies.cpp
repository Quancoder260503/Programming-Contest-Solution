#include "bits/stdc++.h"
using namespace std;
#define N 1000005
const int mod = 1e9;
int n, q;
int col[N];
vector<int> adj[N];
int trs[N], dep[N];
int up[23][N];
int in[N], top[N];
int timer = 1;
int ans[N];
struct query
{
    int id, u, v, type;
    query(int _id, int _u, int _v, int _type) : id(_id), u(_u), v(_v), type(_type){};
};
vector<query> qry[N];
struct node
{
    int opt, left, right, dist;
    node() : dist(0), left(mod), right(mod), opt(mod) {}
    node(int x) : dist(1), left(x > 0 ? 0 : mod), right(x > 0 ? 0 : mod), opt(mod) {}
    node operator+(const node &other)
    {
        node res;
        res.dist = dist + other.dist;
        res.left = min(left, dist + other.left);
        res.right = min(other.right, other.dist + right);
        res.opt = min(other.opt, min(opt, right + other.left + 1));
        return res;
    }
} tree[N * 4];
void update(int val, int pos, int l = 1, int r = n, int p = 1)
{
    if (l == r)
    {
        tree[p] = node(val);
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid)
        update(val, pos, l, mid, 2 * p);
    else
        update(val, pos, mid + 1, r, 2 * p + 1);
    tree[p] = tree[2 * p] + tree[2 * p + 1];
    return;
}
node queryn(int L, int R, int l = 1, int r = n, int p = 1)
{
    if (L > r || R < l)
        return node();
    if (L <= l && r <= R)
        return tree[p];
    int mid = (l + r) / 2;
    return queryn(L, R, l, mid, 2 * p) + queryn(L, R, mid + 1, r, 2 * p + 1);
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
        if (v == p)
            continue;
        dep[v] = dep[up[0][v] = u] + 1;
        trs[u] += dfs(v, u);
    }
    return trs[u];
}
void dfs_hld(int u, int anc)
{
    in[u] = timer++;
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
    if (hchi == 0)
        return;
    dfs_hld(hchi, anc);
    for (int i = 0; i < adj[u].size(); i++)
    {
        int v = adj[u][i];
        if (v == up[0][u] or v == hchi)
            continue;
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
int lca(int a, int b)
{
    if (dep[a] < dep[b])
        swap(a, b);
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
node path(int u, int v)
{
    int anc = lca(u, v);
    vector<node> f;
    vector<node> s;
    while (top[u] != top[anc])
    {
        f.push_back(queryn(in[top[u]], in[u]));
        u = up[0][top[u]];
    }
    f.push_back(queryn(in[anc], in[u]));
    while (top[v] != top[anc])
    {
        s.push_back(queryn(in[top[v]], in[v]));
        v = up[0][top[v]];
    }
    if (in[anc] < in[v])
        s.push_back(queryn(in[anc] + 1, in[v]));
    reverse(s.begin(), s.end());
    for (int i = 0; i < s.size(); i++)
    {
        swap(s[i].left, s[i].right);
    }
    for (int i = 0; i < s.size(); i++)
    {
        f.push_back(s[i]);
    }
    node res = node();
    for (int i = 0; i < f.size(); i++)
    {
        res = f[i] + res;
    }
    return res;
}
signed main(void)
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &col[i]);
    }
    for (int i = 1; i < n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 0);
    dfs_hld(1, 0);
    for (int i = 1; i <= n; i++)
    {
        qry[col[i]].push_back(query(0, i, 1, -1));
    }
    int sz = 0;
    for (int i = 0; i < q; i++)
    {
        char typ;
        scanf(" %c", &typ);
        if ((char)typ == 'Q')
        {
            int u, v, c;
            scanf("%d%d%d", &u, &v, &c);
            qry[c].push_back(query(++sz, u, v, 1));
        }
        else
        {
            int u, c;
            scanf("%d%d", &u, &c);
            qry[col[u]].push_back(query(0, u, -1, -1));
            col[u] = c;
            qry[col[u]].push_back(query(0, u, 1, -1));
        }
    }
    for (int i = 1; i <= n; i++)
    {
        qry[col[i]].push_back(query(0, i, -1, -1));
    }
    fill(tree, tree + N * 4, node());
    for (int i = 1; i <= n; i++)
    {
        update(-1, i);
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < qry[i].size(); j++)
        {
            query curr = qry[i][j];
            if (curr.type == -1)
            {
                update(curr.v, in[curr.u]);
            }
            else
            {
                node res = path(curr.u, curr.v);
                ans[curr.id] = res.opt <= n ? res.opt : -1;
                return 0;
            }
        }
    }
    for (int i = 1; i <= sz; i++)
    {
        printf("%d\n", ans[i]);
    }
    return 0;
}
