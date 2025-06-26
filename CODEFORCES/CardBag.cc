#include "bits/stdc++.h"

using namespace std;

const int mod = 998244353;
int n;

int64_t fpow(int64_t a, int64_t k) {
    if (!k)   return 1;
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
    int n; 
    cin >> n; 
    vector<int>ctr(n + 1);
    vector<int64_t> dyn(n + 1, 0), fact(n + 1, 0), ifact(n + 1, 0);
    fact[0] = ifact[0] = 1; 
    for(int i = 0, x; i < n; i++) { 
        cin >> x;  
        ctr[x]++; 
    }
    for(int i = 1; i <= n; i++) { 
        fact[i] = fact[i - 1] * i % mod; 
        ifact[i] = ifact[i - 1] * fpow(i, mod - 2) % mod; 
    }
    dyn[0] = 1; 
    int64_t acc = 0; 
    for(int i = 1; i <= n; i++) { 
        vector<int64_t>ndyn(n + 1); 
        for(int j = 0; j <= i; j++) { 
            if(j) ndyn[j] = (dyn[j - 1] * ctr[i]) % mod; 
            if(ctr[i] > 1) { 
                acc = (acc + 1LL * ndyn[j] % mod * (ctr[i] - 1) % mod * fact[n - j - 1] % mod) % mod; 
            }
            ndyn[j] = (ndyn[j] + dyn[j]) % mod; 
        }
        dyn.swap(ndyn); 
    }
    cout << acc % mod * ifact[n] % mod << '\n'; 
    return 0;
}