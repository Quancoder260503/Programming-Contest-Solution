#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int MOD = 1e9 + 7;
const int maxn = 3e5 + 2;

struct Node {
  int64_t mn, mx, h1, h2;
  Node(int x = 0) { 
   mn = mx = x; 
   h1 = x; 
   h2 = 1LL * x * x % MOD; 
  }
  Node operator + (const Node &other) {
    Node ret;
    ret.mn = min(mn, other.mn); 
    ret.mx = max(mx, other.mx); 
    ret.h1 = (h1 + other.h1) % MOD; 
    ret.h2 = (h2 + other.h2) % MOD; 
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

  Node query(int l, int r) {
    auto res = query(1, 0, n, l, r);
    return res; 
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
  }
  segtree tree(a); 
  for (int i = 0; i < q; i++) {
   int op, l, r; 
   cin >> op >> l >> r; 
   if(op == 1) { 
    tree.update(l - 1, r); 
   } else { 
    auto res = tree.query(l - 1, r); 
    int dist = r - l; 
    if((res.mx - res.mn) % dist) { 
     cout << "NO\n"; 
     continue;
    }
      int k = (res.mx - res.mn) / dist; 
    // mn + (mn + k) + .... + mn + k * dist
    // mn * (dist + 1) + k + 2 * k + ... + k * dist 
    // mn * (dist + 1) + k * dist * (dist + 1) / 2 
    // (dist + 1) * (mn + k * dist / 2) 
    // (dist + 1) * (mn + mx) / 2

    int64_t h1 = (res.mx + res.mn) % MOD * (dist + 1) % MOD; 

    // mn ^ 2 + (mn + dist) ^ 2 + ... + (mn + k * dist) ^ 2 
    // mn ^ 2 + mn ^ 2 + 2 * mn * (dist + 2 * dist + ... + k * dist) + (dist ^ 2 + (2 * dist) ^ 2 + ... + (k * dist) ^ 2) 
    // mn ^ 2 * (k + 1) + mn * dist * k * (k + 1)  + dist ^ 2 * k * (k + 1) * (2 * k + 1) / 6

    int64_t h2 = 6LL * res.mn % MOD * res.mn % MOD * (dist + 1) % MOD + 
                 6LL * res.mn % MOD * dist % MOD * (dist + 1) % MOD * k % MOD + 
                 1LL * k % MOD * k % MOD * dist % MOD * (dist + 1) % MOD * (2LL * dist + 1) % MOD; 
             

    if(6LL * res.h2 % MOD == h2 % MOD && 2LL * res.h1 % MOD == h1 % MOD) { 
     cout << "YES\n";    
    } else { 
     cout << "NO\n"; 
    }
   }
  }
  return 0;
}