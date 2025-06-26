#include "bits/stdc++.h"
using namespace std;
#define lint long long
#define pii pair<int,int> 
#define mp make_pair
const int MAXN = (int)2e5 + 10;
const lint INF = 1e12;
int in[MAXN], out[MAXN];
int pos[MAXN];
int n, k;
lint tree[MAXN * 4], tree2[MAXN * 4];
lint lazy[MAXN * 4], lazy2[MAXN * 4];
int dist[MAXN]; 
vector<pii>adj[MAXN]; 
lint a[MAXN], b[MAXN]; 
void push_down(int p)
{
    if (lazy[p] != 0)
    {
        tree[2 * p] += lazy[p];
        tree[2 * p + 1] += lazy[p];
        lazy[2 * p] += lazy[p];
        lazy[2 * p + 1] += lazy[p];
        lazy[p] = 0;
    }
    return;
}
void push_down2(int p)
{
    if (lazy2[p] != 0)
    {
        tree2[2 * p] += lazy2[p];
        tree2[2 * p + 1] += lazy2[p];
        lazy2[2 * p] += lazy2[p];
        lazy2[2 * p + 1] += lazy2[p];
        lazy2[p] = 0;
    }
    return;
}
void update(lint val, int L, int R, int l = 1, int r = n, int p = 1)
{
    if (L > r || R < l)
        return;
    if (L <= l && r <= R)
    {
        tree[p] += val;
        lazy[p] += val;
        return;
    }
    int mid = (l + r) / 2;
    push_down(p);
    update(val, L, R, l, mid, 2 * p);
    update(val, L, R, mid + 1, r, 2 * p + 1);
    tree[p] = max(tree[2 * p], tree[2 * p + 1]);
}
void update2(lint val, int L, int R, int l = 1, int r = n, int p = 1)
{
    if (L > r || R < l)
        return;
    if (L <= l && r <= R)
    {
        tree2[p] += val;
        lazy2[p] += val;
        return;
    }
    int mid = (l + r) / 2;
    push_down2(p);
    update2(val, L, R, l, mid, 2 * p);
    update2(val, L, R, mid + 1, r, 2 * p + 1);
    tree2[p] = min(tree2[2 * p], tree2[2 * p + 1]);
}
int timer = 1;
void dfs(int u, int p)
{
    in[u] = timer++; 
    for(int i = 0; i < adj[u].size(); i++)
    {
        int v = adj[u][i].first; 
        int cost = adj[u][i].second;
        if (v == p) continue;
        dist[v] = dist[u] + cost; 
        dfs(v, u); 
    }
    out[u] = timer - 1; 
}
void dfs2(int u, int p)
{
     b[u] = tree[1]; 
     a[u] = tree2[1]; 
     for(int i = 0; i < adj[u].size(); i++)
     {
         int v = adj[u][i].first; 
         int cost = adj[u][i].second;
         if(v == p) continue; 
         update(cost, 1, n); 
         update(-2 * cost, in[v], out[v]);
         update2(cost, 1, n);
         update2(-2 * cost, in[v], out[v]);
         dfs2(v, u);
         update2(2 * cost, in[v], out[v]);
         update2(-cost, 1, n);
         update(2 * cost,  in[v], out[v]); 
         update(-cost, 1, n); 
     } 
} 
bool cmp(const int x, const int y)
{
    return 1LL * a[x] * b[y] < 1LL * a[y] * b[x]; 
}
lint gcd(lint a, lint b)
{
    if(a == 0) return b;
    return gcd(b % a, a); 
}
signed main(void)
{
    cin >> n >> k;
    for(int i = 1; i <= k; i++)
    {
         int x; cin >> x; 
         pos[x]++; 
    }
    for(int i = 1; i < n; i++)
    {
         int u,v, cost;
         cin >> u >> v >> cost; 
         adj[u].push_back(mp(v, cost));
         adj[v].push_back(mp(u, cost)); 
    }
    memset(lazy, 0, sizeof(lazy)); 
    memset(tree, 0, sizeof(tree)); 
    memset(lazy2, 0, sizeof(lazy2)); 
    memset(tree2, 0, sizeof(tree2));
    dfs(1, 0); 
    for(int i = 1; i <= n; i++)
    {
        if(pos[i])
        {
            update(dist[i], in[i], in[i]); 
            update2(dist[i], in[i], in[i]); 
        }
        else 
        {
             update(-INF, in[i], in[i]); 
             update2(INF, in[i], in[i]); 
        }
    }
    dfs2(1, 0); 
    vector<int>ord(n); 
    iota(ord.begin(), ord.end(), 1); 
    sort(ord.begin(), ord.end(), cmp);
    int g = gcd(a[ord[n - 1]] , b[ord[n - 1]]);
    assert(g != 0); 
    cout << a[ord[n - 1]] / g << "/" << b[ord[n - 1]] / g << endl;
    return 0;
}
/* for each node find the farthest node and closest node of which */