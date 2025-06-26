#include "bits/stdc++.h"


#define int64_t long long 

using namespace std; 

int main(void) {
    ios_base::sync_with_stdio(0); 
    cin.tie(0); 
    int tc; 
    cin >> tc; 
    auto func = [&](int64_t n, int64_t p, int64_t q) -> int64_t { 
        int64_t t = gcd(p, q), z = 1;
        p = p / t; 
        q = q / t;  
        int64_t ret = 0; 
        while(q > 0 && n > 0) { 
            t = p / q; 
            ret += 1LL * n * (n + 1) * t * z / 2;
            p = p - 1LL * q * t; 
            t = n / q; 
            ret += 1LL * z * p * t * (n + 1) - 1LL * z * t * (p * q * t + p + q - 1) / 2; 
            n = n - 1LL * q * t; 
            t = (1LL * n * p) / q; 
            ret += 1LL * z * t * n;
            n = t; 
            swap(p, q); 
            z = -z;  
        }
        return ret; 
    }; 
    while(tc--) { 
        int64_t n, p, q; 
        cin >> p >> q >> n;
        cout << 1LL * p * n * (n + 1) / 2 - 1LL * q * func(n, p, q) << '\n'; 
    } 
    return 0; 
}