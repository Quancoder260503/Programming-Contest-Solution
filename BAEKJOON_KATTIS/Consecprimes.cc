#include "bits/stdc++.h"

using namespace std; 

inline uint64_t mod_mult64(uint64_t a, uint64_t b, uint64_t m) {
    return __int128_t(a) * b % m;
}
uint64_t mod_pow64(uint64_t a, uint64_t b, uint64_t m) {
    uint64_t ret = (m > 1);
    for (;;) {
        if (b & 1) ret = mod_mult64(ret, a, m);
        if (!(b >>= 1)) return ret;
        a = mod_mult64(a, a, m);
    }
}

// Works for all primes p < 2^64
bool is_prime(uint64_t n) {
    if (n <= 3) return (n >= 2);
    static const uint64_t small[] = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67,
        71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139,
        149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199,
    };
    for (size_t i = 0; i < sizeof(small) / sizeof(uint64_t); ++i) {
        if (n % small[i] == 0) return n == small[i];
    }

    // Makes use of the known bounds for Miller-Rabin pseudoprimes.
    static const uint64_t millerrabin[] = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37,
    };
    static const uint64_t A014233[] = {  // From OEIS.
        2047LL, 1373653LL, 25326001LL, 3215031751LL, 2152302898747LL,
        3474749660383LL, 341550071728321LL, 341550071728321LL,
        3825123056546413051LL, 3825123056546413051LL, 3825123056546413051LL, 0,
    };
    uint64_t s = n-1, r = 0;
    while (s % 2 == 0) {
        s /= 2;
        r++;
    }
    for (size_t i = 0, j; i < sizeof(millerrabin) / sizeof(uint64_t); i++) {
        uint64_t md = mod_pow64(millerrabin[i], s, n);
        if (md != 1) {
            for (j = 1; j < r; j++) {
                if (md == n-1) break;
                md = mod_mult64(md, md, n);
            }
            if (md != n-1) return false;
        }
        if (n < A014233[i]) return true;
    }
    return true;
}
// }}}
const uint64_t LIM = 10'000'000'000'000'000'000ULL;
const int SQRT = 4'000'000; 
vector<uint64_t>cand; 

void get_prime(void) { 
    vector<vector<int>>g(SQRT); 
    vector<uint64_t>prime; 
    for(int i = 2; i < SQRT; i++) {
        if(g[i].empty()) { 
            prime.push_back(i); 
            for(int j = i; j < SQRT; j += i) g[j].push_back(i); 
        }
    }
    for(int i = 0; i < prime.size(); i++) { 
        int start = i; 
        uint64_t prod = 1; 
        while(start < prime.size()) { 
            if(prod > LIM / prime[start]) break; 
            prod = prod * prime[start++]; 
            cand.push_back(prod); 
        }
    }
    sort(cand.begin(), cand.end()); 
    return; 
}

map<uint64_t, uint64_t> cache_next_prime, cache_prev_prime;

// returns smallest prime >= n
uint64_t next_prime(uint64_t n) {
    if (n <= 2) return 2;

    auto orig = n;
    auto it = cache_next_prime.upper_bound(n);
    if (it != cache_next_prime.begin()) {
        --it;
        if (it->second >= n) {
            return it->second;
        }
    }

    while (n % 6 != 1 && n % 6 != 5) ++n;
    bool stt = n % 6 == 1;
    while (!is_prime(n)) n += stt ? 4 : 2, stt ^= 1;
    return cache_next_prime[orig] = n;
}

uint64_t prev_prime(uint64_t n) {
    assert(n > 1);
    if (n == 2) return 2;
    if (n <= 4) return 3;
    if (n <= 6) return 5;

    auto it = cache_prev_prime.lower_bound(n);
    if (it != cache_prev_prime.end() && it->second <= n) {
        return it->second;
    }
    auto orig = n;

    while (n % 6 != 1 && n % 6 != 5) n--;
    bool stt = n % 6 == 1;
    while (true) {
        if (is_prime(n)) return cache_prev_prime[orig] = n;
        n -= stt ? 2 : 4;
        stt ^= 1;
    }
}

map<uint64_t, int>ret; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int tc;
    cin >> tc; 
    get_prime(); 
    vector<string>state = {"UGLY", "NICE"}; 
    for(int j = 0; j < tc; j++) { 
        uint64_t x;
        cin >> x; 
        if(ret.count(x)) { 
            cout << state[ret[x]] << '\n'; 
            continue; 
        }
        if(is_prime(x)) { 
            ret[x] = true; 
        }
        else { 
            auto it = lower_bound(cand.begin(), cand.end(), x); 
            if(it != cand.end() && (*it) == x) { 
                ret[x] = true;
                goto done;  
            }
            uint64_t y = (uint64_t) sqrt(x) + 3; 
            while(y * y > x) y--; 
            uint64_t nxt = next_prime(y + 1); 
            if(x % nxt != 0 || !is_prime(x / nxt)) { 
                ret[x] = false; 
                goto done; 
            }
            ret[x] = (x == (uint64_t) nxt * prev_prime(y)); 
        }
    done:; 
        cout << state[ret[x]] << '\n'; 
    }
    return 0;
}