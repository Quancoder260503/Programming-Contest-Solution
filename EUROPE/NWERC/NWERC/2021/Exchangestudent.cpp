#include "bits/stdc++.h"
using namespace std;
#define LIM (int)2e5
#define pii pair<int, int>
#define lint long long
const int MAXN = 1e6 + 10;
#define mp make_pair
int n;
int N;
int h[MAXN], g[MAXN];
vector<pii> moves;
struct seg
{
    int tree[MAXN];
    int lim;
    void init(int n)
    {
        fill(tree, tree + MAXN, 0);
        for (lim = 1; lim <= n; lim <<= 1)
            ;
    }
    int combine(int a, int b)
    {
        return max(a, b);
    }
    void update(int x, int v)
    {
        x += lim;
        tree[x] = v;
        while (x > 1)
        {
            x >>= 1;
            tree[x] = combine(tree[2 * x], tree[2 * x + 1]);
        }
    }
    int query(int s, int e)
    {
        s += lim;
        e += lim;
        int L, R;
        L = R = 0;
        while (s < e)
        {
            if (s % 2 == 1)
                L = combine(L, tree[s++]);
            if (e % 2 == 0)
                R = combine(tree[e--], R);
            s >>= 1;
            e >>= 1;
        }
        if (s == e)
            L = combine(L, tree[s]);
        return combine(L, R);
    }
} seg;

template <typename T>
struct Fenwick
{
    Fenwick(int _n) : n(_n), f(_n + 1) {}
    void update(int u, T val)
    {
        assert(0 <= u && u < n);
        ++u;
        for (; u <= n; u += u & -u)
        {
            f[u] += val;
        }
    }
    T get(int u) const
    {
        assert(0 <= u && u <= n);
        T res = 0;
        for (; u > 0; u -= u & -u)
        {
            res += f[u];
        }
        return res;
    }
    T get(int l, int r) const
    {
        assert(0 <= l && l <= r && r <= n);
        if (l == r)
            return 0;
        return get(r) - get(l);
    }

    void reset()
    {
        std::fill(f.begin(), f.end(), T(0));
    }
    int n;
    vector<T> f;
};
vector<int> ordh;
vector<int> ordg;
vector<int> posg;
bool cmph(const int a, const int b)
{
    return h[a] < h[b];
}
bool cmpg(const int a, const int b)
{
    return g[a] < g[b];
}
void swappos(int i, int j)
{
    swap(g[i], g[j]);
    swap(posg[i], posg[j]);
    swap(ordg[posg[i]], ordg[posg[j]]);
    seg.update(i, g[i]);
    seg.update(j, g[j]);
    moves.push_back(mp(i, j));
}
void solve()
{
    for (int i = 1; i <= n; i++)
    {
        seg.update(i, g[i]);
    }
    for (int i = 0; i < n; i++)
    {
        int start = ordg[i];
        int target = ordh[i];
        while (start < target)
        {
            int lo = start + 1;
            int hi = n;
            while (lo < hi)
            {
                int mid = (lo + hi) / 2;
                if (seg.query(start + 1, mid) <= g[start])
                {
                    lo = mid + 1;
                }
                else
                {
                    hi = mid;
                }
            }
            if (lo > n)
                break;
            int low = start;
            int high = lo - 1;
            while (low < high)
            {
                int mid = (low + high + 1) / 2;
                if (seg.query(mid, lo - 1) < g[start])
                {
                    high = mid - 1;
                }
                else
                {
                    low = mid;
                }
            }
            swappos(low, lo);
            if (start == low)
                start = lo;
            if (moves.size() == LIM)
                return;
        }
        while (start > target)
        {
            int lo = 1;
            int hi = start - 1;
            while (lo < hi)
            {
                int mid = (lo + hi + 1) / 2;
                if (seg.query(mid, start - 1) <= g[start])
                {
                    hi = mid - 1;
                }
                else
                {
                    lo = mid;
                }
            }
            if (lo < 1)
                break;
            int low = lo + 1;
            int high = start;
            while (low < high)
            {
                int mid = (low + high) / 2;
                if (seg.query(lo + 1, mid) < g[start])
                {
                    low = mid + 1;
                }
                else
                {
                    high = mid;
                }
            }
            swappos(lo, low);
            if (start == low)
                start = lo;
            if (moves.size() == LIM)
                return;
        }
    }
    return;
}
signed main(void)
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &g[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &h[i]);
    }
    Fenwick<lint> feng(n + 1);
    Fenwick<lint> fenh(n + 1);
    for (int i = 1; i <= n; i++)
    {
        ordg.push_back(i);
        ordh.push_back(i);
    }
    posg.resize(n + 1, 0);
    stable_sort(ordh.begin(), ordh.end(), cmph);
    stable_sort(ordg.begin(), ordg.end(), cmpg);
    lint ans = 0;
    for (int i = 0; i < n; i++)
    {
        int curh = ordh[i];
        int curg = ordg[i];
        feng.update(curg, 1);
        fenh.update(curh, 1);
        ans += 1LL * abs((curg - feng.get(curg)) - (curh - fenh.get(curh)));
    }
    for (int i = 0; i < n; i++)
    {
        posg[ordg[i]] = i;
    }
    cout << ans << '\n';
    seg.init(n + 1);
    solve();
    for (int i = 0; i < min((int)moves.size(), LIM); i++)
    {
        printf("%d %d\n", moves[i].first, moves[i].second);
    }
    return 0;
}
