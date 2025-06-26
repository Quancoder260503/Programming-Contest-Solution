#include "bits/stdc++.h"
using namespace std;
#define MAXN 150000
#define lint long long
const int mod = 1e9 + 7;
int n, k;
lint ans[MAXN];
struct Vec
{
    lint x, y;
    Vec(lint _x = 0, lint _y = 0) : x(_x), y(_y) {}
    lint dot(const Vec &other) const
    {
        return x * other.x + y * other.y;
    }
    lint cross(const Vec &other) const
    {
        return 1LL * x * other.y - 1LL * y * other.x;
    }
    bool operator<(const Vec &a) const
    {
        return x == a.x ? y < a.y : x < a.x;
    }
    Vec operator-(const Vec &a) const
    {
        return Vec(x - a.x, y - a.y);
    }
    lint length() const
    {
        return sqrt(x * x + y * y);
    }
    lint norm() const
    {
        return x * x + y * y;
    }
};
using Point = Vec;
Point P[MAXN];
struct fenwick
{
    int N;
    vector<lint> bit;
    void init(lint _N)
    {
        N = _N;
        bit.resize(N);
    }
    lint sum(int i)
    {
        lint c = 0;
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
            bit[i] = (1LL) * (dif + bit[i]);
        }
    }
    lint query(int l, int r)
    {
        return sum(r) - sum(l - 1);
    }
} fenw;
lint ccw(Point C, Point B, Point A)
{
    Vec X = B - C;
    Vec Y = A - C;
    return 1LL * X.cross(Y);
}
int val[MAXN];
Point original = Point(0, 0);
bool cmp(const int a, const int b)
{
    Vec A = P[a] - P[0];
    Vec B = P[b] - P[0];
    lint p = A.cross(B);
    return p == 0 ? A.norm() < B.norm() : p > 0;
}
bool cmp2(const int a, const int b)
{
    Vec A = P[a] - original;
    Vec B = P[b] - original;
    lint p = A.cross(B);
    return p == 0 ? A.norm() < B.norm() : p > 0;
}
signed main(void)
{
    cin >> n;
    P[0].y = 0;
    cin >> P[0].x;
    for (int i = 1; i <= n; i++)
    {
        cin >> P[i].x >> P[i].y >> val[i];
    }
    fenw.init(n + 2);
    vector<int> ordg(n);
    vector<int> ordh(n);
    iota(ordh.begin(), ordh.end(), 1);
    iota(ordg.begin(), ordg.end(), 1);
    sort(ordh.begin(), ordh.end(), cmp);
    sort(ordg.begin(), ordg.end(), cmp2);
    reverse(ordh.begin(), ordh.end());
    reverse(ordg.begin(), ordg.end());
    vector<int> gh(n + 1);
    for (int i = 0; i < ordg.size(); i++)
    {
        gh[ordg[i]] = i + 1;
    }
    for (int i = 0; i < ordh.size(); i++)
    {
        ans[ordh[i]] = fenw.query(gh[ordh[i]] + 1, n);
        fenw.upd(gh[ordh[i]], val[ordh[i]]);
    }
    for (int i = 1; i <= n; i++)
    {
        cout << ans[i] << '\n';
    }
    return 0;
}