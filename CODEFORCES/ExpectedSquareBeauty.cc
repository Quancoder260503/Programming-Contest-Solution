#include "bits/stdc++.h"

using namespace std;

const int maxf = 1e6 + 2;
const int mod = 1e9 + 7;

int64_t ifact[maxf], fact[maxf], dyn[maxf];
int n, tc;

int64_t fpow(int64_t a, int64_t k) {
  if (!k) return 1;
  int64_t res = a, tmp = a;
  k--;
  while (k) {
    if (k & 1) {
      res = (int64_t)res % mod * tmp % mod;
    }
    tmp = (int64_t)tmp % mod * tmp % mod;
    k >>= 1;
  }
  return res;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<int> l(n), r(n);
  vector<int64_t> p(n);
  for (int i = 0; i < n; i++) cin >> l[i];
  for (int i = 0; i < n; i++) cin >> r[i];
  int64_t sum = 1;
  p[0] = 1;
  for (int i = 1; i < n; i++) {
    int64_t num = max({0, min(r[i], r[i - 1]) - max(l[i], l[i - 1]) + 1});
    int64_t den =
        1LL * (r[i] - l[i] + 1) % mod * (r[i - 1] - l[i - 1] + 1) % mod;
    p[i] = (1 + mod - num % mod * fpow(den, mod - 2) % mod) % mod;
    sum = (sum + p[i]) % mod;
  }
  int64_t ret = 0;
  auto calc = [&](int id) -> int64_t {
    int64_t res = 0, tprob = 0;
    if (id > 0) {
      int lb = max({l[id], l[id - 1], l[id + 1]});
      int rb = min({r[id], r[id - 1], r[id + 1]});
      if (lb <= rb) {
        int64_t num = (rb - lb + 1);
        int64_t den = 1LL * (r[id] - l[id] + 1) % mod *
                      (r[id - 1] - l[id - 1] + 1) % mod *
                      (r[id + 1] - l[id + 1] + 1) % mod;
        tprob = num % mod * fpow(den, mod - 2) % mod;
      }
    }

    return (mod + tprob + p[id] + p[id + 1] - 1) % mod;
  };
  for (int i = 0; i < n; i++) {
    int64_t prob = p[i] % mod *
                   (1 + sum - (i ? p[i - 1] : 0) % mod -
                    (i + 1 < n ? p[i + 1] : 0) % mod - p[i] % mod + mod) %
                   mod;
    while (prob < 0) prob += mod;
    ret = (ret + prob) % mod;
    if (0 < i) {
      ret += calc(i - 1);
      ret %= mod;
    }
    if (i + 1 < n) {
      ret += calc(i);
      ret %= mod;
    }
  }
  cout << ret << '\n';
  return 0;
}