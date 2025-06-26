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
set<int> query[MAXN][2];
vector<int> cor;
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
    void upd(int x, int v)
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
bool cmph(const int a, const int b)
{
    return h[a] < h[b];
}
bool cmpg(const int a, const int b)
{
    return g[a] < g[b];
}
void solve()
{
    for (int i = 1; i <= n; i++)
    {
        seg.upd(i, g[i]);
        query[g[i]][0].insert(i);
        query[h[i]][1].insert(i);
    }
    for (int i = 1; i <= N; i++)
    {
        while (query[i][0].size() && query[i][1].size())
        {
            int start =  (*query[i][0].begin());
            int target = (*query[i][1].begin());
            while (start < target)
            {
                int lo = start + 1;
                int hi = n;
                while (lo < hi)
                {
                    int mid = (lo + hi) / 2;
                    if (seg.query(start + 1, mid) <= i)
                    {
                        lo = mid + 1;
                    }
                    else
                    {
                        hi = mid;
                    }
                }
                if (lo > n) break;
                int low = start; 
                int high = lo - 1;
                while (low < high)
                {
                    int mid = (low + high + 1) / 2;
                    if (seg.query(mid, lo - 1) < i)
                    {
                        high = mid - 1;
                    }
                    else
                    {
                        low = mid;
                    }
                }
                int nxt = seg.query(lo, lo);
                seg.upd(low, nxt);
                seg.upd(lo, i);
                query[i][0].erase(low);
                query[i][0].insert(lo);
                query[nxt][0].erase(lo);
                query[nxt][0].insert(low);
                moves.push_back(mp(low, lo));
                if (start == low)
                    start = lo;
                if (moves.size() == LIM)
                    break;
            }
            while (start > target)
            {
                int lo = 1;
                int hi = start - 1;
                while (lo < hi)
                {
                    int mid = (lo + hi + 1) / 2;
                    if (seg.query(mid, start - 1) <= i)
                    {
                        hi = mid - 1;
                    }
                    else
                    {
                        lo = mid;
                    }
                }
                if (lo < 1) break;
                int low = lo + 1;
                int high = start;
                while (low < high)
                {
                    int mid = (low + high) / 2;
                    if (seg.query(low + 1, mid) < i)
                    {
                        low = mid + 1;
                    }
                    else
                    {
                        high = mid;
                    }
                }
                int nxt = seg.query(lo, lo);
                seg.upd(low, nxt);
                seg.upd(lo, i);
                query[i][0].erase(low);
                query[i][0].insert(lo);
                query[nxt][0].erase(lo);
                query[nxt][0].insert(low);
                moves.push_back(mp(low, lo));
                if (start == low) start = lo;
                if (moves.size() == LIM) break;
            }
            query[i][0].erase(*query[i][0].begin());
            query[i][1].erase(*query[i][1].begin());
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
        cor.push_back(g[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &h[i]);
        cor.push_back(h[i]);
    }
    sort(cor.begin(), cor.end());
    cor.erase(unique(cor.begin(), cor.end()), cor.end());
    Fenwick<lint> feng(n + 1);
    Fenwick<lint> fenh(n + 1);
    for (int i = 1; i <= n; i++)
    {
        ordg.push_back(i);
        ordh.push_back(i);
    }
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
    for (int i = 1; i <= n; i++)
    {
        g[i] = lower_bound(cor.begin(), cor.end(), g[i]) - cor.begin() + 1;
        h[i] = lower_bound(cor.begin(), cor.end(), h[i]) - cor.begin() + 1;
    }
    cout << ans << '\n';
    seg.init(n + 1);
    N = cor.size();
    solve();
    for (int i = 0; i < min((int)moves.size(), LIM); i++)
    {
       printf("%d %d\n", moves[i].first, moves[i].second);
    }
    return 0;
}