#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int64_t oo = 1e18; 
const int MOD = 1e9 + 7;
const int BOUND = 10; 

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

template <typename T>
struct Matrix {
  int n_row, n_col;
  vector<T> x;

  // accessors
  typename vector<T>::iterator operator[](int r) {
    return x.begin() + r * n_col;
  }
  inline T get(int i, int j) const { return x[i * n_col + j]; }
  vector<T> at(int r) const {
    return vector<T>{x.begin() + r * n_col, x.begin() + (r + 1) * n_col};
  }

  // constructors
  Matrix() = default;
  Matrix(int _n_row, int _n_col)
      : n_row(_n_row), n_col(_n_col), x(n_row * n_col) {}
  Matrix(const vector<vector<T>>& d)
      : n_row(d.size()), n_col(d.size() ? d[0].size() : 0) {
    for (auto& row : d)
      std::copy(row.begin(), row.end(), std::back_inserter(x));
  }

  // convert to 2d vec
  vector<vector<T>> vecvec() const {
    vector<vector<T>> ret(n_row);
    for (int i = 0; i < n_row; i++) {
      std::copy(x.begin() + i * n_col, x.begin() + (i + 1) * n_col,
                std::back_inserter(ret[i]));
    }
    return ret;
  }
  operator vector<vector<T>>() const { return vecvec(); }

  static Matrix identity(int n) {
    Matrix res(n, n);
    for (int i = 0; i < n; i++) {
      res[i][i] = 1;
    }
    return res;
  }

  Matrix transpose() const {
    Matrix res(n_col, n_row);
    for (int i = 0; i < n_row; i++) {
      for (int j = 0; j < n_col; j++) {
        res[j][i] = this->get(i, j);
      }
    }
    return res;
  }

  Matrix& operator*=(const Matrix& r) { return *this = *this * r; }
  Matrix operator*(const Matrix& r) const {
    assert(n_col == r.n_row);
    Matrix res(n_row, r.n_col);

    for (int i = 0; i < n_row; i++) {
      for (int k = 0; k < n_col; k++) {
        for (int j = 0; j < r.n_col; j++) {
         (res[i][j] += this->get(i, k) % MOD * r.get(k, j) % MOD) %= MOD;
        }
      }
    }
    return res;
  } 
  vector<int64_t> operator*(const vector<int64_t>&vec) const {
    Matrix a = *this;
    vector<int64_t>ret(sz(vec)); 
    for (int i = 0; i < n_row; ++i) {
     for (int j = 0; j < n_col; ++j) {
      (ret[i] += 1LL * a[i][j] % MOD * vec[j] % MOD) %= MOD; 
     }
    }
    return ret;
  }
  Matrix pow(long long n) const {
    assert(n_row == n_col);
    Matrix res = identity(n_row);
    if (n == 0) return res;

    bool res_is_id = true;
    for (int i = 63 - __builtin_clzll(n); i >= 0; i--) {
      if (!res_is_id) res *= res;
      if ((n >> i) & 1) res *= (*this), res_is_id = false;
    }
    return res;
  }

  // Gauss
  template <typename T2,
            typename std::enable_if<std::is_floating_point<T2>::value>::type* =
                nullptr>
  static int choose_pivot(const Matrix<T2>& mtr, int h, int c) noexcept {
    int piv = -1;
    for (int j = h; j < mtr.n_row; j++) {
      if (mtr.get(j, c) and
          (piv < 0 or std::abs(mtr.get(j, c)) > std::abs(mtr.get(piv, c))))
        piv = j;
    }
    return piv;
  }
  template <typename T2,
            typename std::enable_if<!std::is_floating_point<T2>::value>::type* =
                nullptr>
  static int choose_pivot(const Matrix<T2>& mtr, int h, int c) noexcept {
    for (int j = h; j < mtr.n_row; j++) {
      if (mtr.get(j, c) != T(0)) return j;
    }
    return -1;
  }

  // For upper triangle matrix
  T det() const {
    T ret = 1;
    for (int i = 0; i < n_row; i++) {
      ret *= get(i, i);
    }
    return ret;
  }

  // return rank of inverse matrix. If rank < n -> not invertible
  int inverse() {
    assert(n_row == n_col);
    vector<vector<T>> ret = identity(n_row), tmp = *this;
    int rank = 0;

    for (int i = 0; i < n_row; i++) {
      int ti = i;
      while (ti < n_row && tmp[ti][i] == 0) ++ti;
      if (ti == n_row)
        continue;
      else
        ++rank;

      ret[i].swap(ret[ti]);
      tmp[i].swap(tmp[ti]);

      T inv = mod_inv(tmp[i][i], MOD);
      for (int j = 0; j < n_col; j++) (ret[i][j] *= inv) %= MOD;
      for (int j = i + 1; j < n_col; j++) (tmp[i][j] *= inv) %= MOD;

      for (int h = 0; h < n_row; h++) {
        if (i == h) continue;
        const T c = (MOD - tmp[h][i]);
        for (int j = 0; j < n_col; j++) (ret[h][j] += ret[i][j] % MOD * c % MOD) %= MOD;
        for (int j = i + 1; j < n_col; j++) (tmp[h][j] += tmp[i][j] % MOD * c % MOD) %= MOD;
      }
    }

    *this = ret;
    return rank;
  }

  // sum of all elements in this matrix
  T sum_all() { return submatrix_sum(0, 0, n_row, n_col); }

  // sum of [r1, r2) x [c1, c2)
  T submatrix_sum(int r1, int c1, int r2, int c2) {
    T res{0};
    for (int r = r1; r < r2; ++r) {
      res += std::accumulate(x.begin() + r * n_col + c1,
                             x.begin() + r * n_col + c2, T{0});
    }
    return res;
  }
};
template <typename T>
ostream& operator<<(ostream& cout, const Matrix<T>& m) {
  cout << m.n_row << ' ' << m.n_col << '\n';
  for (int i = 0; i < m.n_row; ++i) {
    cout << "row [" << i << "] = " << m.at(i) << '\n';
  }
  return cout;
}
// }}}

using matrix = Matrix<int64_t>; 

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 vector<matrix>cc(BOUND); 
 Matrix base = matrix :: identity(BOUND); 
 for(int i = 0; i < BOUND - 1; i++) { 
  cc[i] = base; 
  for(int j = 0; j < BOUND; j++) { 
    cc[i][i + 1][j] = 1; 
  }
 }
 string S; 
 cin >> S; 
 int N = sz(S); 
 vector<matrix>prefix(N), iprefix(N);
 for(int i = 0; i < N; i++) { 
  prefix[i] = (i ? prefix[i - 1] : base) * cc[S[i] - 'a']; 
  iprefix[i] = prefix[i]; 
  iprefix[i].inverse(); 
 } 
 int L, R, Q; 
 for(cin >> Q; Q--; ) { 
  cin >> L >> R; 
  --L, --R; 
  vector<int64_t>dp(BOUND); 
  dp[0] = 1; 
  auto pre = (L ? iprefix[L - 1] : base); 
  auto mat = pre * (prefix[R] * dp);
  int64_t ret = 0; 
  for(int j = 1; j < BOUND; j++) { 
   (ret += mat[j]) %= MOD; 
  }
  cout << ret << '\n'; 
 }
 return 0; 
}