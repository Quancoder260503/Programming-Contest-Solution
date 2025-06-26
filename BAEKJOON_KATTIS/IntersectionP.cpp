#include "bits/stdc++.h"
using namespace std;
const int MAXN = (int)2e5 + 10;
template <class T, int SZ>
struct Fenwick2D
{
    bool mode = 0;               // mode = 1 -> initialized
    vector<pair<int, int>> todo; // locations of updates to process
    int cnt[SZ], st[SZ];
    vector<int> val;
    vector<T> bit; // store all BITs in single vector
    void init()
    {
        assert(!mode);
        mode = 1;
        int lst[SZ];
        for (int i = 0; i < SZ; i++)
        {
            lst[i] = cnt[i] = 0;
        }
        sort(todo.begin(), todo.end(), [](const pair<int, int> &a, const pair<int, int> &b)
             { return a.second < b.second; });
        for (auto &t : todo)
        {
            for (int x = t.first; x < SZ; x += x & -x)
            {
                if (lst[x] != t.second)
                {
                    lst[x] = t.second, cnt[x]++;
                }
            }
        }
        int sum = 0;
        for (int i = 0; i < SZ; i++)
        {
            lst[i] = 0, st[i] = (sum += cnt[i]);
        }
        val.resize(sum);
        bit.resize(sum);
        reverse(todo.begin(), todo.end());
        for (auto &t : todo)
        {
            for (int x = t.first; x < SZ; x += x & -x)
            {
                if (lst[x] != t.second)
                {
                    lst[x] = t.second, val[--st[x]] = t.second;
                }
            }
        }
    }
    int rank(int y, int l, int r)
    {
        return upper_bound(begin(val) + l, begin(val) + r, y) - begin(val) - l;
    }
    void UPD(int x, int y, T t)
    {
        for (y = rank(y, st[x], st[x] + cnt[x]); y <= cnt[x]; y += y & -y)
        {
            bit[st[x] + y - 1] += t;
        }
    }
    void upd(int x, int y, T t)
    {
        if (!mode)
            todo.push_back({x, y});
        else
            for (; x < SZ; x += x & -x)
                UPD(x, y, t);
    }
    int QUERY(int x, int y)
    {
        T res = 0;
        for (y = rank(y, st[x], st[x] + cnt[x]); y; y -= y & -y)
            res += bit[st[x] + y - 1];
        return res;
    }
    T query(int x, int y)
    {
        assert(mode);
        T res = 0;
        for (; x; x -= x & -x)
            res += QUERY(x, y);
        return res;
    }
    T query(int xl, int xr, int yl, int yr)
    {
        return query(xr, yr) - query(xl - 1, yr) - query(xr, yl - 1) + query(xl - 1, yl - 1);
    }
};
int n, q;
pair<int, int> pos[MAXN];
int a[MAXN], b[MAXN], c[MAXN];
struct Query
{
    int type, r1, c1, r2, c2;
    Query(int _type, int _r1, int _c1, int _r2, int _c2) : type(_type), r1(_r1), c1(_c1), r2(_r2), c2(_c2){};
};
signed main(void)
{
    cin >> n >> q;
    Fenwick2D<int, MAXN> fenw;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        pos[a[i]].first = i;
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> b[i];
        c[i] = b[i];
        pos[b[i]].second = i;
    }
    for (int i = 1; i <= n; i++)
    {
        fenw.upd(pos[i].first, pos[i].second, 1);
    }
    vector<Query> qry;
    for (int i = 1; i <= q; i++)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int r1, c1, r2, c2;
            cin >> r1 >> c1 >> r2 >> c2;
            qry.push_back(Query(type, r1, c1, r2, c2));
        }
        else
        {
            int x, y;
            cin >> x >> y;
            int atx = c[x];
            int aty = c[y];
            swap(c[x], c[y]);
            pos[atx].second = y;
            pos[aty].second = x;
            fenw.upd(pos[atx].first, pos[atx].second, 1);
            fenw.upd(pos[aty].first, pos[aty].second, 1);
            qry.push_back(Query(type, x, y, -1, -1));
        }
    }
    fenw.init();
    for (int i = 1; i <= n; i++)
    {
        c[i] = b[i];
        pos[c[i]].second = i;
    }
    for (int i = 1; i <= n; i++)
    {
        fenw.upd(pos[i].first, pos[i].second, 1);
    }
    for (int i = 0; i < q; i++)
    {
        auto now = qry[i];
        if (now.type == 1)
        {
            cout << fenw.query(now.r1, now.c1, now.r2, now.c2) << '\n';
        }
        else
        {
            int x = now.r1, y = now.c1;
            int atx = c[x];
            int aty = c[y];
            fenw.upd(pos[atx].first, pos[atx].second, -1);
            fenw.upd(pos[aty].first, pos[aty].second, -1);
            swap(c[x], c[y]);
            pos[atx].second = y;
            pos[aty].second = x;
            fenw.upd(pos[atx].first, pos[atx].second, 1);
            fenw.upd(pos[aty].first, pos[aty].second, 1);
        }
    }
    return 0;
}