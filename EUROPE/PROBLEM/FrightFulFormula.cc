#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())
#define int64_t long long

namespace fft {
typedef complex<double> base;
void fft(vector<base> &a, bool inv) {
  int n = a.size(), j = 0;
  vector<base> roots(n / 2);
  for (int i = 1; i < n; i++) {
    int bit = (n >> 1);
    while (j >= bit) {
      j -= bit;
      bit >>= 1;
    }
    j += bit;
    if (i < j) swap(a[i], a[j]);
  }
  double ang = 2 * acos(-1) / n * (inv ? -1 : 1);
  for (int i = 0; i < n / 2; i++) {
    roots[i] = base(cos(ang * i), sin(ang * i));
  }
  for (int i = 2; i <= n; i <<= 1) {
    int step = n / i;
    for (int j = 0; j < n; j += i) {
      for (int k = 0; k < i / 2; k++) {
        base u = a[j + k], v = a[j + k + i / 2] * roots[step * k];
        a[j + k] = u + v;
        a[j + k + i / 2] = u - v;
      }
    }
  }
  if (inv)
    for (int i = 0; i < n; i++) a[i] /= n;
}

vector<int64_t> multiply(vector<int64_t> &v, vector<int64_t> &w) {
  vector<base> fv(v.begin(), v.end()), fw(w.begin(), w.end());
  int n = 1;
  while (n < max(v.size(), w.size())) n <<= 1;
  n <<= 1;
  fv.resize(n);
  fw.resize(n);
  fft(fv, 0);
  fft(fw, 0);
  for (int i = 0; i < n; i++) fv[i] *= fw[i];
  fft(fv, 1);
  vector<int64_t> ret(n);
  for (int i = 0; i < n; i++) ret[i] = (int64_t)round(fv[i].real());
  return ret;
}
vector<int64_t> multiply(vector<int64_t> &v, vector<int64_t> &w, int mod) {
  int n = 1;
  while (n < max(v.size(), w.size())) n <<= 1;
  n <<= 1;
  vector<base> v1(n), v2(n);
  vector<base> r1(n), r2(n);
  for (int i = 0; i < v.size(); i++) {
    v1[i] = base(v[i] >> 15, v[i] & 32767);
  }
  for (int i = 0; i < w.size(); i++) {
    v2[i] = base(w[i] >> 15, w[i] & 32767);
  }
  fft(v1, 0);
  fft(v2, 0);
  for (int i = 0; i < n; i++) {
    int j = (i ? (n - i) : i);
    base ans1 = (v1[i] + conj(v1[j])) * base(0.5, 0);
    base ans2 = (v1[i] - conj(v1[j])) * base(0, -0.5);
    base ans3 = (v2[i] + conj(v2[j])) * base(0.5, 0);
    base ans4 = (v2[i] - conj(v2[j])) * base(0, -0.5);
    r1[i] = (ans1 * ans3) + (ans1 * ans4) * base(0, 1);
    r2[i] = (ans2 * ans3) + (ans2 * ans4) * base(0, 1);
  }
  fft(r1, 1);
  fft(r2, 1);
  vector<int64_t> ret(n);
  for (int i = 0; i < n; i++) {
    int64_t av = (int64_t)round(r1[i].real());
    int64_t bv = (int64_t)round(r1[i].imag()) + (int64_t)round(r2[i].real());
    int64_t cv = (int64_t)round(r2[i].imag());
    av %= mod, bv %= mod, cv %= mod;
    ret[i] = (av << 30) + (bv << 15) + cv;
    ret[i] %= mod;
    ret[i] += mod;
    ret[i] %= mod;
  }
  return ret;
}
}  

const int mod = 1000003;
const int maxf = (1 << 19);

int64_t fact[maxf], ifact[maxf];

int64_t Comb(int a, int b) {
  if (a < b || b < 0) return 0;
  return fact[a] % mod * ifact[b] % mod * ifact[a - b] % mod;
}

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

void init(void) {
  fact[0] = ifact[0] = 1;
  for (int i = 1; i < maxf; i++) {
    fact[i] = fact[i - 1] % mod * i % mod;
    ifact[i] = ifact[i - 1] % mod * fpow(i, mod - 2) % mod;
  }
  return;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  init();
  int N, A, B, C;
  cin >> N >> A >> B >> C;
  vector<int> hor(N + 1), ver(N + 1);
  int64_t ret = 0;
  for (int i = 1; i <= N; i++) {
    cin >> ver[i];
  }
  for (int i = 1; i <= N; i++) {
    cin >> hor[i];
  }
  for (int i = 2; i <= N; i++) {
    ret += ver[i] % mod * Comb(2 * N - i - 2, N - i) % mod * fpow(A, N - 1) %
           mod * fpow(B, N - i) % mod;
    ret %= mod;
  }
  for (int i = 2; i <= N; i++) {
    ret += hor[i] % mod * Comb(2 * N - i - 2, N - i) % mod * fpow(A, N - i) %
           mod * fpow(B, N - 1) % mod;
    ret %= mod;
  }
  vector<int64_t> f(N + 1), g(N + 1);
  for (int i = 2; i <= N; i++) {
    f[i] = fpow(A, N - i) % mod * ifact[N - i] % mod;
    g[i] = fpow(B, N - i) % mod * ifact[N - i] % mod;
  }
  vector<int64_t> h = fft::multiply(f, g, mod);
  for (int i = 0; i < sz(h); i++) {
    ret += C % mod * h[i] % mod * fact[2 * N - i] % mod;
    ret %= mod;
  }
  cout << ret << '\n';
  return 0;
}