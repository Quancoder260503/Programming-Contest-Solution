#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())
#define int64_t long long

int64_t N, M;
string S; 
int Q;  

using type = __int128_t;

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
  Matrix operator*(const Matrix &b) {
    Matrix a = *this;
    assert(a.col() == b.row());
    Matrix c(a.row(), b.col());
    for (int i = 0; i < a.row(); ++i) {
      for (int j = 0; j < b.col(); ++j) {
        for (int k = 0; k < a.col(); ++k) {
          c[i][j] += a[i][k] % M * b[k][j] % M;
          c[i][j] %= M;
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

int isSuffix(string a, string b) {
  if (sz(a) < sz(b)) return false;
  for (int i = sz(a) - 1, j = sz(b) - 1; j >= 0; i--, j--) {
    if (a[i] != b[j]) {
      return false;
    }
  }
  return true;
}

__int128_t fpow(int64_t a, int64_t k, int64_t mod) {
  if (!k) return 1;
  __int128_t res = a, tmp = a;
  k--;
  while (k) {
    if (k & 1) {
      res = __int128_t(res % mod * tmp % mod);
    }
    tmp = __int128_t(tmp % mod * tmp % mod);
    k >>= 1;
  }
  return res;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> Q;
  for (int iter = 0; iter < Q; iter++) {
    cin >> N >> M >> S;
    vector<string> substring;
    for (int i = 0; i < sz(S); i++) {
      substring.push_back(S.substr(0, i));
    }
    Matrix _Mat(sz(S), sz(S));
    for (int i = 0; i < sz(substring); i++) {
      for (int c = 0; c < 26; c++) {
        string next = substring[i] + (char)('a' + c);
        if (next == S) continue;
        int pos = 0;
        string nextPattern;
        for (int j = 0; j < sz(substring); j++) {
          if (isSuffix(next, substring[j]) &&
              sz(nextPattern) < sz(substring[j])) {
            pos = j;
            nextPattern = substring[j];
          }
        }
        _Mat[i][pos]++;
      }
    }
    _Mat = _Mat.pow(N - 1);
    __int128_t ret = fpow(26, N, M);
    for (int j = 0; j < sz(S); j++) {
      ret = (ret + M - _Mat[0][j]) % M;
    }
    cout << (int64_t)ret << '\n';
  }
  return 0;
}
