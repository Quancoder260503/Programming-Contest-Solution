#include "bits/stdc++.h"

using namespace std;

// Bipartite Matching {{{
struct Matching {
    int n;
    vector<vector<int>> ke;
    vector<int> seen;
    vector<int> matchL, matchR;
    int iteration;

    Matching(int _n) : n(_n), ke(_n), seen(_n, false), matchL(_n, -1), matchR(_n, -1), iteration{0} {}

    void addEdge(int u, int v) { ke[u].push_back(v); }

    bool dfs(int u) {
        seen[u] = iteration;
        for (int v : ke[u]) {
            if (matchR[v] < 0) {
                matchR[v] = u;
                matchL[u] = v;
                return true;
            }
        }
        for (int v : ke[u]) {
            if (seen[matchR[v]] != iteration && dfs(matchR[v])) {
                matchR[v] = u;
                matchL[u] = v;
                return true;
            }
        }
        return false;
    }

    int match() {
        int res = 0;
        int newMatches = 0;
        do {
            iteration++;
            newMatches = 0;
            for (int u = 0; u < n; u++) {
                if (matchL[u] < 0 && dfs(u)) ++newMatches;
            }
            res += newMatches;
        } while (newMatches > 0);
        return res;
    }
};

// Rabin miller {{{
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
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199,
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
        2047LL, 1373653LL, 25326001LL, 3215031751LL, 2152302898747LL, 3474749660383LL, 341550071728321LL, 341550071728321LL, 3825123056546413051LL, 3825123056546413051LL, 3825123056546413051LL, 0,
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
// }}}
// }}}

int
main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a;
    int flag = false; 
    for (int i = 0, x; i < n; i++) {
        cin >> x;
        if (x > 1) a.push_back(x);
        if(x == 1) {
            flag = true; 
        }
    }
    if (flag) a.push_back(1);
    n = a.size(); 
    Matching mc(n);
    for (int i = 0; i < n; i++) if (a[i] % 2 == 0) {
        for (int j = 0; j < n; j++)
            if (a[j] % 2 == 1 && is_prime(a[i] + a[j])) {
                mc.addEdge(i, j);
            }
    }
    cout << n - mc.match() << '\n';
    return 0;
}