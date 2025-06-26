#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())
const int mod = 998244353; 
const int maxf = 2e5 + 10; 

int64_t fact[maxf], ifact[maxf]; 

int64_t Comb(int a, int b) { 
    if(a == b) return 1; 
    if(a < b || b < 0) return 0; 
    return fact[a] % mod * ifact[b] % mod * ifact[a - b] % mod; 
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

void init(void) {
    fact[0] = ifact[0] = 1; 
    for(int i = 1; i < maxf; i++) { 
        fact[i]  = fact[i - 1] % mod * i % mod; 
        ifact[i] = ifact[i - 1] % mod * fpow(i, mod - 2) % mod; 
    }
    return; 
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    cout.tie(0);
    int P, S, R; 
    init(); 
    cin >> P >> S >> R; 
    auto g = [&](int total_score, int max_score, int player) {
        int64_t ret = 0;
        int sign = 1;  
        for(int i = 0; i <= player; i++) {
            ret = (ret + mod + sign * (Comb(player, i) % mod * 
                                       Comb(total_score + player - 1 - i * max_score, player - 1) % mod)) % mod; 
            sign = -sign; 
        }  
        return ret;
    }; 
    int64_t ret = 0; 
    for(int score = R; score <= S; score++) { 
        for(int num = 1; num <= P; num++) { 
            ret = (ret + Comb(P - 1, num - 1) % mod * fpow(num, mod - 2) % mod * 
                           g(S - num * score, score, P - num) % mod) % mod; 
         //   cout << g(S - num * score, score, P - num) << " " << S - num * score << " " << score << " " << P - num << '\n'; 
        }
    }
    ret = ret % mod * fpow(Comb(S - R + P - 1, P - 1), mod - 2) % mod; 
    cout << ret << '\n'; 
    return 0;
}

/*
*/