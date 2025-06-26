#include "bits/stdc++.h"
 
using namespace std; 
 
#define sz(x) int(x.size())
 
using type = int64_t; 
 
const int mod = 1e9 + 7; 
 
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
    for(int i = 0; i < sz(data); i++) { 
      type sum = 0.0; 
      for(int j = 0; j < sz(data[i]); j++) { 
        sum += data[i][j]; 
      }
      for(int j = 0; j < sz(data[i]); j++) { 
        data[i][j] /= sum; 
      }
    }
    return; 
  }
};
 
int isSuffix(string a, string b) { 
  if(sz(a) < sz(b)) return false; 
  for(int i = sz(a) - 1, j = sz(b) - 1; j >= 0; i--, j--) { 
    if(a[i] != b[j]) {
      return false; 
    }
  }
  return true; 
}
 
int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N; 
  string S; 
  cin >> N >> S; 
  vector<string>substring;  
  for(int i = 0; i < sz(S); i++) { 
    substring.push_back(S.substr(0, i)); 
  }
  Matrix _Mat(sz(S), sz(S)); 
  for(int i = 0; i < sz(substring); i++) { 
    for(int c = 0; c < 26; c++) { 
      string next = substring[i] + (char)('A' + c); 
      if(next == S) continue; 
      int pos = 0; 
      string nextPattern; 
      for(int j = 0; j < sz(substring); j++) { 
        if(isSuffix(next, substring[j]) && sz(nextPattern) < sz(substring[j])) { 
          pos = j; 
          nextPattern = substring[j]; 
        } 
      }
      _Mat[i][pos]++; 
    }
  }
  _Mat = _Mat.pow(N - 1);  
  int64_t ret = 1; 
  for(int i = 0; i < N; i++) { 
    ret = ret * 26 % mod; 
  }
  for(int j = 0; j < sz(S); j++) { 
    ret = (ret + mod - _Mat[0][j]) % mod;
  }
  cout << ret << '\n'; 
  return 0; 
}