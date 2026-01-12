#include "bits/stdc++.h"

using namespace std;

int64_t A, B, C; 
int n; 

const int N = 2500;
__int128_t c[N][N]; 

template <typename T>
pair<T, vector<int>> Hungarian(int n, int m, T c[][N]) {
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
  for (int i = 0; i < n; ++i) { 
  // if(L[i] == 0) continue;
   ret += c[i][L[i]];
  }  
  return {ret, L};
}


int64_t minCost(int64_t x, int64_t y) { 
 if(x == y) return 0; 
 int64_t ret = LLONG_MAX; 
 if(x > 0) { 
  ret = min(ret, minCost(0LL, y) + C); 
 } 
 if(x > y) return ret; 
 if(y / 2 >= x) { 
  ret = min(ret, minCost(x, y / 2) + (y % 2 == 1 ? A : 0) + (y > 1 ? B : 0)); 
 } 
 if(LLONG_MAX >= (__int128_t) (y - x) * A) {
  ret = min(ret, (y - x) * A); 
 } 
 return ret;  
};

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  cin >> n >> A >> B >> C;
  vector<int64_t>val(n + 1); 
  for(int i = 1; i <= n; i++) { 
   cin >> val[i]; 
  }
  for(int i = 0; i <= n; i++) { 
   for(int j = 0; j <= n; j++) { 
    c[i][j] = (i == j ? LLONG_MAX : minCost(val[i], val[j])); 
   } 
  }
  auto ret = Hungarian<__int128_t>(n + 1, n + 1, c); 
  cout << int64_t(ret.first) - C << '\n'; 
  return 0;
}
