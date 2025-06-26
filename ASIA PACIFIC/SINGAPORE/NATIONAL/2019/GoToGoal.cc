#include "bits/stdc++.h"

using namespace std;

const int mod = 1e9 + 7;
const int maxf = 1e6 + 2; 

int64_t fact[maxf], ifact[maxf]; 

int64_t fpow(int64_t a, int64_t k)
{
    if (!k) return 1;
    int64_t res = a, tmp = a;
    k--;
    while (k)
    {
        if (k & 1)
        {
            res = (long long)res * tmp % mod;
        }
        tmp = (long long)tmp * tmp % mod;
        k >>= 1;
    }
    return res;
}

void init(void)
{
    fact[0] = ifact[0] = 1; 
    for(int i = 1; i < maxf; i++)
    {
        fact[i] = 1LL * fact[i - 1] * i % mod; 
        ifact[i] = fpow(fact[i], mod - 2); 
    }
    return; 
}

int64_t f(int a, int b, int c)
{
    return fact[a + b + c] % mod * ifact[a] % mod * ifact[b] % mod * ifact[c] % mod; 
}

int main(void)
{
    int N, M; 
    cin >> N >> M;
    int64_t ret = 0;  
    init(); 
    for(int space = 0; space < 3; space++)
    {
        for(int two = 0; two <= M; two++)
        {
            int one  = N - 2 * two - space; 
            int zero = M - two - one; 
            if(one < 0 || zero < 0) continue;
            ret += f(zero, one, two);
            ret %= mod; 
        }
    }
    cout << ret << '\n'; 
    return 0;
}
