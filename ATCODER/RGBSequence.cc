#include "bits/stdc++.h"

using namespace std; 

#define int64_t long long

const int maxf = 4e6 + 10; 
const int mod = 998244353; 

int64_t ifact[maxf], fact[maxf], dyn[maxf]; 

int64_t
fpow(int64_t a, int64_t k) {
    if (!k) return 1;
    int64_t res = a, tmp = a;
    k--;
    while (k) {
        if (k & 1) {
            res = (int64_t) res % mod * tmp % mod;
        }
        tmp = (int64_t) tmp % mod * tmp % mod;
        k >>= 1;
    }
    return res;
}

void init(void) {
    fact[0] = ifact[0] = 1; 
    for(int i = 1; i < maxf; i++) { 
        fact[i]  = fact[i - 1] % mod * i % mod; 
        ifact[i] = ifact[i - 1] % mod * fpow(i, mod - 2) % mod; 
    }
    return; 
}

int 
main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);  
    init(); 
    int k, r, g, b; 
    cin >> r >> g >> b >> k; 
    int64_t ret = 0;
    r = r - k, g = g - k; 
    for(int x = 0, sign = 1; x <= min(r, g); x++) { 
        ret = (ret + sign * fact[r + g + b + k - x] % mod * ifact[b] % mod * ifact[r - x] % mod * ifact[g - x] % mod * ifact[x] % mod * ifact[k] % mod + mod) % mod; 
        sign = sign * (-1); 
    }
    cout << ret << '\n'; 
    return 0; 
}

/*

*/ 
