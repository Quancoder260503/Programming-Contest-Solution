#include "bits/stdc++.h"
#include <array>
using namespace std;
#define lint long long
#define MAXN 102
const int mod = (int) 1e9 + 7;
using Matrix = array<array<lint, MAXN>, MAXN>;
lint n;
int k, c, t;
Matrix matrix_multiplication(Matrix &a, Matrix &b)
{
    Matrix c;
    for(int i = 0; i < MAXN; i++)
    {
         for(int j = 0; j < MAXN; j++)
         {
             c[i][j] = 0;
         }
    }
    for (int i = 0; i < MAXN; ++i)
    {
        for (int j = 0; j < MAXN; ++j)
        {
            for (int k = 0; k < MAXN; ++k)
            {
                c[i][j] = (c[i][j] + 1LL * a[i][k] % mod * b[k][j] % mod + mod) % mod;
            }
        }
    }
    return c;
}
Matrix binpow(Matrix &a, lint pow)
{
    Matrix c;
    for (int i = 0; i < MAXN; i++)
    {
        for (int j = 0; j < MAXN; j++)
        {
            c[i][j] = a[i][j];
        }
    }
    while(pow)
    {
         if(pow & 1) c = matrix_multiplication(c, a);
         a = matrix_multiplication(a, a);
         pow = pow / 2; 
    }
    return c;
}
signed main(void)
{
    scanf("%lld %d %d %d", &n, &k, &t, &c);
    Matrix a, b;
    for (int i = 0; i < MAXN; i++)
    {
         for (int j = 0; j < MAXN; j++)
         {
            a[i][j] = b[i][j] = 0;
         }
    }
    for(int i = 1; i <= t; i++)
    {
        a[i][i - 1] = 1; 
    }
    a[t][t] = 1;
    a[0][t] = k;
    b[t][0] = c;
    lint res = 0;
    if(n > 1)
    {
        Matrix p = binpow(a, n - 2);
        Matrix ans = matrix_multiplication(p, b); 
        for (int i = 0; i <= t; i++)
        {
            res = (res + mod + ans[i][0] % mod * (i == t ? 2 : 1) % mod) % mod;
        }
    }
    else 
    {
         res = 1LL * c * 2 % mod;
    }
    printf("%lld\n", res);  
    return 0;
}
/*
   Special case : n = 1 
*/ 