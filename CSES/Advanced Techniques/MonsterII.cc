#include "bits/stdc++.h"
using namespace std;
const int maxf = (int)1e6 + 10;
const int64_t INF = 1e12;
struct Line
{
    int64_t m, b = INF;
    //Line(int64_t _m, int64_t _b) : m(_m), b(_b) {};  
    int64_t operator()(int64_t x) { return 1LL * m * x + b; }
};
Line seg[maxf * 4];
int64_t lo[maxf * 4], hi[maxf * 4], f[maxf], s[maxf]; 
void build(int i, int l, int r)
{
    lo[i] = l;
    hi[i] = r;
    seg[i] = {0, INF};
    if (l == r)
        return;
    int m = (l + r) / 2;
    build(2 * i, l, m);
    build(2 * i + 1, m + 1, r);
}

void insert(int i, Line L)
{
    int l = lo[i], r = hi[i];
    if (l == r)
    {
        if (L(l) < seg[i](l)) seg[i] = L;
        return;
    }

    int m = (l + r) / 2;
    if (seg[i].m < L.m) swap(seg[i], L);
    if (seg[i](m) > L(m))
    {
        swap(seg[i], L);
        insert(2 * i, L);
    }
    else
        insert(2 * i + 1, L);
}

int64_t query(int i, int64_t x)
{
    int l = lo[i], r = hi[i];
    if (l == r)
        return seg[i](x);

    int m = (l + r) / 2;
    if (x < m)
        return min(seg[i](x), query(2 * i, x));
    else
        return min(seg[i](x), query(2 * i + 1, x));
}
int main(void)
{
    int n;
    int64_t x;
    cin >> n >> x;
    for (int i = 1; i <= n; i++)
    {
        cin >> s[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> f[i];
    }
    build(1, 1, maxf); 
    insert(1, {x, 0});
    for (int i = 1; i < n; i++)
    {
        int64_t opt = query(1, s[i]);
        insert(1, {f[i], opt});
    }
    cout << query(1, s[n]) << '\n';
    return 0;
}