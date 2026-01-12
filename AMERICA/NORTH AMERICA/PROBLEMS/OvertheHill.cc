#include "bits/stdc++.h"

using namespace std;

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#define sz(x) int(x.size())
#define int64_t long long

using type = int64_t; 

const int MOD = 37; 

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
          (c[i][j] += (int64_t)(a[i][k] % MOD * b[k][j] % MOD)) %= MOD;
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

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int n; 
 cin >> n; 
 Matrix a(n, n); 
 for(int i = 0; i < n; i++) { 
  for(int j = 0; j < n; j++) { 
   cin >> a[i][j]; 
  }
 }
 string s; 
 cin.ignore(); 
 getline(cin, s); 
 vector<int>encode; 
 for(int i = 0; i < sz(s); i++) { 
  if(s[i] == ' ') encode.push_back(36); 
  if('A' <= s[i] && s[i] <= 'Z') encode.push_back(s[i] - 'A'); 
  if('0' <= s[i] && s[i] <= '9') encode.push_back(s[i] - '0' + 26); 
 }
 while(sz(encode) % n) { 
  encode.push_back(36);   
 }
 string ret = ""; 
 for(int i = 0; i < sz(encode); i += n) { 
  Matrix b(n, n); 
  for(int j = i; j < i + n; j++) { 
   b[j - i][0] = encode[j];  
  }
  b = a * b; 
  for(int j = 0; j < n; j++) {
   if(b[j][0] == 36) ret += ' '; 
   else if(b[j][0] < 26) ret += char('A' + b[j][0]); 
   else ret +=  char(b[j][0] - 26 + '0'); 
  }
 }
 cout << ret << '\n'; 
 return 0; 
}