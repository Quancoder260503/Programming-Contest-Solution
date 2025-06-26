#include "bits/stdc++.h"

using namespace std;

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#define sz(x) int(x.size())

const int MOD = 998244353; 

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
  vector<int64_t> operator*(const vector<int64_t>&vec) {
    Matrix a = *this;
    vector<int64_t>ret(sz(vec)); 
    for (int i = 0; i < a.row(); ++i) {
     for (int j = 0; j < a.col(); ++j) {
      (ret[i] += 1LL * a[i][j] % MOD * vec[j] % MOD) %= MOD; 
     }
    }
    return ret;
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

const int LOG = 60; 

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N, T; 
  Matrix base(6, 6); 
  base[0][0] = 1; 
  base[1][0] = base[2][1] = base[3][2] = base[4][3] = base[5][4] = 1;
  base[1][3] = base[1][4] = base[1][5] = mod_inv(3, MOD); 
  vector<int64_t>coef(6, 1);
  coef[0] = 1; 
  coef[1] = (4LL * mod_inv(3, MOD)) % MOD; 
  coef[2] = 1; 
  coef[3] = 1; 
  coef[4] = 1; 
  coef[5] = 0;
  vector<Matrix>c(LOG); 
  c[0] = base; 
  for(int i = 1; i < LOG; i++) { 
    c[i] = c[i - 1] * c[i - 1]; 
  }
  for(cin >> T; T--; ) {
   cin >> N; 
   int64_t ret = 0; 
   vector<int64_t>a(N); 
   for(int i = 0; i < N; i++) { 
    cin >> a[i]; 
   }
   sort(a.begin(), a.end());
   int st = -1; 
   for(int i = 0; i < N; i++) { 
    if(a[i] < 5) { 
     (ret += coef[5 - a[i]]) %= MOD; 
    } else { 
      st = i; 
      break; 
    }
   } 
   auto vec = coef; 
   for(int i = st; 0 <= i && i < N; i++) {  
    int64_t dist = (i == st ?  a[i] - 4 : a[i] - a[i - 1]); 
    for(int j = 0; (1LL << j) <= dist; j++) { 
     if(dist & (1LL << j)) { 
      vec = c[j] * vec; 
     } 
    }
    (ret += vec[1]) %= MOD;  
   }
   cout << ret << '\n'; 
  }
  return 0; 
}
/**
 * 2 ^ 0 = 1
  
 * 
 */