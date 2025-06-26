#include "bits/stdc++.h"

using namespace std;

const int maxf = 1e6 + 10;
const int mod = 998244353;

int n, p[maxf];

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

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL); 
    cin >> n; 
    for(int i = 0; i < n; i++) { 
        cin >> p[i];
    }
    int64_t w = 1, num = 0, den = 1, inv = fpow(100, mod - 2); 
    for(int i = 0; i < n; i++) { 
        den = den % mod * p[i] % mod * inv % mod; 
        num = (num + w) % mod; 
        w = w % mod * p[i] % mod * inv % mod; 
    }
    cout << num % mod * fpow(den, mod - 2) % mod << '\n'; 
    return 0;
}