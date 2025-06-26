#include "bits/stdc++.h"
 
using namespace std; 
 
const int mod = 998244353; 
 
#define sz(x) int(x.size())
 
int64_t x, y, k, dyn[2][20][(1 << 10) + 10], sum[2][20][(1 << 10) + 10], pw[20];  
 
int64_t f(const string &a, int is_equal, int i, int mask) { 
    if(i == sz(a)) return 1; 
    if(dyn[is_equal][i][mask] != -1) return dyn[is_equal][i][mask]; 
    int d = (is_equal ? a[i] - '0' : 9); 
    int64_t &ret = dyn[is_equal][i][mask]; 
    ret = 0; 
    for(int ni = (i == 0); ni <= d; ni++) { 
        if(mask & (1 << ni)) { 
            ret += f(a, is_equal & (ni == d), i + 1, mask); 
            ret %= mod; 
        }
        else if(__builtin_popcount(mask) < k) { 
            ret += f(a, is_equal & (ni == d), i + 1, mask | (1 << ni));
            ret %= mod; 
        }
    } 
    return ret; 
}
 
int64_t f2(const string &a, int is_equal, int i, int mask) { 
    if(i == sz(a)) return 0; 
    if(sum[is_equal][i][mask] != -1) return sum[is_equal][i][mask]; 
    int d = (is_equal ? a[i] - '0' : 9); 
    int64_t &ret = sum[is_equal][i][mask]; 
    ret = 0; 
    for(int ni = (i == 0); ni <= d; ni++) { 
        if(mask & (1 << ni)) { 
            ret += (f2(a, is_equal & (ni == d), i + 1, mask) + 1LL * ni * pw[sz(a) - i - 1] % mod * f(a, is_equal & (ni == d), i + 1, mask) % mod) % mod; 
            ret %= mod; 
        }
        else if(__builtin_popcount(mask) < k) { 
            ret += (f2(a, is_equal & (ni == d), i + 1, mask | (1 << ni)) + 1LL * ni * pw[sz(a) - i - 1] % mod * f(a, is_equal & (ni == d), i + 1, mask | (1 << ni)) % mod) % mod;
            ret %= mod; 
        }
    }
    return ret; 
}
 
int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    pw[0] = 1; 
    for(int i = 1; i < 20; i++) { 
        pw[i] = 1LL * pw[i - 1] * 10 % mod; 
    }
    cin >> x >> y >> k;
    string a = to_string(x - 1); 
    string b = to_string(y);
    memset(dyn, -1, sizeof(dyn));
    memset(sum, -1, sizeof(sum));
    int64_t ret = 0, ctr = 0; 
    for(int i = 0;  i < sz(b); i++) { 
        memset(dyn, -1, sizeof(dyn));
        memset(sum, -1, sizeof(sum)); 
        ctr = (ctr + f( b.substr(i), (i == 0), 0, 0)) % mod;
        ret = (ret + f2(b.substr(i), (i == 0), 0, 0)) % mod; 
    }
    for(int i = 0;  i < sz(a); i++) { 
        memset(dyn, -1, sizeof(dyn));
        memset(sum, -1, sizeof(sum)); 
        ctr = (ctr + mod - f( a.substr(i), (i == 0), 0, 0)) % mod;
        ret = (ret + mod - f2(a.substr(i), (i == 0), 0, 0)) % mod; 
    }
    cout << ret << '\n'; 
    return 0; 
}