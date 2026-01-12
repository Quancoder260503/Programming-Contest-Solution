#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int MOD = 998244353;
const int maxn = 3e5 + 2;

struct info {
  int64_t ans = 0;
  int dest;
};

struct Node {
  int64_t pw2;
  array<info, 3> data;
  Node(int val = 0) {
    pw2 = 2;
    for (int dest = 0; dest < 3; dest++) {
      if (dest == val) {
        data[dest].dest = val;
        data[dest].ans = 0;
      } else {
        data[dest].dest = 3 ^ val ^ dest;
        data[dest].ans = 1;
      }
    }
  };
  Node operator+(const Node &other) {
    Node ret;
    ret.pw2 = pw2 % MOD * other.pw2 % MOD;
    for (int dest = 0; dest < 3; dest++) {
      int64_t ansR = other.data[dest].ans;
      int destR = other.data[dest].dest;
      ansR = (ansR % MOD * pw2 % MOD + data[destR].ans) % MOD;
      ret.data[dest].ans = ansR;
      ret.data[dest].dest = data[destR].dest;
    }
    return ret;
  }
};

struct segtree {
  vector<int> a;
  int n;
  vector<Node> tree;
  segtree(vector<int> a) : a(a), n(sz(a)), tree(4 * n) { build(1, 0, n); }

  void build(int v, int vl, int vr) {
    if (vr - vl == 1) {
      tree[v] = Node(a[vl]);
      return;
    }
    int vm = (vl + vr) / 2;
    build(v << 1, vl, vm);
    build(v << 1 | 1, vm, vr);
    tree[v] = tree[v << 1] + tree[v << 1 | 1];
  }

  void update(int pos, int val) {
    a[pos] = val;
    update(1, 0, n, pos, val);
  }

  void update(int v, int vl, int vr, int pos, int val) {
    if (pos < vl || vr <= pos) {
      return;
    }
    if (vr - vl == 1) {
      tree[v] = Node(val);
      return;
    }

    int vm = (vl + vr) / 2;
    update(v << 1, vl, vm, pos, val);
    update(v << 1 | 1, vm, vr, pos, val);
    tree[v] = tree[v << 1] + tree[v << 1 | 1];
  }

  int64_t query(int l, int r) {
    auto res = query(1, 0, n, l, r);
  //  cout << res.data[0].dest << " " << res.data[0].ans << '\n';
    return res.data[0].ans;
  }

  Node query(int v, int vl, int vr, int l, int r) {
    if (l <= vl && vr <= r) {
      return tree[v];
    }
    int vm = (vl + vr) / 2;
    if (r <= vm) {
      return query(v << 1, vl, vm, l, r);
    }
    if (vm <= l) {
      return query(v << 1 | 1, vm, vr, l, r);
    }
    return query(v << 1, vl, vm, l, r) + query(v << 1 | 1, vm, vr, l, r);
  }
};

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n, q;
  cin >> n >> q;
  vector<int>a(n); 
  for(auto &x : a) { 
   cin >> x; 
   --x; 
  }
  segtree tree(a); 
  for (int i = 0; i < q; i++) {
    char type;
    cin >> type;
    if (type == 's') {
      int l, r;
      cin >> l >> r;
      auto ret = tree.query(l - 1, r);
    //  cout << ret.data[0].dest << " " << ret.data[0].ans << '\n';
       cout << ret << '\n';
    } else {
      int pos, val;
      cin >> pos >> val;
      tree.update(pos - 1, val - 1);
    }
  }
  return 0;
}