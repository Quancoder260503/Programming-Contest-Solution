#include "bits/stdc++.h"

using namespace std;

const int mod = 1e9 + 7;

int main(void) {
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0); 
    int r, c; 
    cin >> r >> c; 
    vector<vector<char>>g(r, vector<char>(c)); 
    for(int i = 0; i < r; i++)
    for(int j = 0; j < c; j++) { 
        cin >> g[i][j]; 
    }
    int64_t res = 0; 
    for(int mask_iter = 0; mask_iter < (1 << r); mask_iter++) { 
        vector<vector<int64_t>>dyn(c, vector<int64_t>(2, -1)); 
        vector<int>ctr(c); 
        for(int i = 0; i < r; i++) if(mask_iter & (1 << i)) { 
            for(int j = 0; j < c; j++) { 
                ctr[j] += (g[i][j] == '.'); 
            }
        }
        function<int64_t(int, int)> func = [&](int pos, int skipable) -> int64_t { 
            if(pos == -1) return 1;
            int64_t &ret = dyn[pos][skipable]; 
            if(ret != -1) return ret;
            ret = 0; 
            if(skipable) { 
                ret += func(pos - 1, false); 
                ret %= mod; 
            }
            ret += func(pos - 1, true) % mod * ((1 << ctr[pos]) - 1) % mod; 
            ret %= mod; 
            return ret; 
        };
        res = (res + func(c - 1, true) * ((r - __builtin_popcount(mask_iter)) % 2 == 0 ? 1 : -1) + mod) % mod; 
    } 
    cout << res << '\n'; 
    return 0;
}

/*
  P(a AND b) = P(a OR b) - P(a) - P(b) ->
*/ 