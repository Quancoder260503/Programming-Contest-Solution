#include "bits/stdc++.h"

using namespace std; 

const int maxf = (1 << 21);
const int maxb = (1 << 17); 
const int mod  = 1e9 + 7; 

int64_t fib[maxf], ofib[maxb + 10], xfib[maxb + 10], ret[maxb + 10], ctr[maxb + 10];

int64_t fpow(int64_t a, int64_t k)
{
    if (!k) return 1;
    int64_t res = a, tmp = a;
    k--;
    while (k)
    {
        if (k & 1)
        {
            res = (int64_t)res * tmp % mod;
        }
        tmp = (int64_t)tmp * tmp % mod;
        k >>= 1;
    }
    return res;
}
void FWHT(int64_t *P, int deg, bool invert)
{
    for (int len = 1; 2 * len <= deg; len = len * 2)
    {
        for (int i = 0; i < deg; i += 2 * len)
        {
            for (int j = 0; j < len; j++)
            {
                int64_t u = P[i + j];
                int64_t v = P[i + j + len];
                P[i + j] = (u + v) % mod;
                P[i + j + len] = (u - v + mod) % mod;
            }
        }
    }
    if (invert)
    {
        int64_t inv = fpow(deg, mod - 2); 
        for (int i = 0; i < deg; i++)
        {
            P[i] = P[i] * inv % mod;
        }
    }
}
void ANDFWHT(int64_t *P, int deg, bool invert)
{
    for (int len = 1; 2 * len <= deg; len = len * 2)
    {
        for (int i = 0; i < deg; i += 2 * len)
        {
            for (int j = 0; j < len; j++)
            {
                int64_t u = P[i + j];
                int64_t v = P[i + j + len];
                if (!invert)
                {
                    P[i + j] = v;
                    P[i + j + len] = (u + v + mod) % mod;
                }
                else
                {
                    P[i + j] = (v - u + mod) % mod;
                    P[i + j + len] = u;
                }
            }
        }
    }
}

int main(void)
{
    int n; 
    cin >> n;
    fib[1] = 1; 
    for(int i = 2; i < maxf; i++) fib[i] = (fib[i - 1] + fib[i - 2]) % mod; 
    for(int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        ctr[x]++; 
        xfib[x]++; 
    }
    for(int x = 0; x < maxb; x++)
    {
        int rx = x xor (maxb - 1); 
        for(int y = rx; ; y = rx & (y - 1))
        {
            ofib[x | y] += ctr[x] % mod * ctr[y] % mod * fib[x | y] % mod;
            ofib[x | y] %= mod;
            if(y == 0) break;    
        }
    }
    FWHT(xfib, maxb, 0);
    for(int i = 0; i < maxb; i++) xfib[i] = xfib[i] * xfib[i] % mod; 
    FWHT(xfib, maxb, 1); 
    for(int i = 0; i < maxb; i++) xfib[i] = xfib[i] % mod * fib[i] % mod; 
    for(int i = 0; i < maxb; i++) ctr[i]  = ctr[i]  % mod * fib[i] % mod; 
    ANDFWHT(xfib, maxb, 0);
    ANDFWHT(ofib, maxb, 0);
    ANDFWHT(ctr,  maxb, 0);
    for(int i = 0; i < maxb; i++) ret[i] = xfib[i] % mod * ofib[i] % mod * ctr[i] % mod; 
    ANDFWHT(ret, maxb, 1); 
    int64_t res = 0;
    for(int i = 0; (1 << i) < maxb; i++)
    {
        res = (res + ret[(1 << i)]) % mod; 
    }
    cout << res << '\n'; 
    return 0; 
}