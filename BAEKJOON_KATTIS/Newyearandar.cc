#include "bits/stdc++.h"

using namespace std;

const int mod = 1e9 + 7; 
const int maxf = 2000;

int64_t n, pa, pb, ivpa, ivpb, ivps, dyn[maxf][maxf];

int64_t fpow(int64_t a, int64_t k)
{
    if (!k) return 1;
    int64_t res = a, tmp = a;
    k--;
    while (k) {
        if (k & 1) res = (long long)res * tmp % mod;
        tmp = (long long)tmp * tmp % mod;
        k >>= 1;
    }
    return res;
}

int64_t f(int a, int ab) {
    if (ab >= n) return ab;
    if(a + ab >= n) return (1LL * ivpb % mod * (pa + pb) % mod + mod - 1 + ab + a) % mod; 
    if(dyn[a][ab] != -1) return dyn[a][ab]; 
    int64_t &ret = dyn[a][ab]; 
    ret = (1LL * pa % mod * f(a + 1, ab) % mod + 1LL * pb % mod * f(a, a + ab) % mod) % mod * ivps % mod; 
    return ret;  
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL); 
    cin >> n >> pa >> pb;
    ivpa  = fpow(pa, mod - 2); 
    ivpb  = fpow(pb, mod - 2); 
    ivps  = fpow(pa + pb, mod - 2); 
    memset(dyn, -1, sizeof(dyn)); 
    cout << (f(1, 0)) % mod << '\n'; 
    return 0;
}