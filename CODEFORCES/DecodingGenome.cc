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
 int64_t N; 
 int M, K; 
 cin >> N >> M >> K; 
 Matrix base(M, M); 
 for(int i = 0; i < M; i++) {
  for(int j = 0; j < M; j++) { 
   base[i][j] = 1; 
  }
 }
 vector<char>a(K), b(K); 
 vector<char>coord; 
 for(int i = 0; i < K; i++) { 
  cin >> a[i] >> b[i]; 
  coord.push_back(a[i]); 
  coord.push_back(b[i]); 
 }
 sort(coord.begin(), coord.end()); 
 coord.erase(unique(coord.begin(), coord.end()), coord.end()); 
 for(int i = 0; i < K; i++) {  
  int c0 = lower_bound(coord.begin(), coord.end(), a[i]) - coord.begin(); 
  int c1 = lower_bound(coord.begin(), coord.end(), b[i]) - coord.begin(); 
  base[c0][c1] = 0;  
 }
 auto ret = base.pow(N - 1); 
 int64_t ans = 0; 
 for(int i = 0; i < M; i++) { 
  for(int j = 0; j < M; j++) { 
   (ans += ret[i][j]) %= MOD; 
  }
 }
 cout << ans << '\n'; 
 return 0; 
}