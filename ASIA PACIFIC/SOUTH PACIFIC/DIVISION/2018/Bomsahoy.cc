#include "bits/stdc++.h"

using namespace std;

#define sz(x) (int) x.size()


const int dx[8] = {-1, 1, 0, 0, 1, -1, -1, 1};
const int dy[8] = {0, 0, 1, -1, 1, -1, 1, -1}; 

struct Fenwick2D {
  using T = vector<vector<int64_t>>; 
  vector<T>A, M; 
  int N, C;
  Fenwick2D(int n, int m) {
    N = n + 10, C = m + 10;
    A = vector<T>(N, T(C, vector<int64_t>(2, 0))); 
    M = vector<T>(N, T(C, vector<int64_t>(2, 0))); 
    return; 
  }
  void upd2(vector<T>& t, int x, int y, int64_t mul, int64_t add) {
    for(int i = x; i < N; i += i & -i) {
      for(int j = y; j < C; j += j & -j) {
        t[i][j][0] += mul;
        t[i][j][1] += add;
      }
    }
  }
  void upd1(int x, int y1, int y2, int64_t mul, int64_t add) {
    upd2(M, x, y1, mul, -mul * (y1 - 1));
    upd2(M, x, y2, -mul, mul * y2);
    upd2(A, x, y1, add, -add * (y1 - 1));
    upd2(A, x, y2, -add, add * y2);
  }
  void upd(int x1, int y1, int x2, int y2, int64_t val) {
    upd1(x1, y1, y2, val, -val * (x1 - 1));
    upd1(x2, y1, y2, -val, val * x2);
  }
  int64_t query2(vector<T>& t, int x, int y) {
    int64_t mul = 0, add = 0;
    for(int i = y; i > 0; i -= i & -i) {
      mul += t[x][i][0];
      add += t[x][i][1];
    }
    return mul * y + add;
  }
  int64_t query1(int x, int y) {
    int64_t mul = 0, add = 0;
    for(int i = x; i > 0; i -= i & -i) {
      mul += query2(M, i, y);
      add += query2(A, i, y);
    }
    return mul * x + add;
  }
  int64_t query(int x1, int y1, int x2, int y2) {
    return query1(x2, y2) - query1(x1 - 1, y2) - query1(x2, y1 - 1) + query1(x1 - 1, y1 - 1);
  }
}; 

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m, q; 
    cin >> n >> m >> q;
    Fenwick2D fenw(n, m); 
    vector<vector<char>>g(n + 1, vector<char>(m + 1)); 
    vector<vector<int>>vis(n + 1, vector<int>(m + 1, false)); 
    pair<int, int>st; 
    for(int i = 1; i <= n; i++) 
    for(int j = 1; j <= m; j++) { 
        cin >> g[i][j]; 
        if(g[i][j] == 'X') { 
          fenw.upd(i, j, i, j, true); 
        }
        if(g[i][j] == 'S') { 
          st = {i, j};
          vis[i][j] = true; 
        }  
    }
    queue<pair<int, int>>dq, nq;
    dq.push(st);  
    for(int iter = 0, r1, c1, r2, c2; iter < q; iter++) { 
      while(sz(dq)) {
        auto [x, y] = dq.front();
        dq.pop();  
        if(fenw.query(x, y, x, y)) continue; 
        for(int k = 0; k < 8; k++) { 
          int kx = dx[k] + x; 
          int ky = dy[k] + y; 
          if(0 < kx && kx <= n && 0 < ky && ky <= m && !vis[kx][ky] && !fenw.query(kx, ky, kx, ky)) { 
            nq.push({kx, ky}); 
            vis[kx][ky] = true; 
          }
        }
      }
      cin >> r1 >> c1 >> r2 >> c2; 
      fenw.upd(r1, c1, r2, c2, true);  
      dq.swap(nq);
    } 
    pair<int, int>ret = {int(1e9), int(1e9)}; 
    for(int i = 1; i <= n; i++) { 
      for(int j = 1; j <= m; j++) { 
        if(vis[i][j] && !fenw.query(i, j, i, j)){ 
          ret = min(ret, {i, j}); 
        }
      }
    }
    if(ret.first == int(1e9)) cout << -1 << '\n'; 
    else cout << ret.first << " " << ret.second << '\n'; 
    return 0; 
}