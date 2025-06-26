#include "bits/stdc++.h"

using namespace std;

const int mod = 998244353;

int64_t
fpow(int64_t a, int64_t k) {
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

int
main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int64_t inv6 = fpow(6, mod - 2);
    int64_t inv2 = fpow(2, mod - 2);
    auto sum_of_linear = [&](int l, int r) { return (1LL * r % mod * (r + 1) % mod - 1LL * l % mod * (l - 1) % mod + mod) % mod * inv2 % mod; };
    auto sum_of_square = [&](int l, int r) { return (1LL * r % mod * (r + 1) % mod * (2 * r + 1) % mod - 1LL * l % mod * (l - 1) % mod * (2 * l - 1) % mod + mod) % mod * inv6 % mod; };
    int n;
    cin >> n;
    vector<int> l(n), r(n);
    vector<int64_t> dyn(n);
    for (int i = 0; i < n; i++)
        cin >> l[i] >> r[i];
    int64_t sum = 0;
    for (int i = 1; i < n; i++) {
        if (max(l[i], l[i - 1]) > min(r[i], r[i - 1])) continue;
        int64_t num = sum_of_linear(max(l[i], l[i - 1]), min(r[i], r[i - 1]));
        int64_t den = 1LL * (r[i] - l[i] + 1) % mod * (r[i - 1] - l[i - 1] + 1) % mod;
        dyn[i] = 1LL * num % mod * fpow(den, mod - 2) % mod;
        sum = (sum + dyn[i]) % mod;
    }
    int64_t ret = 0;
    for (int i = 1; i < n; i++) {
        if (max(l[i], l[i - 1]) > min(r[i], r[i - 1])) continue;
        int64_t den = 1LL * fpow(r[i] - l[i] + 1, mod - 2) % mod * fpow(r[i - 1] - l[i - 1] + 1, mod - 2) % mod;
        ret = (ret + 1LL * sum_of_square(max(l[i], l[i - 1]), min(r[i], r[i - 1])) % mod * den % mod) % mod;
        int64_t csum = dyn[i] % mod * (sum - (i ? dyn[i - 1] : 0) % mod - (i + 1 < n ? dyn[i + 1] : 0) % mod - dyn[i] % mod + mod) % mod;
        while (csum < 0)
            csum += mod;
        ret = (ret + csum) % mod;
        if (i > 1) {
            int lb = max({l[i], l[i - 1], l[i - 2]});
            int rb = min({r[i], r[i - 1], r[i - 2]});
            if (lb <= rb) {
                int64_t den = 1LL * fpow(r[i] - l[i] + 1, mod - 2) % mod * fpow(r[i - 1] - l[i - 1] + 1, mod - 2) % mod * fpow(r[i - 2] - l[i - 2] + 1, mod - 2) % mod;
                int64_t num = sum_of_square(lb, rb);
                ret = (ret + 1LL * num % mod * den % mod) % mod;
            }
        }
        if (i + 1 < n) {
            int lb = max({l[i], l[i - 1], l[i + 1]});
            int rb = min({r[i], r[i - 1], r[i + 1]});
            if (lb <= rb) {
                int64_t den = 1LL * fpow(r[i] - l[i] + 1, mod - 2) % mod * fpow(r[i - 1] - l[i - 1] + 1, mod - 2) % mod * fpow(r[i + 1] - l[i + 1] + 1, mod - 2) % mod;
                int64_t num = sum_of_square(lb, rb);
                ret = (ret + 1LL * num % mod * den % mod) % mod;
            }
        }
    }
    while (ret < 0)
        ret += mod;
    cout << ret << '\n';
    return 0;
}