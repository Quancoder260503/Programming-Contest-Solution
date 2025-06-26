#include "bits/stdc++.h"

using namespace std; 

const int mod = 998244353; 

int64_t Comb(int a, int b) {
    #define COMB_MAXA 5000
    #define COMB_MAXB 5000 
    if(b > a || b < 0) return 0; 
    if(!a) return 1; 
    static int64_t combmemo[COMB_MAXA + 1][COMB_MAXB + 1];
    int64_t &ret = combmemo[a][b]; 
    if(!ret) ret = Comb(a - 1, b - 1) + Comb(a - 1, b); 
    ret %= mod; 
    return ret; 
}

int64_t fpow(int64_t a, int64_t k) {
    if (!k) return 1;
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
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, x; 
    cin >> n >> x;
    vector<vector<int64_t>>dyn(n + 1, vector<int64_t>(x + 1));
    dyn[n][0] = 1; 
    for(int i = n; i > 1; i--) { 
        for(int j = 0; j < x; j++) { 
            if(!dyn[i][j]) continue; 
            for(int k = i; k >= 0; k--) { 
                dyn[k][min(x, i + j - 1)] += dyn[i][j] % mod * Comb(i, i - k) % mod * fpow(min(x, i + j - 1) - j, i - k) % mod; 
                dyn[k][min(x, i + j - 1)] %= mod; 
            }
        }
    }
    int64_t ret = 0; 
    for(int i = 0; i <= x; i++) { 
        ret += dyn[0][i]; 
        ret %= mod; 
    }
    cout << ret << '\n'; 
    return 0; 
}

/*
    dyn[i][j] = {number of ways to construct the health array such that there are ith survivors left and have dealt
                 j damage}
*/