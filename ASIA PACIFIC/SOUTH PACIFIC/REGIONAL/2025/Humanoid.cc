#include "bits/stdc++.h"

using namespace std;

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#define sz(x) int(x.size())
#define int64_t long long

using type = int64_t; 

struct Matrix {
  vector<vector<type>> data;
  int row() const { return data.size(); }
  int col() const { return data[0].size(); }
  auto &operator[](int i) { return data[i]; }
  const auto &operator[](int i) const { return data[i]; }
  Matrix() = default;

  Matrix(int r, int c) : data(r, vector<type>(c)) {}

  Matrix(const vector<vector<type>> &d) : data(d) {
    assert(d.size());
    int size = d[0].size();
    assert(size);
    for (auto x : d) assert(x.size() == size);
  }
  static Matrix identity(long long n) {
    Matrix a = Matrix(n, n);
    while (n--) a[n][n] = 1;
    return a;
  }
  Matrix operator*(const Matrix &b) {
    Matrix a = *this;
    assert(a.col() == b.row());
    Matrix c(a.row(), b.col());
    for (int i = 0; i < a.row(); ++i) {
      for (int j = 0; j < b.col(); ++j) {
        for (int k = 0; k < a.col(); ++k) {
          c[i][j] += a[i][k] * b[k][j];
        }
      }
    }
    return c;
  }
  Matrix pow(long long exp) {
    assert(row() == col());
    Matrix base = *this; 
    Matrix ans  = identity(row()); 
    for (; exp > 0; exp >>= 1, base = base * base)
      if (exp & 1) ans = ans * base;
    return ans;
  }
  friend ostream &operator<<(ostream &out, const Matrix &d) {
    for (auto x : d.data) {
      for (auto y : x) out << y << ' ';
      out << '\n';
    }
    return out;
  }
};

struct segtree {
  string a;
  int n;
  vector<Matrix> tree;
  segtree(int n) : n(n), tree(4 * n + 7) { build(1, 0, n); }
  Matrix getMatrix(int type) {
    Matrix ret(4, 4); 
    if(type == 0) { 
      // rotation matrix
      ret[0][1] = ret[0][2] = ret[1][2] = ret[1][3] = ret[2][2] = ret[3][3] = 1;
      ret[0][3] = ret[1][0] = -1;  
    } else if(type == 1) { 
      // swapping active and inactive 
      ret[0][2] = ret[1][3] = ret[2][0] = ret[3][1] = 1;  
    }
    return ret;
  }
  void build(int v, int vl, int vr) {
    if (vr == vl) {
      tree[v]  = getMatrix(0); 
      return;
    }
    int vm = (vl + vr) / 2;
    build(v << 1, vl, vm);
    build(v << 1 | 1, vm + 1, vr);
    tree[v] = tree[v << 1 | 1] * tree[v << 1];
    return; 
  }
  void update(int v, int vl, int vr, int pos) {
    if (vl == vr) {
      tree[v] = getMatrix(1) * getMatrix(0); 
      return;
    }
    int vm = (vl + vr) / 2;
    if(pos <= vm) update(v << 1, vl, vm, pos);
    else          update(v << 1 | 1, vm + 1, vr, pos);
    tree[v] = tree[v << 1 | 1] * tree[v << 1];
    return; 
  }
};

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0); 
  int n, t; 
  cin >> n >> t; 
  segtree tree(t + 1);
  tree.build(1, 1, t);  
  Matrix fixed(4, 4); 
  fixed[2][0] = 1; 
  for(int i = 0, x; i < n; i++) { 
   cin >> x;  
   tree.update(1, 1, t, x); 
   auto ret = tree.tree[1] * fixed;
   if(i % 2 == 0) cout << ret[2][0] << " " << ret[3][0] << '\n'; 
   else cout << ret[0][0] << " " << ret[1][0] << '\n'; 
  }
  return 0;
}

