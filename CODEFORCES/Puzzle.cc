#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())
const int mod  = 998244353; 
const int maxf = 4e6 + 10; 

int64_t fact[maxf], ifact[maxf]; 

int64_t Comb(int a, int b) { 
    if(a == b) return 1; 
    if(a < b || b < 0) return 0; 
    return fact[a] % mod * ifact[b] % mod * ifact[a - b] % mod; 
}

int64_t fpow(int64_t a, int64_t k) {
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

int64_t ways(int n1, int n2, int n3, int n4) { 
    return (Comb(n1 + n3 - 1, n3) % mod * Comb(n2 + n4 - 1, n4)) % mod; 
}

int main(void) {
    ios_base::sync_with_stdio(0); 
    cin.tie(0); 
    cout.tie(0);
    init(); 
    int tc; 
    cin >> tc; 
    for(int iter = 0; iter < tc; iter++) { 
        int n1, n2, n3, n4; 
        cin >> n1 >> n2 >> n3 >> n4; 
        if(n1 == 0 && n2 == 0) { 
            cout << (n3 == 0 || n4 == 0 ? 1 : 0) << '\n'; 
            continue;
        }
        if(abs(n1 - n2) > 1) { 
            cout << 0 << '\n'; 
            continue; 
        }
        int64_t ret = 0; 
        if(n1 <= n2) { 
            ret += ways(n1 + 1, n2, n3, n4); 
            ret %= mod; 
        }
        if(n2 <= n1) { 
            ret += ways(n1, n2 + 1, n3, n4); 
            ret %= mod; 
        }
        cout << ret << '\n'; 
    }
    return 0; 
}