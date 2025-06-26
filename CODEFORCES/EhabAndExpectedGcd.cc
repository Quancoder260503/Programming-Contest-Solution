#include "bits/stdc++.h"

using namespace std; 

const int maxf = 1e6 + 10; 
const int mod = 1e9 + 7; 

int64_t ifact[maxf], fact[maxf], dyn[maxf]; 
int n, tc;

int64_t
fpow(int64_t a, int64_t k) {
    if (!k)
        return 1;
    int64_t res = a, tmp = a;
    k--;
    while (k) {
        if (k & 1) {
            res = (int64_t) res * tmp % mod;
        }
        tmp = (int64_t) tmp * tmp % mod;
        k >>= 1;
    }
    return res;
}

void init() { 
    fact[0] = ifact[0] = 1; 
    for(int i = 1; i < maxf; i++){
        fact[i] = fact[i - 1] * i % mod; 
        ifact[i] = fpow(fact[i], mod - 2); 
    } 
    return; 
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    init(); 
    int n; 
    cin >> n;
    vector<vector<int>>g(n + 1);
    vector<int>opt_d(n + 1, n), dist(n + 1);  
    iota(opt_d.begin(), opt_d.end(), 0); 
    for(int i = 2; i <= n; i++) if(opt_d[i] == i) {         
        for(int j = i; j <= n; j += i) { 
            g[j].push_back(i); 
            opt_d[j] = min(opt_d[j], i); 
        }
    }
    int opt = 0; 
    for(int i = 1; i <= n; i++) { 
        int ni = i;
        while(ni > 1) { 
            dist[i]++; 
            ni = ni / opt_d[ni]; 
        }
        opt = max(opt, dist[i]); 
    } 
    auto nCr = [&](int n, int r) -> int64_t { 
        if(r > n) return 0; 
        return fact[n] % mod * ifact[r] % mod * ifact[n - r] % mod; 
    }; 
    vector<int64_t>dyn(n + 1, -1); 
    function<int64_t(int)> func = [&](int x) -> int64_t {
        if(x == 1) return 1; 
        if(dyn[x] != -1) return dyn[x]; 
        int64_t &ret = dyn[x]; 
        ret = 0; 
        for(auto &v : g[x]) {
            int vx = x / v, dx = n - n / x, dy = n / vx - n / x;  
            ret += func(vx) % mod * fact[dy] % mod * nCr(dx - 1, dy - 1) % mod; 
            ret %= mod; 
        } 
        return ret; 
    };
    int64_t ret = 0; 
    for(int i = 1; i <= n; i++) if(dist[i] == opt) { 
        ret = (ret + func(i)) % mod; 
    }
    cout << ret << '\n'; 
    return 0; 
}

/*

*/ 