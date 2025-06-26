#include "bits/stdc++.h"

using namespace std;

#define int64_t long long 

const int maxf = 1e6 + 10; 
const int mod = 1e9 + 7; 

int64_t sum[maxf]; 

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


int main(void) { 
    ios_base::sync_with_stdio(0); 
    cin.tie(0); 
    cout.tie(0); 
    for(int i = 1; i < maxf; i++) { 
        sum[i] += (sum[i - 1] + fpow(fpow(2, i) % mod, mod - 2)) % mod; 
        sum[i] %= mod; 
    }
    int tc, N; 
    cin >> tc; 
    for(int iter = 0; iter < tc; iter++) { 
        cin >> N; 
        vector<int64_t>a(N + 1), prefix(N + 1); 
        for(int i = 1; i <= N; i++) { 
            cin >> a[i]; 
        }
        sort(a.begin(), a.end()); 
        for(int i = 1; i <= N; i++) { 
            prefix[i] += (prefix[i - 1] + 1LL * a[i] % mod * fpow(fpow(2, i) % mod, mod - 2) % mod) % mod; 
            prefix[i] %= mod; 
        }
        int64_t ret = 0; 
        for(int i = 1; i <= N; i++) { 
            ret += fpow(2, i - 1) % mod * (a[i] % mod * sum[i] % mod - prefix[i] + mod) % mod; 
            ret %= mod; 
        }
        printf("Case #%d: %lld\n", iter + 1, ret); 
    }
    return 0; 
}