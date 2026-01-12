#include "bits/stdc++.h"

using namespace std;

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#define sz(x) int(x.size())
#define int64_t long long

using type = int64_t; 

const int64_t MOD = (1LL << 32);  
const int LOG = 20; 

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
          (c[i][j] += (int64_t)((__int128_t) a[i][k] % MOD * b[k][j] % MOD)) %= MOD;
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

vector<pair<string, array<int64_t, 3>>>ins; 
vector<int64_t>val; 
vector<int>match; 
int n, k;

Matrix rec(int i, int j) { 
 int start;
 Matrix idn(k + 1, k + 1); 
 for(int c = 0; c <= k; c++) { 
  idn[c][c] = 1; 
 } 
 Matrix ret = idn; 
 for(start = i; start < j && ins[start].first != "for"; start++) { 
  Matrix curr = idn;   
 // cout << ins[start].first << '\n'; 
  if(ins[start].first == "add") {  
   curr[ins[start].second[0]][ins[start].second[0]] = 0; 
   curr[ins[start].second[0]][ins[start].second[1]] += 1; 
   curr[ins[start].second[0]][ins[start].second[2]] += 1; 
  } else if(ins[start].first == "addi") { 
    curr[ins[start].second[0]][ins[start].second[0]] = 0; 
    curr[ins[start].second[0]][ins[start].second[1]] = 1; 
    curr[ins[start].second[0]][k] = ins[start].second[2]; 
    //cout << curr; 
  } else if(ins[start].first == "move") { 
    curr[ins[start].second[0]][ins[start].second[0]] = 0; 
    curr[ins[start].second[0]][ins[start].second[1]] = 1; 
  } else {
    curr[ins[start].second[0]][ins[start].second[0]] = 0;   
    curr[ins[start].second[0]][k] = ins[start].second[1]; 
  }
  ret = curr * ret;  
  //cout << '\n'; 
 }  
 if(start == j) return ret; 
 if(start + 1 < match[start]) { 
  Matrix curr = rec(start + 1, match[start]); 
 // cout << curr; 
 // cout << start << " " << match[start] << '\n'; 
  curr = curr.pow(ins[start].second[0]); 
  ret = curr * ret; 
 }
 return rec(match[start] + 1, j) * ret; 
}

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 cin >> n >> k; 
 ins.resize(n); 
 val.resize(k); 
 for(auto &x : val) { 
  cin >> x; 
 }
 for(int i = 0; i < n; i++) { 
  cin >> ins[i].first; 
  for(int j = 0; j < 3; j++) { 
   ins[i].second[j] = -1; 
  }
  string curr;  
  if(ins[i].first == "addi" || ins[i].first == "add") { 
   for(int j = 0; j < 3; j++) { 
    cin >> curr; 
    ins[i].second[j] = (curr[0] == 'r' ? stoll(curr.substr(1, sz(curr) - 1)) : stoll(curr)); 
   }
  } else if (ins[i].first == "move" || ins[i].first == "li") {
   for(int j = 0; j < 2; j++) { 
    cin >> curr; 
    ins[i].second[j] = (curr[0] == 'r' ? stoll(curr.substr(1, sz(curr) - 1)) : stoll(curr)); 
   /// cout << ins[i].second[j] << " "; 
   } 
  } else if(ins[i].first == "for") { 
    for(int j = 0; j < 1; j++) { 
     cin >> curr; 
     ins[i].second[j] = (curr[0] == 'r' ? stoll(curr.substr(1, sz(curr) - 1)) : stoll(curr)); 
    } 
  }
 }
 stack<int>stk; 
 match.assign(n, -1); 
 for(int i = 0; i < n; i++) { 
  if(ins[i].first == "for") { 
   stk.push(i);  
  } else if(ins[i].first == "rof") { 
   match[stk.top()] = i;
   stk.pop();  
  }
 }
 auto ret = rec(0, n); 
 Matrix coef(k + 1, k + 1); 
 for(int i = 0; i < k; i++) { 
  coef[i][0] = val[i]; 
 }
 coef[k][0] = 1; 
 ret = ret * coef; 
 for(int i = 0; i < k; i++) { 
  cout << ret[i][0] << " "; 
 }
 cout << '\n'; 
 return 0; 
}
