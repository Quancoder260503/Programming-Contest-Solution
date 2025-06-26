#include "bits/stdc++.h"

using namespace std;

const int oo = 1e9;

struct Tree {
  typedef int T;
  static constexpr T unit = int(1e9);
  T f(T a, T b) { return min(a, b); }  // (any associative fn)
  vector<T> s;
  int n;
  Tree(int n = 0, T def = unit) : s(2 * n, def), n(n) {}
  void update(int pos, T val) {
    pos += n;
    s[pos] = min(val, s[pos]);
    for (; pos /= 2;) s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
  }
  T query(int b, int e) {  // query [b, e)
    T ra = unit, rb = unit;
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if (b % 2) ra = f(ra, s[b++]);
      if (e % 2) rb = f(s[--e], rb);
    }
    return f(ra, rb);
  }
};

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int N, K;
  cin >> N >> K;
  vector<vector<char>> g(N, vector<char>(N));
  vector<vector<int>> dyn(N, vector<int>(N, oo));
  vector<Tree> rows, cols;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> g[i][j];
    }
  }
  for (int i = 0; i < N; i++) {
    rows.emplace_back(N);
    cols.emplace_back(N);
  }
  dyn[0][0] = 0; 
  cols[0].update(0, 0); 
  rows[0].update(0, 0); 
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (g[i][j] == '#' || (i == 0 && j == 0)) continue;
      dyn[i][j] = min(dyn[i][j], 1 + min(cols[j].query(max(0, i - K), i),
                                         rows[i].query(max(0, j - K), j)));
      rows[i].update(j, dyn[i][j]); 
      cols[j].update(i, dyn[i][j]); 
    }
  }
  cout << (dyn[N - 1][N - 1] == oo ? -1 : dyn[N - 1][N - 1]) << '\n';
  return 0;
}