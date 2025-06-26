#include "bits/stdc++.h"
using namespace std;
const int maxf = (1 << 21);
const int mod = 1e9 + 7;
int64_t fpow(int64_t a, int64_t k)
{
    if (!k)
        return 1;
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
                if(!invert)
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
int64_t P[maxf];
int main(void)
{
    int N; 
    while (cin >> N)
    {
        for (int i = 0; i < N; i++) 
        {
            int64_t x; 
            cin >> x; 
            P[x]++;
        }
        int deg = (1 << 20);
        P[0]++;  
        FWHT(P, deg, 0);
        for (int i = 0; i < deg; i++)
        {
            P[i] = fpow(P[i], N);
        }
        FWHT(P, deg, 1);
        int64_t ret = 0;
        for (int i = 0; i < deg; i++) ret = ret + (P[i] != 0); 
        cout << ret << '\n';
    }
    return 0;
}