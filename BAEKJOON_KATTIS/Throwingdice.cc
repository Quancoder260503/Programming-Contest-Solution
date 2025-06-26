#include "bits/stdc++.h"
using namespace std;
#define lint long long
const int N = 6;
const int mod = 1e9 + 7;
struct matrix
{
    lint arr[N][N];
    void init()
    {
        memset(arr, 0, sizeof(arr));
    }
    void print()
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                cout << arr[i][j] << ' ';
            }
            cout << '\n';
        }
    }
};
matrix operator*(const matrix &a, const matrix &b)
{
    matrix c;
    c.init();
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < N; k++)
            {
                c.arr[i][j] = (c.arr[i][j] + 1LL * a.arr[i][k] % mod * b.arr[k][j] % mod + mod) % mod;
            }
        }
    }
    return c;
};
signed main(void)
{
    lint n;
    cin >> n;
    matrix coef;
    coef.init();
    matrix ret;
    ret.init();
    for (int i = 0; i < 6; i++)
    {
        ret.arr[i][i] = 1;
        coef.arr[0][i] = 1;
    }
    for (int i = 0; i < 5; i++)
    {
        coef.arr[i + 1][i] = 1;
    }
    while (n)
    {
        if (n & 1)
            ret = ret * coef;
        coef = coef * coef;
        n = n / 2;
    }
    cout << ret.arr[0][0] << '\n'; 
    return 0;
}