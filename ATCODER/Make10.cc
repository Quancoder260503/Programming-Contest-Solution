#include "bits/stdc++.h"

using namespace std; 

const int LOG = 11; 
const int mod = 998244353; 

int64_t
fpow(int64_t a, int64_t k) {
    if (!k) return 1;
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

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0); 
    int N; 
    cin >> N; 
    vector<vector<int64_t>>dyn(N + 1, vector<int64_t>(1 << LOG, 0)); 
    dyn[0][1] = 1; 
    for(int i = 1, x; i <= N; i++) { 
        cin >> x; 
        int64_t den = fpow(x, mod - 2); 
        for(int mask = 0; mask < (1 << LOG); mask++) { 
            for(int j = 1; j <= min(x, 10); j++) { 
                int nmask = ((mask << j) | mask) & ((1 << LOG) - 1); 
                dyn[i][nmask] += dyn[i - 1][mask] % mod * den % mod;
                dyn[i][nmask] %= mod;  
            }
            dyn[i][mask] += dyn[i - 1][mask] % mod * den % mod * max(0, x - 10) % mod;
            dyn[i][mask] %= mod;  
        }
    }
    int64_t ret = 0; 
    for(int mask = 0; mask < (1 << LOG); mask++) if(mask & (1 << 10)) { 
        ret += dyn[N][mask]; 
        ret %= mod; 
    }
    cout << ret << '\n'; 
    return 0; 
}