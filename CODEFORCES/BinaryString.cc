#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int64_t oo = 1e18; 
const int MOD = 1e9 + 7;

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
  friend ostream &operator<<(ostream &out, const Matrix &d) {
    for (auto x : d.data) {
      for (auto y : x) out << y << ' ';
      out << '\n';
    }
    return out;
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
          (c[i][j] += 1LL * a[i][k] % MOD * b[k][j] % MOD) %= MOD;
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
};


int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int T; 
 cin >> T; 
 for(int _case = 0; _case < T; _case++) {   
  int64_t L, R; 
  int K; 
  cin >> L >> R >> K; 
  Matrix mat(2, 2); 
  mat[0][0] = mat[0][1] = mat[1][0] = 1; 
  auto st = mat.pow(K - 1); 
  auto base = st * mat; 
  Matrix g(3, 3); 
  g[0][0] = base[0][0]; 
  g[0][1] = base[0][1]; 
  g[1][0] = base[1][0]; 
  g[1][1] = base[1][1];
  g[2][0] = g[2][1] = g[2][2] = 1;
  int64_t upper = R / K, lower = (L - 1) / K;
  int64_t ret = 0; 
  if(upper) { 
   auto upperMat = g.pow(upper);
   (ret += upperMat[2][0] % MOD * (st[0][0] + st[1][0]) % MOD + 
           upperMat[2][1] % MOD * (st[1][1] + st[0][1]) % MOD) %= MOD; 
  } 
  if(lower) { 
   auto lowerMat = g.pow(lower);
   (ret += MOD - lowerMat[2][1] % MOD * (st[0][1] + st[1][1]) % MOD) %= MOD;
   (ret += MOD - lowerMat[2][0] % MOD * (st[0][0] + st[1][0]) % MOD) %= MOD;
  } 
  printf("Case %d: %lld\n", _case + 1, ret); 
 }
 return 0; 
}