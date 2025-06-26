#include "bits/stdc++.h"
using namespace std; 
const int MAXN = (int) 2e6 + 10; 
int n, q;
char s[MAXN];  
struct Node
{
     int opt, L, R; 
     Node() : L(0), R(0), opt(0) {};  
} tree[MAXN * 2]; 
Node operator + (const Node &a, const Node &b)
{
    Node res = Node(); 
    res.opt = a.opt + b.opt + 2 * min(a.L, b.R); 
    res.L = a.L + b.L - min(a.L, b.R); 
    res.R = a.R + b.R - min(a.L, b.R); 
    return res; 
}
void build(int l = 1, int r = n, int p = 1)
{
    if (l == r)
    {
         tree[p] = Node();
         tree[p].L = (s[l - 1] == '('); 
         tree[p].R = (s[r - 1] == ')'); 
         return; 
    }
    int mid = (l + r) >> 1;
    build(l, mid, 2 * p);
    build(mid + 1, r, 2 * p + 1);
    tree[p] = tree[2 * p] + tree[2 * p + 1]; 
}
Node query(int L, int R, int l = 1, int r = n, int p = 1)
{
    if (L > r || R < l) return Node(); 
    if (L <= l && r <= R)
    {
      return tree[p];
    }
    int mid = (l + r) >> 1;
    return query(L, R, l, mid, 2 * p) + query(L, R, mid + 1, r, 2 * p + 1);
}
signed main(void)
{
    scanf(" %s",&s);
    n = strlen(s);
    scanf("%d", &q);
    build(); 
    for(int i = 0; i < q; i++)
    {
         int l, r; 
         scanf("%d %d", &l, &r);
         printf("%d\n", query(l, r).opt); 
    }
    return 0; 
}