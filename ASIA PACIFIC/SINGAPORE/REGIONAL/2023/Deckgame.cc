#include "bits/stdc++.h"
using namespace std;

#define sz(x) (int) x.size()

const int N = (1 << 18);
const int mod = 998244353;
using pii = pair<int64_t, int64_t>; 

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

void fwht(vector<int64_t>&a, bool inv)
{
    for (int n = sz(a), step = 1; step < n; step *= 2) {
        for (int i = 0; i < n; i += 2 * step) for(int j = i; j < i + step; j++) {
                int64_t &u = a[j], &v = a[j + step];
                tie(u, v) = pii(u + v, u - v);        
        }
    }
    if (inv) { 
        int64_t inv = fpow(sz(a), mod - 2); 
        for (int64_t& x : a) x = x % mod * inv % mod;  
    }
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n; 
    cin >> n; 
    vector<int64_t>a(N), pw3(N); 
    for(int i = 0, x; i < n; i++) {
        cin >> x; 
        a[x]++;
    }
    fwht(a, false);
    pw3[0] = 1; 
    for(int i = 1; i < N; i++) pw3[i] = pw3[i - 1] * 3 % mod; 
    for(int i = 0; i < N; i++) {
        int64_t c = (a[i] + n) / 2; 
        a[i] = 1LL * ((n - c) & 1 ? mod - 1 : 1) % mod * pw3[c] % mod;
    }
    fwht(a, true); 
    cout << a[0] << '\n'; 
    return 0;
}