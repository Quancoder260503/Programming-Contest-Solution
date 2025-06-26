#include "bits/stdc++.h"
using namespace std;
#define lint long long
#define MAXN (int)1e6 + 10
#define BASE 37
const int mod = 1e9 + 7;
lint pw[MAXN];
int n, q;
int cnt;
int fa[MAXN];
vector<int> comp[MAXN];
struct Node
{
     lint lef, rig, len;
     Node() : lef(0), rig(0), len(0){};
     Node(lint _lef, lint _rig, lint _len) : lef(_lef), rig(_rig), len(_len){};
     Node operator+(const Node &other)
     {
          return Node((1LL * pw[len] % mod * other.lef % mod + lef + mod) % mod, (1LL * pw[other.len] % mod * rig % mod + other.rig + mod) % mod, other.len + len);
     }
};
Node tree[MAXN];
Node null = Node(0, 0, 0);
void update(int val, int pos, int l = 1, int r = n, int p = 1)
{
     if (l == r)
     {
          tree[p].lef = tree[p].rig = val;
          tree[p].len = 1;
          return;
     }
     int mid = (l + r) / 2;
     if (pos <= mid)
          update(val, pos, l, mid, 2 * p);
     else
          update(val, pos, mid + 1, r, 2 * p + 1);
     tree[p] = tree[2 * p] + tree[2 * p + 1];
}
Node query(int L, int R, int l = 1, int r = n, int p = 1)
{
     if (L > r || R < l)
          return null;
     if (L <= l && r <= R)
     {
          return tree[p];
     }
     int mid = (l + r) / 2;
     return query(L, R, l, mid, 2 * p) + query(L, R, mid + 1, r, 2 * p + 1);
}
int find(int u)
{
     return u == fa[u] ? u : fa[u] = find(fa[u]);
}
void merge(int u, int v)
{
     u = find(u);
     v = find(v);
     if (u == v)
          return;
     if (comp[u].size() < comp[v].size())
     {
          swap(u, v);
     }
     for (int i = 0; i < comp[v].size(); i++)
     {
          int pos = comp[v][i];
          comp[u].push_back(pos);
          update(u, pos);
     }
     comp[v].clear();
     fa[v] = u;
     return;
}
bool palin(int la, int ra, int lb, int rb)
{
     Node a = query(la, ra);
     Node b = query(lb, rb);
     return (a.lef == b.rig && a.rig == b.lef && a.len == b.len);
}
bool equal(int la, int ra, int lb, int rb)
{
     Node a = query(la, ra);
     Node b = query(lb, rb);
     return (a.lef == b.lef && a.rig == b.rig && a.len == b.len);
}
signed main(void)
{
     scanf("%d %d", &n, &q);
     for (int i = 1; i <= n; i++)
     {
          fa[i] = i;
          comp[i].push_back(i);
     }
     pw[0] = 1;
     for (int i = 1; i <= n; i++)
     {
          pw[i] = pw[i - 1] % mod * BASE % mod;
     }
     for (int i = 1; i <= n; i++)
     {
          update(i, i);
     }
     for (int i = 0; i < q; i++)
     {
          int tc;
          scanf("%d", &tc);
          if (tc == 1)
          {
               int la, rb;
               scanf("%d %d", &la, &rb);
               int ra = (la + rb) / 2;
               int lb = (la + rb + 1) / 2;
               while (!palin(la, ra, lb, rb))
               {
                    int lo = 0;
                    int hi = ra - la;
                    while (lo <= hi)
                    {
                         int mid = (lo + hi) / 2;
                         if (cnt == 1)
                         {
                         }
                         if (palin(la, la + mid, rb - mid, rb))
                         {
                              lo = mid + 1;
                         }
                         else
                         {
                              hi = mid - 1;
                         }
                    }
                    merge(la + lo, rb - lo);
               }
          }
          else
          {
               int la, ra, lb, rb;
               scanf("%d %d %d %d", &la, &ra, &lb, &rb);
               if (ra - la == rb - lb)
               {
                    bool ans = equal(la, ra, lb, rb);
                    if (ans)
                         puts("Equal");
                    else
                         puts("Unknown");
               }
               else
               {
                    puts("Not equal");
               }
          }
     }
     return 0;
}