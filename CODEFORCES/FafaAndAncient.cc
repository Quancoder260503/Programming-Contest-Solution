#include "bits/stdc++.h"

using namespace std;

const int maxf = 1e6 + 10;
const int mod = 1e9 + 7; 

int64_t dyn[maxf];
int n, m, tc;

int64_t fpow(int64_t a, int64_t k)
{
    if (!k)
        return 1;
    int64_t res = a, tmp = a;
    k--;
    while (k)
    {
        if (k & 1)
        {
            res = (int64_t)res * tmp % mod;
        }
        tmp = (int64_t)tmp * tmp % mod;
        k >>= 1;
    }
    return res;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n >> m; 
    dyn[n] = 0; 
    vector<int>a(n), b(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) cin >> b[i]; 
    int64_t invm = fpow(m, mod - 2), inv2 = fpow(2, mod - 2); 
    for(int i = n - 1; i >= 0; i--) { 
        if(a[i] != 0 && b[i] != 0) { 
            if(a[i] == b[i]) dyn[i] = dyn[i + 1];
            else dyn[i] = (a[i] > b[i]);
        }
        else { 
            if(a[i] == 0 && b[i] == 0) dyn[i] = 1LL * (m - 1) % mod * invm % mod * inv2 % mod + dyn[i + 1] % mod * invm % mod; 
            else if (a[i] == 0)        dyn[i] = 1LL * (m - b[i]) % mod * invm % mod + dyn[i + 1] % mod * invm % mod; 
            else if (b[i] == 0)        dyn[i] = 1LL * (a[i] - 1) % mod * invm % mod + dyn[i + 1] % mod * invm % mod; 
        }
        dyn[i] %= mod; 
    }
    cout << dyn[0] << '\n'; 
    return 0;
}