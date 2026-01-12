#include <algorithm>
#include <cstring>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

using ll = long long;

int dp[52][52][1005][3];

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n, m;
  cin >> n >> m;
  vector<vector<int>> g(n, vector<int>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> g[i][j];
    }
  }
  memset(dp, -1, sizeof dp);
  auto in = [&](int i, int j) { return 0 <= i && i < n && 0 <= j && j < n; };
  function<int(int, int, int, int)> memo = [&](int i, int j, int c, int k) -> int {
    if(c < 0) return -1e6; 
    if (i == n - 1 && j == n - 1) { 
      return (c >= g[i][j]);
    } 
    int& ret = dp[i][j][c][k];
    if (ret != -1) return ret;
    ret = -1e6;
    if (k == 0) {
      if (in(i, j - 1)) {
        ret = max(ret, memo(i, j - 1, c - 1, 1)); 
        if (c > g[i][j]) {
          ret = max(ret, 1 + memo(i, j - 1, c - 1 - g[i][j], 1));
        }
      }
      if (in(i, j + 1)) {
        ret = max(ret, memo(i, j + 1, c - 1, 2)); 
        if (c > g[i][j]) { 
          ret = max(ret, 1 + memo(i, j + 1, c - 1 - g[i][j], 2));   
        }
      }
      if (in(i + 1, j)) {
        ret = max(ret, memo(i + 1, j, c - 1, 0)); 
        if (c > g[i][j]) {
          ret = max(ret, 1 + memo(i + 1, j, c - 1 - g[i][j], 0));
        }
      }
    } else if (k == 1) {
      if (in(i, j - 1)) {
        ret = max(ret, memo(i, j - 1, c - 1, 1)); 
        if (c > g[i][j]) {
          ret = max(ret, 1 + memo(i, j - 1, c - 1 - g[i][j], 1));
        }
      }
      if (in(i + 1, j)) {
        ret = max(ret, memo(i + 1, j, c - 1, 0)); 
        if (c > g[i][j]) {
          ret = max(ret, 1 + memo(i + 1, j, c - 1 - g[i][j], 0));
        }
      } 
    } else {
      if (in(i, j + 1)) {
        ret = max(ret, memo(i, j + 1, c - 1, 2)); 
        if (c > g[i][j]) {
          ret = max(ret, 1 + memo(i, j + 1, c - 1 - g[i][j], 2));
        }
      }
      if (in(i + 1, j)) {
        ret = max(ret, memo(i + 1, j, c - 1, 0)); 
        if (c > g[i][j]) {
          ret = max(ret, 1 + memo(i + 1, j, c - 1 - g[i][j], 0));
        }
      }
    } 
    return ret;
  };
  cout << max(0, memo(0, 0, m, 0)) << '\n'; 
  return 0;
}
