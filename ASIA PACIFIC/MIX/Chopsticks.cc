#include "bits/stdc++.h"

using namespace std;

#define int64_t long long
#define sz(x) int(x.size())

const int MOD = 998244353;
const int maxn = 5e5 + 10; 
const int PRIMITIVE_ROOT = 3;
const int LOG = 20; 

int a[maxn]; 

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

NTT<MOD, PRIMITIVE_ROOT, 1 << LOG>ntt; 

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int n, m; 
  cin >> n >> m; 
  int64_t sum = 0; 
  for(int i = 0; i < m; i++) { 
    cin >> a[i];
    sum += a[i];  
  }
  assert(sum >= 0); 
  vector<int64_t>p(2 * n + 2), q(2 * n + 2); 
  p[0] = q[0] = 1; 
  for(int i = 1; i <= 2 * n; i++) { 
   if(i <= 2 * n + 1) { 
    p[i] = p[i - 1] * (2 * n - i + 1) % MOD * mod_inv(i, MOD) % MOD; 
   } 
   if(sum + 1 >= 2 * n + i) { 
    q[i] = (sum - 2 * n - i + 1) % MOD * mod_inv(i, MOD) % MOD * q[i - 1] % MOD;
   }   
  }
  for(int i = 0; i <= 2 * n; i++) { 
   if(i % 2 == 0) p[i] = 0; 
  }
  vector<int64_t>res = ntt.conv(p, q); 
  int64_t ans = 0;
  p[2 * n] = 1;  
  for(int i = 2 * n - 1; i >= 0; i--) { 
   p[i] = (sum - i) % MOD * mod_inv(i + 1, MOD) % MOD * p[i + 1] % MOD; 
  }
  for(int i = 0; i < m; i++) {
   ans += res[a[i]] * p[a[i]] % MOD;   
   ans %= MOD; 
  }
  ans = ans * mod_inv(2, MOD) % MOD; 
  cout << ans << '\n';
  return 0; 
}
