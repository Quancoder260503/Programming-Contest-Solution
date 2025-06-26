#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())
#define int64_t long long

const int64_t oo = 0x3f3f3f3f3f3f3f3f;
const int mod = 998244353;
const int maxf = 2e5 + 10;


template <class T>
struct LazySeg {
  int sz;
  vector<T> lz, mul;
  T comb(T a, T b) { return (a + b) % mod; }
  void init(int n) {
    sz = 1;
    while (sz < n) sz <<= 1;
    lz.assign(2 * sz, 0), mul.assign(2 * sz, 1);
    return; 
  }
  void push(int i, int l, int r) {
    if (l != r && (mul[i] != 1 || lz[i] != 0)) { 
      lz[i << 1]      = (lz[i << 1] % mod * mul[i] % mod + lz[i]) % mod;
      mul[i << 1]     = mul[i << 1] % mod * mul[i] % mod; 
      lz[i << 1  | 1] = (lz[i << 1 | 1] % mod * mul[i] % mod + lz[i]) % mod; 
      mul[i << 1 | 1] = mul[i << 1 | 1] % mod * mul[i] % mod;
      mul[i] = 1; 
      lz[i] = 0;
    } 
    return; 
  }
  void update(int ql, int qr, T x, T y, int i, int l, int r) {
    push(i, l, r);
    if (ql > r || qr < l) return;
    if (ql <= l && qr >= r) {
      lz[i]  = (lz[i] * x + y) % mod;
      mul[i] = mul[i] % mod * x % mod; 
      return void(push(i, l, r));
    }
    int m = (l + r) >> 1;
    update(ql, qr, x, y, i << 1, l, m);
    update(ql, qr, x, y, i << 1 | 1, m + 1, r);
    return; 
  }
  void update(int ql, int qr, T x, T y) { update(ql, qr, x, y, 1, 0, sz - 1); }
  T query(int pos, int i, int l, int r) {
    push(i, l, r);
    if (l == r) { 
      return (lz[i] + mul[i]) % mod;
    }
    int m = (l + r) >> 1;
    if(pos <= m) return query(pos, i << 1, l, m); 
    else       return query(pos, i << 1 | 1, m + 1, r);
    return -1; 
  }
  T query(int pos) { return query(pos, 1, 0, sz - 1); }
};

LazySeg<int64_t>tree; 

int N, Q; 

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
  cin.tie(0); 
  cout.tie(0); 
  cin >> N >> Q;
  tree.init(N + 2);  
  for(int i = 1, x; i <= N; i++) { 
    cin >> x;
    tree.update(i, i, 0, x); 
  }
  for(int iter = 0, L, R, x; iter < Q; iter++) { 
    cin >> L >> R >> x; 
    int64_t Prob = fpow(R - L + 1, mod - 2); 
    tree.update(L, R, (1 + mod - Prob) % mod, Prob % mod * x % mod); 
  }
  for(int i = 1; i <= N; i++) { 
    cout << tree.query(i) << " ";
  }
  cout << '\n'; 
  return 0; 
}