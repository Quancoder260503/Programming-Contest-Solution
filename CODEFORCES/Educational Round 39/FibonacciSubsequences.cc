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
  Matrix operator*(const Matrix &b) {
    Matrix a = *this;
    assert(a.col() == b.row());

    Matrix c(a.row(), b.col());
    for (int i = 0; i < a.row(); ++i) {
      for (int j = 0; j < b.col(); ++j) {
        for (int k = 0; k < a.col(); ++k) {
          (c[i][j] += a[i][k] % mod * b[k][j] % mod) %= mod;
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
};

vector<int> prefix_function(const string &s) {
  int n = sz(s);
  vector<int> pi(n + 1);
  for (int i = 2; i <= n; ++i) {
    int j = pi[i - 1];
    while (j > 0 && s[i - 1] != s[j]) j = pi[j];
    if (s[i - 1] == s[j]) ++j;
    pi[i] = j;
  }
  return pi;
}

int get_next(vector<int> &pi, string &s, int pos, char c) {
  if (pos == sz(s)) pos = pi[pos];
  while (pos > 0 && c != s[pos]) pos = pi[pos];
  if (s[pos] == c) pos++;
  return pos;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int N, X;
  string S;
  cin >> X >> N >> S;
  vector<int> kmp = prefix_function(S);
  vector<Matrix> fiboMatrix;
  for (char c = '0'; c <= '1'; c++) {
    Matrix mat(sz(kmp) + 1, sz(kmp) + 1);
    for (int beginState = 0; beginState < sz(kmp); beginState++) {
      int nextState = get_next(kmp, S, beginState, c); 
      mat[beginState][beginState]++; 
      mat[beginState][nextState]++;
      if(nextState == sz(S)) mat[beginState][sz(kmp)]++;  
    }
    mat[sz(kmp)][sz(kmp)] = 2;
    fiboMatrix.push_back(mat);
  }
  for (int i = 2; i <= N; i++) {
    fiboMatrix.push_back(fiboMatrix.back() * fiboMatrix[sz(fiboMatrix) - 2]);
  } 
  cout << fiboMatrix[N][0].back() << '\n'; 
  return 0;
}
