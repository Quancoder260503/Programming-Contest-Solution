#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())
#define ctoi(x) (x - '0')

const int mod = 1e9 + 7; 

int main(void) {
    ios_base::sync_with_stdio(0);
    cin.tie(0); 
    int n; 
    cin >> n;
    string a, b;
    cin >> a >> b; 
    vector<vector<vector<int64_t>>>dyn(n, vector<vector<int64_t>>(2, vector<int64_t>(2, -1))); 
    function<int64_t(int, int, int)> func = [&](int pos, int sa, int sb) -> int64_t { 
        if(pos == n) return (sa && sb); 
        int64_t &ret = dyn[pos][sa][sb]; 
        if(ret != -1) return ret; 
        ret = 0; 
        if(a[pos] == '?' && b[pos] == '?') { 
            ret += (45 * func(pos + 1, sa | 1, sb) + 45 * func(pos + 1, sa, sb | 1) + 10 * func(pos + 1, sa, sb)) % mod;
            ret %= mod;  
        } 
        else if(a[pos] == '?') { 
            ret += ((9 - ctoi(b[pos])) * func(pos + 1, sa | 1, sb) + ctoi(b[pos]) * func(pos + 1, sa, sb | 1) + func(pos + 1, sa, sb)) % mod; 
            ret %= mod; 
        }
        else if(b[pos] == '?') { 
            ret += ((9 - ctoi(a[pos])) * func(pos + 1, sa, sb | 1) + ctoi(a[pos]) * func(pos + 1, sa | 1, sb) + func(pos + 1, sa, sb)) % mod; 
            ret %= mod; 
        }
        else { 
            ret = (a[pos] == b[pos] ? func(pos + 1, sa, sb) : 
                  (a[pos] <  b[pos] ? func(pos + 1, sa, sb | 1) : func(pos + 1, sa | 1, sb))); 
            ret %= mod; 
        }
        return ret;
    };
    cout << func(0, 0, 0) << '\n';  
    return 0; 
}