#include "bits/stdc++.h"
using namespace std;
#define mp make_pair
#define pii pair<int, int>
const int MAXN = 5e5 + 10;
int tree[MAXN * 4] = {0};
int lazy[MAXN * 4] = {0};
int n, m, q;
vector<int> dset[MAXN];
pii at[MAXN];
int ans[MAXN];
struct qry
{
    int in, type, l, r, pos;
    qry(int _in, int _pos, int _l, int _r, int _type) : in(_in), pos(_pos), l(_l), r(_r), type(_type){};
};
struct fenwick
{
    int N;
    vector<int> bit;
    void init(int _N)
    {
        N = _N;
        bit.resize(N);
    }
    int sum(int i)
    {
        int c = 0;
        for (++i; i > 0; i -= (i & -i))
        {
            c = c + bit[i];
        }
        return c;
    }
    void upd(int i, int dif)
    {
        for (++i; i < N; i += (i & -i))
        {
            bit[i] = dif + bit[i];
        }
    }
    void update(int l, int r)
    {
        upd(l, 1);
        upd(r + 1, -1);
    }
} fenw[MAXN];
void push_down2(int p)
{
    if (lazy[p] != 0)
    {
        tree[2 * p] = tree[2 * p + 1] = lazy[p];
        lazy[2 * p] = lazy[2 * p + 1] = lazy[p];
        lazy[p] = 0;
    }
}
void update2(int val, int L, int R, int l = 1, int r = n, int p = 1)
{
    if (L > r || R < l)
        return;
    if (L <= l && r <= R)
    {
        tree[p] = val;
        lazy[p] = val;
        return;
    }
    push_down2(p);
    int mid = (l + r) / 2;
    update2(val, L, R, l, mid, 2 * p);
    update2(val, L, R, mid + 1, r, 2 * p + 1);
}
int get2(int pos, int l = 1, int r = n, int p = 1)
{
    if (l == r)
    {
        return tree[p];
    }
    push_down2(p);
    int mid = (l + r) / 2;
    if (pos <= mid)
        return get2(pos, l, mid, 2 * p);
    else
        return get2(pos, mid + 1, r, 2 * p + 1);
}
vector<qry> offline[MAXN];
bool cmp(const qry &a, const qry &b)
{
    return a.in < b.in;
}
signed main(void)
{
    cin >> n >> m >> q;
    for (int i = 1; i <= m; i++)
    {
        int sz;
        cin >> sz;
        fenw[i].init(sz + 2);
        dset[i].resize(sz);
        for (int j = 0; j < sz; j++)
        {
            cin >> dset[i][j];
        }
    }
    memset(ans, -1, sizeof(ans));
    for (int i = 1; i <= q; i++)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int pos, ndset;
            cin >> ndset >> pos;
            update2(i, pos, pos + dset[ndset].size() - 1);
            at[i] = mp(pos, ndset);
        }
        else if (type == 2)
        {
            int pos;
            cin >> pos;
            int now = get2(pos);
            if (now)
            {
                offline[at[now].second].push_back(qry(now, i, at[now].first, pos, -1));
            }
            else
            {
                ans[i] = 0;
            }
        }
        else
        {
            int l, r, pos;
            cin >> pos >> l >> r;
            offline[pos].push_back(qry(i, i, l, r, 1));
        }
    }
    for (int i = 1; i <= m; i++)
    {
        sort(offline[i].begin(), offline[i].end(), cmp);
        for (int j = 0; j < offline[i].size(); j++)
        {
            qry curr = offline[i][j];
            if (curr.type == 1)
            {
                fenw[i].update(curr.l, curr.r);
            }
            else
            {
                ans[curr.pos] = (dset[i][curr.r - curr.l] + fenw[i].sum(curr.r - curr.l + 1)) % 256;
            }
        }
    }
    for (int i = 1; i <= q; i++)
    {
        if (ans[i] != -1)
            cout << ans[i] << '\n';
    }
    return 0;
}
/*
    We still need fenwick tree to keep track of the increment
    Use index to actually measure the in of increment
*/