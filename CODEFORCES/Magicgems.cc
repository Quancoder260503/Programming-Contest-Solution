#include "bits/stdc++.h"
using namespace std;
#define lint long long
const int N = 102;
const int mod = 1e9 + 7;
struct matrix
{
    lint mat[N][N];
    void init()
    {
        memset(mat, 0, sizeof(mat));
    }
    void print(int n)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << mat[i][j] << " ";
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
                c.mat[i][j] = (c.mat[i][j] + mod + 1LL * a.mat[i][k] % mod * b.mat[k][j] % mod) % mod;
            }
        }
    }
    return c;
}
signed main(void)
{
    lint n;
    int m;
    while (cin >> n >> m)
    {
        matrix coef, ret;
        ret.init();
        coef.init();
        coef.mat[0][0] = 1; 
        for(int i = 1; i < m; i++)
        {
            coef.mat[i][i - 1] = 1; 
        }
        coef.mat[0][m - 1] = 1;
        ret.mat[0][0] = 1;
        while (n)
        {
            if (n & 1) ret = ret * coef;
            coef = coef * coef;
            n = n / 2;
        }
        cout << ret.mat[0][0] << '\n';
    }
    return 0;
}