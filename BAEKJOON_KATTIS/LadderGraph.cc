#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int mod = 1e9 + 7; 

using type = int64_t;

struct Matrix {
  vector<vector<type>> data;
  int row() const { return data.size(); }
  int col() const { return data[0].size(); }
  auto &operator[](int i) { return data[i]; }
  const auto &operator[](int i) const { return data[i]; }
  Matrix() = default;

  Matrix(int r, int c) : data(r, vector<type>(c, 0)) {}

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
          c[i][j] += a[i][k] % mod * b[k][j] % mod;
          c[i][j] %= mod; 
        }
      }
    }
    return c;
  }
  Matrix pow(long long exp) {
    assert(row() == col());
    Matrix base = *this, ans = *this;
    for (; exp > 0; exp >>= 1, base = base * base)
      if (exp & 1) ans = ans * base;
    return ans;
  }
  void reduce(void) {
    for (int i = 0; i < sz(data); i++) {
      type sum = 0.0;
      for (int j = 0; j < sz(data[i]); j++) {
        sum += data[i][j];
      }
      for (int j = 0; j < sz(data[i]); j++) {
        data[i][j] /= sum;
      }
    }
    return;
  }
};

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int64_t N; 
  cin >> N; 
  Matrix mat(2, 2); 
  mat[0][0] = mat[1][0] = 1; 
  mat[0][1] = 2; 
  mat[1][1] = 4; 
  cout << (mat.pow(N - 1))[1][0] << '\n'; 
  return 0;
}
