#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int64_t oo = 0x3f3f3f3f3f3f3f3f;

template <class T>
struct LazySeg {
  int sz;
  vector<T> st, lz;
  T comb(T a, T b) { return max(a, b); }
  void init(int n) {
    sz = 1;
    while (sz < n) sz <<= 1;
    st.assign(2 * sz, 0), lz.assign(2 * sz, 0);
  }
  void pull(int i) { st[i] = comb(st[i << 1], st[i << 1 | 1]); }
  void push(int i, int l, int r) {
    st[i] += lz[i];
    if (l != r) lz[i << 1] += lz[i], lz[i << 1 | 1] += lz[i];
    lz[i] = 0;
  }
  void update(int ql, int qr, T x, int i, int l, int r) {
    push(i, l, r);
    if (ql > r || qr < l) return;
    if (ql <= l && qr >= r) {
      lz[i] += x;
      return void(push(i, l, r));
    }
    int m = (l + r) >> 1;
    update(ql, qr, x, i << 1, l, m);
    update(ql, qr, x, i << 1 | 1, m + 1, r);
    pull(i);
  }
  void update(int ql, int qr, T x) { update(ql, qr, x, 1, 0, sz - 1); }
  T query(int ql, int qr, int i, int l, int r) {
    push(i, l, r);
    if (ql > r || qr < l) return -oo;
    if (ql <= l && qr >= r) return st[i];
    int m = (l + r) >> 1;
    return comb(query(ql, qr, i << 1, l, m),
                query(ql, qr, i << 1 | 1, m + 1, r));
  }
  T query(int ql, int qr) { return query(ql, qr, 1, 0, sz - 1); }
};

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int N, M;
  cin >> N >> M;
  LazySeg<int64_t> tree;
  tree.init(N + 1);
  vector<vector<pair<int, int>>> Todo(N + 2);
  vector<int64_t> acc(N + 2);
  for (int i = 0, L, R, a; i < M; i++) {
    cin >> L >> R >> a;
    acc[L] += a;
    Todo[R + 1].push_back({L, a});
  }
  for (int i = 1; i <= N + 1; i++) {
    tree.update(0, i - 1, acc[i]);
    for (auto [x, y] : Todo[i]) {
      tree.update(0, x - 1, -y);
    }
    tree.update(i, i, tree.query(0, i - 1));
  }
  cout << tree.query(0, N) << '\n';
  return 0;
}