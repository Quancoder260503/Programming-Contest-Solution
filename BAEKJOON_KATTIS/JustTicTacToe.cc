#include "bits/stdc++.h"

using namespace std;

const int maxf = 1e7 + 10;

int64_t fpow(int64_t a, int64_t k)
{
    if (!k) return 1;
    int64_t res = a, tmp = a;
    k--;
    while (k)
    {
        if (k & 1)
        {
            res = (int64_t)res * tmp;
        }
        tmp = (int64_t)tmp * tmp;
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
                P[i + j] = (u + v) ;
                P[i + j + len] = (u - v );
            }
        }
    }
    if (invert)
    {
        for (int i = 0; i < deg; i++)
        {
            P[i] = P[i] / deg; 
        }
    }
    return; 
}
int64_t P[maxf], ctr[maxf];

int main(void)
{
    int n, k; 
    cin >> n >> k; 
    for(int i = 0; i < n; i++) { 
        int64_t x; cin >> x; 
        x %= (k + 1); 
        ctr[x]++; 
        P[x]++; 
    }
    int deg = (1 << 19); 
    FWHT(P, deg, 0); 
    for(int i = 0; i < deg; i++) P[i] = 1LL * P[i] * P[i]; 
    FWHT(P, deg, 1);
    int64_t ret = 0; 
    for(int i = 0; i < deg; i++) ret += P[i] * ctr[i];  
    ret = ret - 3 * n * ctr[0]; 
    ret += 2 * ctr[0]; 
    cout << ret / 6 << '\n'; 
    return 0;
}