#include "bits/stdc++.h"

using namespace std;

const int maxf = 1e6 + 1;
const int LOG = 40;

inline uint64_t
mod_mult64(uint64_t a, uint64_t b, uint64_t m) {
    return __int128_t(a) * b % m;
}
uint64_t
mod_pow64(uint64_t a, uint64_t b, uint64_t m) {
    uint64_t ret = (m > 1);
    for (;;) {
        if (b & 1) ret = mod_mult64(ret, a, m);
        if (!(b >>= 1)) return ret;
        a = mod_mult64(a, a, m);
    }
}

// Works for all primes p < 2^64
bool
is_prime(uint64_t n) {
    if (n <= 3) return (n >= 2);
    static const uint64_t small[] = {
        2,  3,  5,   7,   11,  13,  17,  19,  23,  29,  31,  37,  41,  43,  47,  53,  59,  61,  67,  71,  73,  79,  83,
        89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199,
    };
    for (size_t i = 0; i < sizeof(small) / sizeof(uint64_t); ++i) {
        if (n % small[i] == 0) return n == small[i];
    }

    // Makes use of the known bounds for Miller-Rabin pseudoprimes.
    static const uint64_t millerrabin[] = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37,
    };
    static const uint64_t A014233[] = {
        // From OEIS.
        2047LL,
        1373653LL,
        25326001LL,
        3215031751LL,
        2152302898747LL,
        3474749660383LL,
        341550071728321LL,
        341550071728321LL,
        3825123056546413051LL,
        3825123056546413051LL,
        3825123056546413051LL,
        0,
    };
    uint64_t s = n - 1, r = 0;
    while (s % 2 == 0) {
        s /= 2;
        r++;
    }
    for (size_t i = 0, j; i < sizeof(millerrabin) / sizeof(uint64_t); i++) {
        uint64_t md = mod_pow64(millerrabin[i], s, n);
        if (md != 1) {
            for (j = 1; j < r; j++) {
                if (md == n - 1) break;
                md = mod_mult64(md, md, n);
            }
            if (md != n - 1) return false;
        }
        if (n < A014233[i]) return true;
    }
    return true;
}

int
main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int64_t n;
    cin >> n;
    if (n == 1) {
        cout << "N\n";
        return 0;
    }
    for (int i = 2; i < maxf; i++) {
        if (is_prime(i)) {
            int64_t c = 1;
            for (int j = 0; j < LOG; j++) {
                if (c == n) {
                    cout << (j & 1 ? 'Y' : 'N') << "\n";
                    return 0;
                }
                if (c > n) break;
                c = 1LL * c * i;
            }
            if (n % i == 0) {
                if (is_prime(n / i)) {
                    cout << "Y\n";
                    return 0;
                }
            }
        }
    }
    cout << (is_prime(n) ? "Y" : "N") << '\n';
    return 0;
}