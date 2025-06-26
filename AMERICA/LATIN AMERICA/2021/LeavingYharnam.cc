#include "bits/stdc++.h"

using namespace std;

const int maxf = 2e6 + 10; 
const int mod  = 1e9 + 7; 

int64_t ifact[maxf], fact[maxf], dyn[maxf]; 

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
        fact[i] = fact[i - 1] % mod * i % mod; 
        ifact[i] = ifact[i - 1] % mod * fpow(i, mod - 2) % mod; 
    } 
    return; 
}

int64_t Comb(int a, int b) { 
    if(b < 0 || a < b) return 0; 
    return fact[a] % mod * ifact[b] % mod * ifact[a - b] % mod; 
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0); 
    cout.tie(0); 
    init(); 
    int N, G, I, E;
    cin >> N >> G >> I >> E; 
    int64_t ret = 0; 
    G = min(G, 2 * N); 
    E = min(E, 2 * N - G); 
    I = min(I, 2 * N - G - E); 
    for(int pair_easy = 0; 2 * pair_easy <= G; pair_easy++) { 
        int single_easy = G - 2 * pair_easy; 
        int rem_seat = N - pair_easy - single_easy;
        int x = G; 
        if(single_easy < 0 || rem_seat < 0) continue;  
        int64_t ways = Comb(N, pair_easy) % mod * Comb(N - pair_easy, single_easy) % mod;
        ways = ways % mod * fpow(2, single_easy) % mod * ifact[2 * N] % mod * fact[2 * N - G] % mod * fact[G] % mod;
        int remE = 0;  
        if(E <= single_easy) { 
            x += E;
            single_easy = single_easy - E; 
        }
        else { 
            if((E - single_easy) % 2 == 1) remE++; 
            x += E - remE; 
            rem_seat = rem_seat - (E - single_easy) / 2 - remE; 
            single_easy = remE; 
        }
        if(rem_seat >= I) { 
            x += I; 
        }
        else { 
            x += rem_seat; 
            int rem_I = I - rem_seat;
            if(remE) { 
                x++; 
                single_easy--; 
                rem_I--; 
            }
            if(rem_I > single_easy) x = x - rem_I + single_easy; 
        }
        ret += x % mod * ways % mod; 
        ret %= mod; 
    }
    cout << ret << '\n'; 
    return 0; 
}