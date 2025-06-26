#include "bits/stdc++.h"

using namespace std; 

const int mod = 998244353; 

#define int64_t long long

int64_t
fpow(int64_t a, int64_t k) {
    if (!k) return 1;
    int64_t res = 1, tmp = a % mod;
    while (k) {
        if (k & 1) {
            res = 1LL * res % mod * tmp % mod;
        }
        tmp = 1LL * tmp % mod * tmp % mod;
        k >>= 1;
    }
    return res;
}

int main(void) { 
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0);
    int n; int64_t k; 
    cin >> n >> k; 
    int64_t den = fpow(k, mod - 2);  
    vector<int64_t>Prob(n), c(n), T(n); 
    for(int i = 0; i < n; i++) { 
        cin >> T[i];
        --T[i]; 
    }
    for(int i = 0; i < n; i++) { 
        cin >> c[i]; 
    }
    auto mul = [&](vector<int64_t>a, vector<int64_t>b) {
        vector<int64_t>ret(n); 
        for(int i = 0; i < n; i++) { 
            ret[i] = a[b[i]]; 
        }
        return ret; 
    }; 
    auto go = [&](vector<int64_t>a, vector<int64_t>b) { 
        vector<int64_t>ret(n); 
        for(int i = 0; i < n; i++) { 
            ret[a[i]] += b[i]; 
            ret[a[i]] %= mod; 
        }
        return ret; 
    }; 
    auto get_expected = [&](vector<int64_t>&ret, vector<int64_t>add) { 
        for(int i = 0; i < n; i++) { 
            ret[i] += add[i]; 
            ret[i] %= mod; 
        }
        return; 
    };
    c = go(T, c); 
    while(k) { 
        if(k & 1) { 
            get_expected(Prob, c); 
            c = go(T, c); 
        }
        k >>= 1;
        get_expected(c, go(T, c));  
        T = mul(T, T);
    }
    for(int i = 0; i < n; i++) { 
        cout << Prob[i] % mod * den % mod << ' '; 
    }
    return 0; 
}