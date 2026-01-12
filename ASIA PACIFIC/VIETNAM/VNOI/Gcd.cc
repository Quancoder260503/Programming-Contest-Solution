#include "bits/stdc++.h"

using namespace std;

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#define sz(x) int(x.size())

using type = __int128_t;

int64_t A, B, MOD; 

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
  cin >> A >> B >> MOD;
  int64_t g = gcd(A, B); 
  Matrix fib(2, 2);
  fib[0][0] = fib[0][1] = fib[1][0] = 1; 
  fib = fib.pow(g - 1); 
  cout << int64_t(fib[0][0]) << '\n';  
  return 0; 
}