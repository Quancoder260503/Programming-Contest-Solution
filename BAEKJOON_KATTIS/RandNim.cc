#include "bits/stdc++.h"
using namespace std;
const int maxf = 1e6 + 10; 
const int mod = 30011;
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
    for(int len = 1; 2 * len <= deg; len = len * 2)
    {
        for(int i = 0; i < deg; i += 2 * len)
        {
            for(int j = 0; j < len; j++)
            {
                int64_t u = P[i + j]; 
                int64_t v = P[i + j + len]; 
                P[i + j] = (u + v) % mod;
                P[i + j + len] = (u - v + mod) % mod; 
            }
        }
    }
    if(invert)
    {
        for(int i = 0; i < deg; i++)
        {
            P[i] = P[i] * fpow(deg, mod - 2); 
        }
    }
}
int64_t P[maxf]; 
int main(void)
{
    int N, K;
    while (cin >> N >> K)
    {
        for(int i = 0; i <= K; i++) P[i] = 1; 
        int deg = (1 << 18); 
        FWHT(P,  deg, 0);
        for(int i = 0; i < deg; i++)
        {
            P[i] = fpow(P[i], N); 
        }
        FWHT(P,  deg, 1);
        int64_t ret = 0; 
        for(int i = 1; i < deg; i++) ret = (ret + mod + P[i]) % mod;
        cout << ret << '\n';   
    }
    return 0;
}