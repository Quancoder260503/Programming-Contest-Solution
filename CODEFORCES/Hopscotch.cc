#include "bits/stdc++.h"

using namespace std; 

#define int64_t long long
#define sz(x) int(x.size())


const int maxf = 4e6 + 10; 
const int mod = 1e9 + 7; 

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

int64_t Comb(int n, int k) { 
    if(n < k || k < 0) return 0; 
    return fact[n] % mod * ifact[n - k] % mod * ifact[k] % mod; 
}

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    cout.tie(0); 
    init(); 
    int N, X, Y; 
    cin >> N >> X >> Y; 
    vector<int64_t>Tx, Ty; 
    for(int k = 1; k * X <= N; k++) { 
        Tx.push_back(Comb(N - k * X - 1 + k, k - 1)); 
    }
    for(int k = 1; k * Y <= N; k++) { 
        Ty.push_back(Comb(N - k * Y - 1 + k, k - 1)); 
    } 
    int64_t ret = 0; 
    for(int i = 0; i < min(sz(Tx), sz(Ty)); i++) { 
        ret += Tx[i] % mod * Ty[i] % mod; 
        ret %= mod; 
    }
    cout << ret << '\n'; 
    return 0; 
}

