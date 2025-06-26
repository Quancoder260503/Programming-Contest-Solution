#include "bits/stdc++.h"

using namespace std;

const int LOG = 20; 
const int mod = 1e9 + 7;
const int maxf = (1 << LOG);

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
    int n;
    cin >> n;
    vector<int64_t> dyn(maxf), a(maxf);
    for (int i = 0, x; i < n; i++) {
        cin >> x;
        dyn[x]++; 
    }
    for(int i = 0; i < LOG; i++) { 
        for(int mask = 0; mask < (1 << LOG); mask++) if(mask & (1 << i)) {
            dyn[mask xor (1 << i)] += dyn[mask]; 
        } 
    }
    for(int i = 0; i < maxf; i++) {
        dyn[i] = (fpow(2, dyn[i]) - 1 + mod) % mod;
    }
    for(int i = 0; i < LOG; i++) { 
        for(int mask = 0; mask < (1 << LOG); mask++) if(mask & (1 << i)) { 
            dyn[mask xor (1 << i)] = (dyn[mask xor (1 << i)] - dyn[mask] + mod) % mod; 
        }
    }
    cout << dyn[0] << '\n'; 
    return 0;
}