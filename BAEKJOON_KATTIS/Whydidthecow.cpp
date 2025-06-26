#include "bits/stdc++.h"
using namespace std;
#define lint long long
#define s second
#define f first
const int MAXN = (int)1e5 + 10;
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
             { return a.s < b.s; });
        for (auto &t : todo)
        {
            for (int x = t.f; x < SZ; x += x & -x)
            {
                if (lst[x] != t.s)
                {
                    lst[x] = t.s, cnt[x]++;
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
            for (int x = t.f; x < SZ; x += x & -x)
            {
                if (lst[x] != t.s)
                {
                    lst[x] = t.s, val[--st[x]] = t.s;
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
int n, k;
pair<int, int> pos[MAXN];
signed main(void)
{
    cin >> n >> k;
    Fenwick2D<int, MAXN> fenw;
    for (int i = 1; i <= n; i++)
    {
        int c;
        cin >> c;
        pos[c].first = i;
    }
    for (int i = 1; i <= n; i++)
    {
        int c;
        cin >> c;
        pos[c].second = i;
    }
    for (int i = 1; i <= n; i++)
    {
        fenw.upd(pos[i].first, pos[i].second, 1);
    }
    fenw.init();
    int at = 1;
    lint ans = 0; 
    for (int i = 1; i <= n; i++)
    {
        while (at < i - k)
        {
            fenw.upd(pos[at].first, pos[at].second, 1);
            at++;
        }
        ans += fenw.query(pos[i].first, n) + fenw.query(n, pos[i].second) - 2 * fenw.query(pos[i].first, pos[i].second); 
    }
    cout << ans << '\n'; 
    return 0;
}