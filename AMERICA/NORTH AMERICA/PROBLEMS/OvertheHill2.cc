#include "bits/stdc++.h"

using namespace std;

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#define sz(x) int(x.size())
#define int64_t long long

using type = int64_t;

const int MOD = 37;

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

int rref(vector<vector<int64_t>> &matrix) {
  int n = matrix.size(), m = matrix[0].size();
  vector<int> match(m, -1);
  int rank = 0;
  for (int c = 0; c < m && rank < n; c++) {
    int pivot = rank;
    for (int i = rank + 1; i < n; i++)
      if (matrix[i][c] > matrix[pivot][c]) pivot = i;

    if (!matrix[pivot][c]) continue;
    swap(matrix[pivot], matrix[rank]);
    match[c] = rank;

    auto temp = mod_inv(matrix[rank][c], MOD);
    for (int j = 0; j < m; j++) matrix[rank][j] = matrix[rank][j] * temp % MOD;

    for (int i = 0; i < n; i++)
      if (i != rank && matrix[i][c]) {
        temp = matrix[i][c];
        for (int j = 0; j < m; j++)
          (matrix[i][j] += (MOD - temp * matrix[rank][j] % MOD)) %= MOD;
      }

    rank++;
  }
  return rank;
}

template<class T>
ostream &operator << (ostream &out, const vector<vector<T>>&d) { 
 for(int i = 0; i < sz(d); i++) { 
  for(int j = 0; j < sz(d[i]); j++) { 
   out << d[i][j] << ' '; 
  }
  out << '\n'; 
 }
 return out; 
}

ostream &operator << (ostream &out, const vector<int>&d) { 
 for(int i = 0; i < sz(d); i++) { 
  out << d[i] << ' '; 
 } 
 out << '\n'; 
 return out; 
}


int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n;
  string a, b;
  cin >> n;
  cin.ignore();
  getline(cin, a);
  getline(cin, b);
  while (sz(a) < sz(b)) a.push_back(' ');
  while (sz(b) < sz(a)) b.push_back(' ');
  while (sz(a) % n) {
    a.push_back(' ');
    b.push_back(' ');
  }
  // cout << a << " " << b << '\n';
  auto get_num = [&](char c) {
    int cc = 0;
    if (c == ' ')
      cc = 36;
    else if ('A' <= c && c <= 'Z')
      cc = c - 'A';
    else
      cc = c - '0' + 26;
    return cc;
  }; 
  vector<int> encode_a, encode_b;
  for (int i = 0; i < sz(a); i++) {
    encode_a.push_back(get_num(a[i]));
    encode_b.push_back(get_num(b[i]));
  }
  vector<vector<int>>ret(n, vector<int>(n)); 
  int m = sz(a) / n;
  int cc = n; 
  for (int st = 0; st < n; st++) {
    vector<vector<int64_t>>mat(m, vector<int64_t>(n + 1)); 
    for (int i = 0; i < sz(a); i += n) {
      for (int j = i, cc = 0; j < i + n; j++) {
        mat[i / n][j - i] = get_num(a[j]);
      }
      mat[i / n][n] = get_num(b[st + i]);
    } 
    int rank = rref(mat);
    //cout << rank << " " << n << " " << m << '\n'; 
    if(rank > n) { 
      cout << "No solution\n"; 
      exit(0); 
    }
    for(int i = 0; i < sz(mat); i++) { 
     int c = true; 
     for(int j = 0; j < sz(mat[i]) - 1; j++) { 
      c &= (mat[i][j] == 0); 
     }
    // cout << mat; 
   // cout << c << " " << mat[i][n] << '\n'; 
     if(c && mat[i][n] > 0) { 
      cout << "No solution\n"; 
      exit(0); 
     }
    }
    cc = min(cc, rank); 
    for(int i = 0; i < min(n, m); i++) { 
     ret[st][i] = mat[i][n];  
    }
  }
  if(cc < n) { 
   cout << "Too many solutions\n"; 
   exit(0); 
  }
  cout << ret; 
  return 0;
}