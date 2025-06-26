#include "bits/stdc++.h"
 
using namespace std; 

#define sz(x) int(x.size())

const int mod = 1e9 + 7; 
const int maxf = 2e3 + 10; 

int n, m; 
int64_t dyn[2][maxf][maxf]; 
 
int64_t f(const string &a, int is_equal, int i, int cur_m) { 
    if(i == sz(a)) return (cur_m == 0); 
    if(dyn[is_equal][i][cur_m] != -1) return dyn[is_equal][i][cur_m]; 
    int d = (is_equal ? a[i] - '0' : 9); 
    int64_t &ret = dyn[is_equal][i][cur_m]; 
    ret = 0; 
    if(i & 1) {
        ret = (n <= d ? f(a, is_equal & (n == d), i + 1, (10 * cur_m + n) % m) : 0);
    }
    else { 
        for(int ni = 0; ni <= d; ni++) if(ni != n) {
           ret += f(a, is_equal & (ni == d), i + 1, (10 * cur_m + ni) % m); 
           ret %= mod; 
        } 
    }
    return ret; 
}
 
int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    string a, b; 
    cin >> m >> n >> a >> b; 
    memset(dyn, -1, sizeof(dyn));
    int64_t ret = f(b, true, 0, 0); 
    memset(dyn, -1, sizeof(dyn)); 
    ret = (ret - f(a, true, 0, 0) + mod) % mod;
    int msum = 0, chk = true; 
    for(int i = 0; i < sz(a); i++) {
        if(i & 1) chk &= (a[i] - '0' == n); 
        else chk &= (a[i] - '0' != n); 
        msum = (msum * 10 + a[i] - '0') % m; 
    }
    ret = (ret + ((msum == 0) && chk)) % mod; 
    cout << ret << '\n'; 
    return 0; 
}