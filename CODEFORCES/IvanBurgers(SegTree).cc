#include "bits/stdc++.h"

using namespace std;

const int maxb = 20;
const int maxf = 5e5 + 2;

struct basis
{
    vector<int64_t> A;
    int flag;
    void init()
    {
        A.resize(maxb + 1);
        return;
    }
    void add(int64_t val)
    {
        for (int mask = maxb; mask >= 0; mask--)
            if (val & (1LL << mask))
            {
                if (A[mask])
                {
                    val = val xor A[mask];
                }
                else
                {
                    A[mask] = val;
                    return;
                }
            }
        return;
    }
};

basis tree[maxf << 2], c;
int n, m;

void build(int l = 1, int r = n, int p = 1)
{
    tree[p].init();
    if (l == r) return;
    int mid = (l + r) / 2;
    build(l, mid, 2 * p);
    build(mid + 1, r, 2 * p + 1);
    return;
}

void update(int x, int pos, int l = 1, int r = n, int p = 1)
{
    tree[p].add(x);
    if (l == r) return;
    int mid = (l + r) / 2;
    if (pos <= mid)
        update(x, pos, l, mid, 2 * p);
    else
        update(x, pos, mid + 1, r, 2 * p + 1);
    return;
}

basis query(int L, int R, int l = 1, int r = n, int p = 1)
{
    if (L > r || R < l)
        return c;
    if (L <= l && r <= R)
        return tree[p];
    int mid = (l + r) / 2;
    auto left = query(L, R, l, mid, 2 * p);
    auto rigt = query(L, R, mid + 1, r, 2 * p + 1);
    for (auto y : rigt.A)
        left.add(y);
    return left;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n;
    build();
    c.init();
    for (int i = 1, x; i <= n; i++)
    {
        cin >> x;
        update(x, i);
    }
    cin >> m;
    for (int _ = 0, l, r; _ < m; _++)
    {
        cin >> l >> r;
        int64_t ret = 0;
        basis cc = query(l, r);
        for (int i = maxb; i >= 0; i--)
        {
            if ((ret ^ cc.A[i]) > ret)
            {
                ret = ret ^ cc.A[i];
            }
        }
        cout << ret << '\n';
    }
    return 0;
}