#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int mod = 998244353; 
const int maxf = 1e6 + 2; 

int64_t ifact[maxf], fact[maxf]; 

int64_t Comb(int a, int b) { 
    #define COMB_MAXA 5000
    #define COMB_MAXB 5000
    static int64_t combmemo[COMB_MAXA + 1][COMB_MAXB + 1]; 
    if(a < b || b < 0) return 0; 
    if(!a) return 1;
    int64_t &ret = combmemo[a][b]; 
    if(!ret) ret = (Comb(a - 1, b - 1) + Comb(a - 1, b)) % mod; 
    return ret; 
}

int64_t fpow(int64_t a, int64_t k) {
    if (!k) return 1;
    int64_t res = a, tmp = a;
    k--;
    while (k) {
        if (k & 1) {
            res = (int64_t) res % mod * tmp % mod;
        }
        tmp = (int64_t) tmp % mod * tmp % mod;
        k >>= 1;
    }
    return res;
}

int main(void) { 
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0);
    fact[0] = ifact[0] = 1; 
    for(int i = 1; i < maxf; i++) { 
        fact[i] = fact[i - 1] % mod * i % mod; 
        ifact[i] = ifact[i - 1] % mod * fpow(i, mod - 2) % mod; 
    }
    int N, M; 
    string A, B; 
    cin >> N >> M >> A >> B; 
    vector<int>ctrA(26), ctrB(26);
    for(int i = 0; i < N; i++) { 
        ctrA[A[i] - 'A']++; 
    } 
    for(int i = 0; i < M; i++) { 
        ctrB[B[i] - 'A']++; 
    }
    vector<int64_t>dyn;
    for(int i = 0; i <= min(ctrA[0], ctrB[0]); i++) { 
        while(dyn.size() <= ctrA[0] - i) dyn.push_back(0); 
        dyn[ctrA[0] - i] = ifact[i] % mod * ifact[ctrA[0] - i] % mod; 
    }
    for(int c = 1; c < 26; c++) { 
        for(int j = 1; j < sz(dyn); j++) { 
            dyn[j] = (dyn[j] + dyn[j - 1]) % mod; 
        }
        vector<int64_t>ndyn; 
        for(int i = 0; i <= min(ctrA[c], ctrB[c]); i++) { 
            while(sz(ndyn) <= ctrA[c] - i) ndyn.push_back(0); 
            if(min(ctrB[c] - i, sz(dyn) - 1) >= 0) { 
                ndyn[ctrA[c] - i] = dyn[min(ctrB[c] - i, sz(dyn) - 1)] % mod * ifact[i] % mod * ifact[ctrA[c] - i] % mod; 
            }
        }
        dyn.swap(ndyn); 
    }
    int64_t ret = dyn[0]; 
    ret = ret % mod * fact[N] % mod; 
    cout << ret << '\n'; 
    return 0; 
}

/*
  dyn[i][c] = {number of ways to fill i characters in string b knowing that c feasible position by the ith characters have been filled
  dyn[i][c] = sum of (dyn[i - 1][c - k] * C(C, k)) for k where C is the number of feasible position left to be filled using the ith characters; 
*/