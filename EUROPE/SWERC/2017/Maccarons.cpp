#include "bits/stdc++.h"
using namespace std;
#define lint long long
const int MAXN = (int)(1 << 8);
const int mod = 1e9;
int n;
lint m;
lint dp[MAXN][MAXN];
lint mat[MAXN][MAXN];
// 0 is filled, 1 is unfilled
struct matrix
{
    lint arr[MAXN][MAXN];
};
void reset(matrix &c)
{
    for (int i = 0; i < (1 << n); i++)
    {
        for (int j = 0; j < (1 << n); j++)
        {
            c.arr[i][j] = 0;
        }
    }
}
void f(int c, int mask, int fmask)
{
    if (c == n)
    {
        dp[mask][fmask]++;
        // cout << mask << " " << fmask << " " << dp[mask][fmask] << endl;
        return;
    }
    else
    {
        if (mask & (1 << c))
        {
            f(c + 1, mask, fmask);
        }
        else
        {
            f(c + 1, mask, fmask | (1 << c));
            f(c + 1, mask, fmask);
            if (c + 1 < n && !(mask & (1 << c)) && !(mask & (1 << (c + 1))))
            {
                f(c + 2, mask, fmask);
            }
        }
    }
}
matrix operator*(const matrix &a, const matrix &b)
{
    matrix c;
    reset(c);
    for (int i = 0; i < (1 << n); i++)
    {
        for (int j = 0; j < (1 << n); j++)
        {
            for (int k = 0; k < (1 << n); k++)
            {
                c.arr[i][j] = (c.arr[i][j] + 1LL * a.arr[i][k] % mod * b.arr[k][j] % mod + mod) % mod;
            }
        }
    }
    return c;
}
signed main(void)
{
    cin >> n >> m;
    for (int mask = 0; mask < (1 << n); mask++)
    {
        f(0, mask, 0);
    }
    matrix coef;
    matrix res;
    reset(res);
    reset(coef);
    for (int i = 0; i < (1 << n); i++)
    {
        res.arr[i][i] = 1;
        for (int j = 0; j < (1 << n); j++)
        {
            coef.arr[i][j] = dp[i][j];
        }
    }
    while (m)
    {
        if (m & 1)
            res = res * coef;
        coef = coef * coef;
        m = m / 2;
    }
    cout << res.arr[0][0] << '\n';
    return 0;
}
// DP on connected profile