#include "bits/stdc++.h"

using namespace std;

struct Line
{
    int k;
    int64_t m;
    Line(int _k, int64_t _m) { k = _k, m = _m; }
    Line() : Line(0, INT64_MIN) {}
    int64_t get(int64_t x) { return k * x + m; }
    bool majorize(Line X, int64_t L, int64_t R)
    {
        return get(L) >= X.get(L) && get(R) >= X.get(R);
    }
};

void ckmax(int64_t &a, int64_t b)
{
    a = max(a, b);
    return;
}

struct lc
{
    lc *c[2];
    Line S;
    lc()
    {
        c[0] = c[1] = NULL;
        S = Line();
    }
    ~lc()
    {
        for (int i = 0; i < 2; i++)
            delete c[i];
    }
    void mc(int i)
    {
        if (!c[i])
            c[i] = new lc();
    }
    int64_t mid(int64_t x) { return x & 1 ? (x - 1) / 2 : x / 2; }
    int64_t query(int64_t X, int64_t L, int64_t R)
    {
        int64_t ans = S.get(X), M = mid(L + R);
        if (X <= M)
        {
            if (c[0])
                ckmax(ans, c[0]->query(X, L, M));
        }
        else
        {
            if (c[1])
                ckmax(ans, c[1]->query(X, M + 1, R));
        }
        return ans;
    }
    void modify(Line X, int64_t L, int64_t R)
    {
        if (X.majorize(S, L, R))
            swap(X, S);
        if (S.majorize(X, L, R))
            return;
        if (S.get(L) < X.get(L))
            swap(X, S);
        int64_t M = mid(L + R);
        if (X.get(M) >= S.get(M))
            swap(X, S), mc(0), c[0]->modify(X, L, M);
        else
            mc(1), c[1]->modify(X, M + 1, R);
    }
};

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
        dyn[i] = -INF;
    }
    for (int i = 1; i <= n; i++)
    {
        prefix[i][arr[i]]++;
        for (int j = 0; j <= k; j++)
            prefix[i][j] += prefix[i - 1][j];
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = k; j >= 1; j--)
            prefix[i][j] += prefix[i][j + 1];
    }
    for (int i = n; i > 0; i--)
    {
        if (arr[i])
            suffix[i][arr[i]]++;
        for (int j = 1; j <= k; j++)
            suffix[i][j] += suffix[i + 1][j];
    }
    for (int i = n; i > 0; i--)
    {
        for (int j = 1; j <= k; j++)
            suffix[i][j] += suffix[i][j - 1];
    }
    int64_t ret = 0;
    for (int i = 1; i <= n; i++)
        if (arr[i])
        {
            ret += prefix[i][arr[i] + 1];
        }
    for (int num = k; num > 0; num--)
    {
        lc *root = new lc();
        root->modify(Line(0, 0), 0, prefix[n][0]);
        for (int i = 1; i <= n; i++)
        {
            p[i] = p[i - 1];
            if (arr[i] == 0)
            {
                p[i] += prefix[i][num + 1] + suffix[i][num - 1];
                root->modify(Line(prefix[i][0], dyn[i] - p[i] - 1LL * prefix[i][0] * prefix[i][0]), 0, prefix[n][0]);
                dyn[i] = root->query(prefix[i][0], 0, prefix[n][0]) + p[i];
            }
            else
            {
                dyn[i] = dyn[i - 1];
            }
        }
    }
    ret += dyn[n];
    cout << ret << '\n';
    return 0;
}