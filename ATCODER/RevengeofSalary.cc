#include "bits/stdc++.h"

using namespace std;

const int mod = 998244353; 

int64_t fpow(int64_t a, int64_t k) {
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
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int64_t> a(n + 1), e(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i]; 
    }
    e[n] = a[n];
    int64_t invn = fpow(n, mod - 2); 
    for (int i = n - 1; i >= 0; i--) {
        e[i] = (e[i + 1] % mod * (1 + invn) % mod + (a[i] - a[i + 1]) % mod + mod) % mod; 
    }
    cout << e[0] << '\n'; 
    return 0;
}