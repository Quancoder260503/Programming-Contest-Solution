#include "bits/stdc++.h"

using namespace std; 

const int mod = 1e9 + 7; 
const int maxf = 2e5 + 10; 

int64_t fact[maxf], ifact[maxf]; 

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

void init(void) {
    fact[0] = ifact[0] = 1; 
    for(int i = 1; i < maxf; i++) { 
        fact[i]  = fact[i - 1] % mod * i % mod; 
        ifact[i] = ifact[i - 1] % mod * fpow(i, mod - 2) % mod; 
    }
    return; 
}


int main(void) {
    ios_base::sync_with_stdio(0); 
    cin.tie(0); 
    cout.tie(0); 
    init(); 
    string S;
    cin >> S; 
    int N = S.size();
    S = " " + S;  // Life - Hack  
    vector<vector<int>>prefix(N + 1, vector<int>(26)); 
    for(int i = 1; i <= N; i++) { 
        for(int j = 0; j < 26; j++) { 
            prefix[i][j] = prefix[i - 1][j] + (S[i] == char(j + 'a')); 
        }
    }
    int Q; 
    cin >> Q; 
    for(int iter = 0; iter < Q; iter++) { 
        vector<int>ctr(26); 
        int a, b; 
        cin >> a >> b; 
        for(int ch = 0; ch < 26; ch++) { 
            ctr[ch] += prefix[b][ch] - prefix[a - 1][ch]; 
        }
        int opt_length = 0, odd = 0; 
        for(int ch = 0; ch < 26; ch++) { 
            odd += (ctr[ch] & 1); 
            opt_length += ctr[ch] / 2; 
        } 
        int64_t ret = fact[opt_length]; 
        for(int ch = 0; ch < 26; ch++) { 
            ret = ret % mod * ifact[ctr[ch] / 2] % mod; 
        }
        if(odd > 0) { ret = ret % mod * odd % mod; } 
        cout << ret << '\n'; 
    }
    return 0; 
}