#include "bits/stdc++.h"

using namespace std;

const int maxf = 1e6 + 10; 
const int mod = 998244353; 

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

int main(void) { 
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL); 
    cin >> tc; 
    for(int _ = 0; _ < tc; _++) { 
        cin >> n; 
        string a, b;
        cin >> a >> b; 
        int nctr = 0; 
        for(int i = 0; i < a.size(); i++) nctr += (a[i] != b[i]); 
        if(nctr == 0) { 
            cout << 0 << '\n';
            continue; 
        }
        dyn[1] = (fpow(2, n) - 1 + mod) % mod;
        for(int i = 1; i < n; i++) { 
            int64_t den = fpow(n - i, mod - 2); 
            dyn[i + 1] = ((dyn[i] - 1 + mod) % mod * n % mod * den % mod + mod - dyn[i - 1] % mod * i % mod * den % mod) % mod; 
        }
        cout << dyn[nctr] << '\n'; 
    }
    return 0; 
}
