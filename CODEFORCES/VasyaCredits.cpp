#include "bits/stdc++.h"
 
using namespace std;
 
const int64_t oo = 1e16;
const int maxf = 1002;
 
template <typename T>
pair<T, vector<int>> Hungarian(int n, int m, T c[][maxf]) {
  vector<T> v(m), dist(m);
  vector<int> L(n, -1), R(m, -1);
  vector<int> index(m), prev(m);
  auto getc = [&](int i, int j) { return c[i][j] - v[j]; };
  iota(index.begin(), index.end(), 0);
  for (int f = 0; f < n; ++f) {
    for (int j = 0; j < m; ++j) {
      dist[j] = getc(f, j), prev[j] = f;
    }
    T w = 0;
    int j, l = 0, s = 0, t = 0;
    while (true) {
      if (s == t) {
        l = s, w = dist[index[t++]];
        for (int k = t; k < m; ++k) {
          j = index[k];
          T h = dist[j];
          if (h <= w) {
            if (h < w) t = s, w = h;
            index[k] = index[t], index[t++] = j;
          }
        }
        for (int k = s; k < t; ++k) {
          j = index[k];
          if (R[j] < 0) goto augment;
        }
      }
      int q = index[s++], i = R[q];
      for (int k = t; k < m; ++k) {
        j = index[k];
        T h = getc(i, j) - getc(i, q) + w;
        if (h < dist[j]) {
          dist[j] = h, prev[j] = i;
          if (h == w) {
            if (R[j] < 0) goto augment;
            index[k] = index[t], index[t++] = j;
          }
        }
      }
    }
  augment:
    for (int k = 0; k < l; ++k) v[index[k]] += dist[index[k]] - w;
    int i;
    do {
      i = R[j] = prev[j];
      swap(j, L[i]);
    } while (i != f);
  }
  T ret = 0;
  for (int i = 0; i < n; ++i) ret += c[i][L[i]];
  return {ret, L};
}
 
int64_t cost[maxf][maxf];
 
int main(void) {
  int N;
  cin >> N;
  vector<array<int, 3>> c(N);
  for (int i = 0; i < N; i++) {
    cin >> c[i][0] >> c[i][1] >> c[i][2];
  }
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cost[i][j] = -max(0LL, c[i][0] - 1LL * min(j, c[i][2]) * c[i][1]);
    }
  }
  cout << -Hungarian<int64_t>(N, N, cost).first << '\n';
  return 0;
}
/**
 * 
 * Suppose that at month kth we take k credits, then the objectives is to find 
 * the optimal order so that we take the lowest lease or find the optimal matching 
 * between the left side (credit) and right side (taken month)
 */