#include "bits/stdc++.h"
using namespace std;
#define pii pair<int, int>
#define mp make_pair
int n, a, b;
const int INF = (int)1e9;
const int MAXN = 7e5 + 10;
int arr[MAXN];
struct seg
{
    pii tree[MAXN];
    int lim;
    void init(int n)
    {
        fill(tree, tree + MAXN, mp(INF, 0));
        for (lim = 1; lim <= n; lim <<= 1);
    }
    pii combine(pii a, pii b)
    {
        return min(a, b);
    }
    void upd(int x, pii v)
    {
        x += lim;
        tree[x] = v;
        while (x > 1)
        {
            x >>= 1;
            tree[x] = combine(tree[2 * x], tree[2 * x + 1]);
        }
    }
    pii query(int s, int e)
    {
        s += lim;
        e += lim;
        pii R = mp(INF, 0), L = mp(INF, 0);
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
} segmn, segmx;
int dp[MAXN];
void del(int v)
{
    segmn.upd(v, mp(INF, 0));
    segmx.upd(v, mp(INF, 0));
}
void solve()
{
    cin >> n >> a >> b;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }
    for (int i = 1; i <= n; i++)
    {
        segmn.upd(i, mp(i - arr[i], i));
        segmx.upd(i, mp(-(i + arr[i]), i));
    }
    memset(dp, 63, sizeof(dp));
    queue<int> q;
    q.push(a);
    del(a);
    dp[a] = 0;
    while (q.size())
    {
        int u = q.front();
        q.pop();
        pii curr;
        while ((curr = segmn.query(u + 1, min(u + arr[u], n))).first <= u)
        {
            int v = curr.second;
            dp[v] = dp[u] + 1;
            q.push(v);
            del(v);
        }
        while (-(curr = segmx.query(max(u - arr[u], 1), u - 1)).first >= u)
        {
            int v = curr.second;
            dp[v] = dp[u] + 1;
            q.push(v);
            del(v);
        }
    }
    cout << dp[b] << '\n';
}
signed main(void)
{
    int t;
    cin >> t;
    segmn.init((int) 2e5 + 10);
    segmx.init((int) 2e5 + 10);
    while (t--)
    {
        solve();
    }
    return 0;
}