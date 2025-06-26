#include "bits/stdc++.h"

using namespace std;

const int maxf = 1e6 + 10;
const int mod = 998244353;

int64_t ifact[maxf], fact[maxf], dyn[maxf];
int n, tc;

int64_t fpow(int64_t a, int64_t k)
{
    if (!k) return 1;
    int64_t res = a, tmp = a;
    k--;
    while (k)
    {
        if (k & 1)
        {
            res = (int64_t)res % mod * tmp % mod;
        }
        tmp = (int64_t)tmp % mod * tmp % mod;
        k >>= 1;
    }
    return res;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> tc;
    for (int _ = 0; _ < tc; _++) {
        cin >> n;
        vector<int>a(n); 
        int x = 0, y = 0; 
        for(int i = 0; i < n; i++) {
            cin >> a[i];  
            x += (a[i] == 0); 
        } 
        for(int i = 0; i < x; i++) { 
            y += (a[i] == 0); 
        }
        vector<int64_t>dyn(x + 1); 
        for(int i = x - 1; i >= 0; i--) { 
            int64_t p = 1LL * 2 * (x - i) % mod * (x - i) % mod * fpow(1LL * n * (n - 1), mod - 2) % mod; 
            dyn[i] = 1LL * (1 + dyn[i + 1] % mod * p % mod) % mod * fpow(p, mod - 2) % mod;  
        }
        cout << dyn[y] << '\n'; 
    }
    return 0;
}
