#include "bits/stdc++.h"

using namespace std;

vector<int> classic_sieve(int N) {
    vector<int> primes;
    vector<bool> isprime(N + 1, true);

    for (int n = 4; n <= N; n += 2) isprime[n] = false;
    for (int n = 3; n * n <= N; n += 2) if (isprime[n]) {
        for (int i = n * n; i <= N; i += 2 * n) {
            isprime[i] = false;
        }
    }
    for (int n = 2; n <= N; n += 1) {
        if (isprime[n]) primes.push_back(n);
    }
    return primes;
}

template <bool inverse, typename T> void divisor_transform(vector<T> &a, const vector<int> &primes) {
    int n = a.size() - 1;
    for (int i = 0, P = primes.size(); i < P && primes[i] <= n; i++) {
        if constexpr (inverse) {
            for (int p = primes[i], k = n / p; k > 0; k--) {
                a[k * p] -= a[k];
            }
        } else {
            for (int p = primes[i], k = 1; k <= n / p; k++) {
                // for (int p = primes[i], k = 1; k <= n / p; k++) {
                a[k * p] += a[k];
            }
        }
    }
}
template <bool inverse, typename T> void multiple_transform(vector<T> &a, const vector<int> &primes) {
    int n = a.size() - 1;
    for (int i = 0, P = primes.size(); i < P && primes[i] <= n; i++) {
        if constexpr (inverse) {
            for (int p = primes[i], k = 1; k <= n / p; k++) {
                a[k] -= a[k * p];
            }
        } else {
            for (int p = primes[i], k = n / p; k > 0; k--) {
                // for (int p = primes[i], k = 1; k <= n / p; k++) {
                a[k] += a[k * p];
            }
        }
    }
}
/* 
template <typename T>
auto
gcd_convolution(vector<T> a, vector<T> b, const vector<int> &primes) {
    int N = max(a.size(), b.size());
    a.resize(N, 0), b.resize(N, 0);
    vector<T> c(N);
    multiple_transform<false, double>(a, primes);
    multiple_transform<false, double>(b, primes);
    for (int i = 0; i < N; i++) {
        c[i] = a[i] * b[i];
    }
    multiple_transform<true, double>(c, primes);
    return c;
}
*/ 

template <typename T>
auto
lcm_convolution(vector<T> a, vector<T> b, const vector<int> &primes) {
    int N = max(a.size(), b.size());
    a.resize(N, 0), b.resize(N, 0);
    vector<T> c(N);
    divisor_transform<false, double>(a, primes);
    divisor_transform<false, double>(b, primes);
    for (int i = 0; i < N; i++) {
        c[i] = a[i] / b[i];
    }
    divisor_transform<true, double>(c, primes);
    return c;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> prime = classic_sieve(n);
    vector<double> w(n + 1);
    double sum = 0;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
        sum += w[i]; 
    }
    for (int i = 1; i <= n; i++) {
        w[i] = -w[i] / sum; 
    }
    w[1] = 1.0 + w[1];
    vector<double> c(n + 1);
    c[1] = 1.0; 
    auto ret = lcm_convolution(c, w, prime);
    double ans = 0; 
    for (int i = 1; i < int(ret.size()); i++) {
        ans += ret[i]; 
    }
    ans = ans - 1; 
    cout << fixed << setprecision(10) << ans << '\n';
    return 0;
}