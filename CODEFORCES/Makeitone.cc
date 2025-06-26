#include "bits/stdc++.h"

using namespace std;

const int maxf = 4e5 + 10; 
const int mod = 1e9 + 7;
const int LOG = 20;  

int64_t dyn[maxf][LOG], fact[maxf], ifact[maxf], a[maxf], n;

int64_t fpow(int64_t a, int64_t k) {
    if (!k) return 1;
    int64_t res = a, tmp = a;
    k--;
    while (k) {
        if (k & 1) {
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
    cin >> n;
    fact[0] = ifact[0] = 1; 
    for(int i = 1; i < maxf; i++) { 
        fact[i]  = fact[i - 1] % mod * i % mod;
        ifact[i] = ifact[i - 1] % mod * fpow(i, mod - 2) % mod; 
    }
    int sz = 0;   
    for(int i = 0, x; i < n; i++) { 
        cin >> x; 
        a[x]++; 
        sz = max(sz, x); 
    }
    for(int i = 1; i <= sz; i++) { 
        for(int j = 2 * i; j <= sz; j += i) { 
            a[i] += a[j]; 
        }
    }
    auto C = [&](int n, int k) -> int64_t { 
        if(n < k) return 0; 
        return fact[n] % mod * ifact[k] % mod * ifact[n - k] % mod; 
    }; 
    for(int c = 1; c <= LOG; c++) { 
        for(int i = sz; i > 0; i--) { 
            dyn[c][i] = C(a[i], c);
            for(int j = 2 * i; j <= sz; j += i) { 
                dyn[c][i] = (dyn[c][i] + mod - dyn[c][j]) % mod; 
            }  
        }
    }
    for(int i = 1; i <= LOG; i++) if(dyn[i][1] > 0) { 
        cout << i << '\n';
        return 0; 
    }
    cout << -1 << '\n'; 
    return 0;
}