#include "bits/stdc++.h"
using namespace std;

#define int64_t long long
#define sz(x) int(x.size())

int64_t mod_pow(int64_t a, int64_t b, int64_t p) {
  int64_t res = 1;
  while (b > 0) {
    if (b & 1) res = (res * a) % p;
    a = (a * a) % p;
    b >>= 1;
  }
  return res;
}

int64_t mod_inv(int64_t a, int64_t p) { return mod_pow(a % p, p - 2, p); }

template <int mod, int root, int maxf>
struct NTT {
  vector<int64_t>rt, out; 
  NTT() { 
    int s = 32 - __builtin_clz(maxf - 1), n = (1 << s); 
    rt.resize(n); 
    rt[0] = rt[1] = 1; 
    for (int k = 2, s = 2; k < n; k *= 2, s++) {
      int64_t z[] = {1, mod_pow(root, mod >> s, mod)};
      for(int i = k; i < 2 * k; i++) { 
        rt[i] = rt[i / 2] % mod * z[i & 1] % mod;
      } 
    }
  }
  void ntt(vector<int64_t> &a) {
    int n = sz(a), L = 31 - __builtin_clz(n);
    vector<int> rev(n);
    for(int i = 0; i < n; i++) { 
      rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    }
    for(int i = 0; i < n; i++) { 
      if (i < rev[i]) swap(a[i], a[rev[i]]);
    }
    for (int k = 1; k < n; k *= 2) {
      for (int i = 0; i < n; i += 2 * k) { 
        for(int j = 0; j < k; j++) {
          int64_t z = rt[j + k] * a[i + j + k] % mod, &ai = a[i + j];
          a[i + j + k] = ai - z + (z > ai ? mod : 0);
          ai += (ai + z >= mod ? z - mod : z);
        } 
      }
    } 
  }
  vector<int64_t> conv(const vector<int64_t> &a, const vector<int64_t>  &b) {
    if (a.empty() || b.empty()) return {};
    int s = sz(a) + sz(b) - 1, B = 32 - __builtin_clz(s), n = 1 << B;
    int inv = mod_pow(n, mod - 2, mod);
    out.resize(n); 
    vector<int64_t> L(a), R(b);
    L.resize(n); 
    R.resize(n); 
    ntt(L), ntt(R);
    for(int i = 0; i < n; i++) { 
      out[-i & (n - 1)] = 1LL * L[i] * R[i] % mod * inv % mod;
    } 
    ntt(out);
    return {out.begin(), out.begin() + s};
  }
};


template <typename T>
struct CRT {
  T res;

  CRT() { res = 0, prd = 1; }

  // Add condition: res % p == r
  void add(T p, T r) {
    res += mul(r - res % p + p, euclid(prd, p).first + p, p) * prd;
    prd *= p;
    if (res >= prd) res -= prd;
  }

 private:
  T prd;
  T mul(T a, T b, T p) {
    a %= p, b %= p;
    T q = (T)((long double)a * b / p);
    T r = a * b - q * p;
    while (r < 0) r += p;
    while (r >= p) r -= p;
    return r;
  }
  pair<T, T> euclid(T a, T b) {
    if (!b) return make_pair(1, 0);
    pair<T, T> r = euclid(b, a % b);
    return make_pair(r.second, r.first - a / b * r.second);
  }
};

const int64_t MOD0 = 1004535809;  // 2^21 * 479 + 1
const int64_t MOD1 = 1012924417;  // 2^21 * 483 + 1
const int64_t MOD2 = 998244353;   // 2^20 * 476 + 1

NTT<MOD0, 3, 1 << 21> NTTA;
NTT<MOD1, 5, 1 << 21> NTTB;

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N, M, R, C;
  cin >> R >> C; 
  vector<vector<int>>f(R, vector<int>(C)); 
  for(int i = 0; i < R; i++) { 
    for(int j = 0; j < C; j++) { 
      cin >> f[i][j]; 
    }
  }
  cin >> N >> M;
  vector<vector<int>>g(N, vector<int>(M)); 
  for(int i = 0; i < N; i++) { 
    for(int j = 0; j < M; j++) { 
      cin >> g[i][j]; 
    }
  }
  if(N < R || M < C) { 
    cout << 0 << '\n'; 
    return 0; 
  }
  vector<vector<int64_t>>ret(N, vector<int64_t>(M)); 
  auto calc = [&](int c) { 
    vector<int64_t>pa(2 * N * M), pb(2 * N * M); 
    for(int i = 0; i < N; i++) { 
      for(int j = 0; j < M; j++) { 
        pa[2 * i * M + j] = (int64_t) pow(g[i][j], c); 
      }
    }
    for(int i = 0; i < R; i++) { 
      for(int j = 0; j < C; j++) { 
        pb[2 * M * (R - i - 1) + (C - j - 1)] = (f[i][j] == 0 ? f[i][j] : (int64_t) pow(f[i][j], 4 - c)); 
      }
    }
    vector<int64_t>retA = NTTA.conv(pa, pb);  
    vector<int64_t>retB = NTTB.conv(pa, pb); 
    for(int i = 0; i < N; i++) { 
      for(int j = 0; j < M; j++) { 
        int pos = (i + R - 1) * 2 * M + j + C - 1; 
        CRT<int64_t> crt;
        crt.add(MOD0, retA[pos]);
        crt.add(MOD1, retB[pos]);
        ret[i][j] += (c == 2 ? -2LL : 1) * crt.res; 
      }
    }
  }; 
  for(int i = 0; i < 3; i++) { 
    calc(i + 1); 
  }
  int ans = 0; 
  for(int i = 0; i < N - R + 1; i++) { 
    for(int j = 0; j < M - C + 1; j++) { 
      ans += (ret[i][j] == 0); 
    }
  }
  cout << ans << '\n'; 
  for(int i = 0; i < N - R + 1; i++) { 
    for(int j = 0; j < M - C + 1; j++) { 
      if(ret[i][j] == 0) cout << i + 1 << " " << j + 1 << '\n'; 
    }
  }
  return 0; 
}
