#include "bits/stdc++.h"
 
using namespace std; 
 
#define int64_t long long
#define sz(x) int(x.size())
 
using type = int64_t; 
const int64_t oo = 1e15; 
 
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
  static Matrix infinity(long long n) {
    Matrix a = Matrix(n, n);
    for (int i = 0; i < a.row(); i++) {
      for (int j = 0; j < a.col(); j++) {
        a[i][j] = -oo;
      }
    }
    return a;
  }
  Matrix operator*(const Matrix &b) {
    Matrix a = *this;
    assert(a.col() == b.row());
    Matrix c = infinity(a.col()); 
    for (int i = 0; i < a.row(); ++i) {
      for (int j = 0; j < b.col(); ++j) {
        for (int k = 0; k < a.col(); ++k) {
          c[i][j] = max(c[i][j], a[i][k] + b[k][j]);
        }
      }
    }
    return c;
  }
  Matrix pow(long long exp) {
    assert(row() == col());
    Matrix base = *this, ans = infinity(row()); 
    ans[0][0] = 0; 
    for (; exp > 0; exp >>= 1, base = base * base)
      if (exp & 1) ans = ans * base;
    return ans;
  }
};
 
struct AhoCorasick {
  enum { alpha = 26, first = 'a' };  // change this!
  struct Node {
    // (nmatches is optional)
    int back, next[alpha], done = 0, start = -1, end = -1, nmatches = 0;
    Node(int v) { memset(next, v, sizeof(next)); }
  };
  vector<Node> N;
  vector<int> backp;
  void insert(string &s, int j, int cc) {
    assert(!s.empty());
    int n = 0;
    for (char c : s) {
      int &m = N[n].next[c - first];
      if (m == -1) {
        n = m = sz(N);
        N.emplace_back(-1);
      } else
        n = m;
    }
    if (N[n].end == -1) N[n].start = j;
    backp.push_back(N[n].end);
    N[n].end = j;
    N[n].nmatches++;
    N[n].done += cc; 
    return; 
  }
  AhoCorasick(vector<string> &pat, vector<int> &cc) : N(1, -1) {
    for (int i = 0; i < sz(pat); i++) {      
       insert(pat[i], i, cc[i]);
    }
    N[0].back = sz(N);
    N.emplace_back(0);
    queue<int> q;
    for (q.push(0); !q.empty(); q.pop()) {
      int n = q.front(), prev = N[n].back;
      for (int i = 0; i < alpha; i++) {
        int &ed = N[n].next[i], y = N[prev].next[i];
        if (ed == -1)
          ed = y;
        else {
          N[ed].back = y;
          (N[ed].end == -1 ? N[ed].end : backp[N[ed].start]) = N[y].end;
          N[ed].done += N[y].done;
          q.push(ed);
        }
      }
    }
  }
};
 
int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int M, N;
  int64_t K;  
  cin >> N >> K; 
  vector<int>a(N); 
  for(int i = 0; i < N; i++) { 
    cin >> a[i]; 
  }
  vector<string>s(N); 
  for(int i = 0; i < N; i++) { 
    cin >> s[i]; 
  }
  AhoCorasick aho(s, a); 
  M = sz(aho.N); 
  Matrix _Mat(M, M);
  for(int i = 0; i < M; i++) { 
    for(int j = 0; j < M; j++) { 
      _Mat[i][j] = -1; 
    }
  }
  for(int i = 0; i < M; i++) { 
    for(int j = 0; j < 26; j++) { 
      int next_node = aho.N[i].next[j];  
      if(_Mat[i][next_node] == -1) _Mat[i][next_node] = 0; 
      _Mat[i][next_node] += aho.N[next_node].done;    
    }
  }
  for(int i = 0; i < M; i++) { 
    for(int j = 0; j < M; j++) { 
      if(_Mat[i][j] == -1) _Mat[i][j] = -oo; 
    }
  }
  _Mat = _Mat.pow(K); 
  int64_t ret = -oo; 
  for(int i = 0; i < M; i++) { 
    ret = max(ret, _Mat[0][i]); 
  }
  cout << ret << '\n'; 
  return 0; 
}