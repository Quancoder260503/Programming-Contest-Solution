#include "bits/stdc++.h"

using namespace std;

#define rep(i, j, k) for (int i = j; i < k; i++)

const int maxf = 3e5 + 2;
const int mod = 998244353;

template <class T, int N>
struct Matrix {
  typedef Matrix M;
  array<array<T, N>, N> d{};
  M operator*(const M &m) const {
    M a;
    rep(i, 0, N) rep(j, 0, N) rep(k, 0, N) a.d[i][j] =
        (a.d[i][j] + d[i][k] % mod * m.d[k][j] % mod) % mod;
    return a;
  }
  vector<T> operator*(const vector<T> &vec) const {
    vector<T> ret(N);
    rep(i, 0, N) rep(j, 0, N) ret[i] =
        (ret[i] + d[i][j] % mod * vec[j] % mod) % mod;
    return ret;
  }
  M operator^(int64_t p) const {
    assert(p >= 0);
    M a, b(*this);
    rep(i, 0, N) a.d[i][i] = 1;
    while (p) {
      if (p & 1) a = a * b;
      b = b * b;
      p >>= 1;
    }
    return a;
  }
  friend ostream &operator<<(ostream &os, M p) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        os << p.d[i][j] << " ";
      }
      os << '\n';
    }
    return os;
  }
};

struct node {
  Matrix<int64_t, 2> c;
  node operator + (const node &other) {
    node ret;
    ret.c = c * other.c;
    return ret;
  }
};

node tree[maxf << 2];

Matrix<int64_t, 2> zero;
Matrix<int64_t, 2> one;
node nc; 

void build(int l, int r, int p = 1) {
  if (l == r) {
    tree[p].c = zero; 
    return;
  }
  int mid = (l + r) / 2;
  build(l, mid, 2 * p);
  build(mid + 1, r, 2 * p + 1);
  tree[p] = tree[2 * p + 1] + tree[2 * p]; 
  return; 
}

void update(int val, int pos, int l, int r, int p = 1) { 
 if(l == r) { 
  tree[p].c = (val ? one : zero); 
  return; 
 } 
 int mid = (l + r) / 2; 
 if(pos <= mid) update(val, pos, l, mid, 2 * p); 
 else update(val, pos, mid + 1, r, 2 * p + 1); 
 tree[p] = tree[2 * p + 1] + tree[2 * p]; 
 return; 
} 

node query(int L, int R, int l, int r, int p = 1) {
  if (L > r || R < l) return nc;
  if (L <= l && r <= R) return tree[p];
  int mid = (l + r) / 2;
  return query(L, R, mid + 1, r, 2 * p + 1) + query(L, R, l, mid, 2 * p);
}

vector<pair<int, int>>q[maxf]; 

int main(void) {
 ios_base::sync_with_stdio(false);
 cin.tie(0);
 cout.tie(0);
 zero.d[0][0] = 3, zero.d[0][1] = 1, zero.d[1][1] = 2; 
 one.d[0][0] = 1, one.d[0][1] = 1, one.d[1][0] = 2, one.d[1][1] = 2; 
 nc.c.d[0][0] = nc.c.d[1][1] = 1; 
 int N; 
 cin >> N; 
 build(1, N);
 int stl, str; 
 for(int i = 0, l, r; i < N; i++) {
  cin >> l >> r; 
  if(i == 0) stl = l, str = r; 
  q[l].push_back({i + 1, 1}); 
  q[r + 1].push_back({i + 1, 0}); 
 }
 int64_t ret = 0; 
 for(int i = 0; i < maxf; i++) { 
  for(auto [ind, v] : q[i]) { 
   update(v, ind, 1, N); 
  }
  vector<int64_t> vec; 
  if(stl <= i && i <= str) vec = {0, 1}; 
  else vec = {1, 0};
  (ret += (query(2, N, 1, N).c * vec)[1]) %= mod; 
 } 
 cout << ret << '\n'; 
 return 0;
}