#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int MOD = 1e9 + 7; 

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
          (c[i][j] += a[i][k] % MOD * b[k][j] % MOD) %= MOD;
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


int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);  
  int N, K;
  string S; 
  cin >> N >> K >> S; 
  auto getBit = [&](int mask, int bit) { 
   return mask >> bit & 1; 
  }; 
  auto calc = [&](int v) { 
   Matrix ret(1 << N, 1 << N); 
   for(int mask = 0; mask < (1 << N); mask++) {
    for(int disMask = 0; disMask < (1 << (N - 1)); disMask++) { 
     int flag = true; 
     int next_mask = mask; 
     int bits = (v << N) | (disMask << 1) | (__builtin_popcount(disMask) & 1); 
     for(int i = 0; i < N; i++) { 
      if(!getBit(mask, i) && getBit(bits, i) && !getBit(bits, i + 1)) { 
        flag = false; 
        break; 
      }
      if(!getBit(bits, i) && getBit(bits, i + 1)) { 
        next_mask |= (1 << i); 
      }
     }
     if(!flag) continue; 
    // cout << next_mask << '\n'; 
     ret[mask][next_mask]++; 
    }
   } 
   return ret; 
  };
  Matrix matrixZero = calc(0); 
  cout << matrixZero; 
  /* 
  Matrix matrixOne  = calc(1);  
  Matrix ret(1 << N, 1 << N); 
  for(int i = 0; i < (1 << N); i++) { 
    ret[i][i] = 1; 
  }
  for(int i = 0; i < sz(S); i++) { 
    ret = ret * (S[i] == '0' ? matrixZero : matrixOne); 
  } 
  ret = ret.pow(K - 1); 
  cout << ret[0][(1 << N) - 1];
  */ 
  return 0; 
}

/**
 * dp[i][mask][mask2]
 * 
 */