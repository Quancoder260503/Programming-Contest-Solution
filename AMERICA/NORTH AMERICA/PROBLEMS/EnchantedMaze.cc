#include <iostream>
#include <iomanip>
#include <vector>
#include <array>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <utility>
#include <queue>
#include <climits>
#include <cstring>

using namespace std;

#define sz(x) int(x.size()

const int maxn = 20;

int dp[maxn][maxn][maxn][maxn][1 << 4];

int main(void) {
 ios_base::sync_with_stdio(false);
 cin.tie(0);
 cout.tie(0);
 int n, m;
 cin >> n >> m;
 vector<vector<char>>g(n, vector<char>(m));
 pair<int, int>start_a{-1, -1}, start_b{-1, -1};
 for(int i = 0; i < n; i++) {
  for(int j = 0; j < m; j++) {
   cin >> g[i][j];
   if(g[i][j] == 'S') {
    if(start_a.first == -1) start_a = {i, j};
    else                    start_b = {i, j};
   }
  }
 }
 const int dx[4] = {-1, 1, 0, 0};
 const int dy[4] = {0, 0, -1, 1};
 auto get_next = [&](int ni, int nj, int mask) -> char {
  char c = g[ni][nj];
  if('A' <= c && c <= 'D') {
   return mask >> (c - 'A') & 1 ? (c - 'A' + 'a') : c;
  }
  if('a' <= c && c <= 'd') {
   return mask >> (c - 'a') & 1 ? (c - 'a' + 'A') : c;
  }
  return c;
 };
 memset(dp, -1, sizeof dp);
 dp[start_a.first][start_a.second][start_b.first][start_b.second][0] = 0;
 queue<array<int, 5>>q;
 q.push({start_a.first, start_a.second, start_b.first, start_b.second, 0});
 while(q.size()) {
  auto [x_a, y_a, x_b, y_b, mask] = q.front();
  q.pop();
  int d = dp[x_a][y_a][x_b][y_b][mask];
  if(g[x_a][y_a] == 'E' && g[x_b][y_b] == 'E') {
   cout << d << '\n';
   return 0;
  }
  for(int k = 0; k < 4; k++) {
   int nx_a = x_a + dx[k], ny_a = y_a + dy[k];
   int nx_b = x_b + dx[k], ny_b = y_b + dy[k];
   if(nx_a < 0 || nx_a >= n || ny_a < 0 || ny_a >= m) continue;
   if(nx_b < 0 || nx_b >= n || ny_b < 0 || ny_b >= m) continue;
   if(g[nx_a][ny_a] == '*' || g[nx_b][ny_b] == '*') {
    continue;
   }
   char c_a = get_next(nx_a, ny_a, mask);
   char c_b = get_next(nx_b, ny_b, mask);
   if(c_a == '#' || ('A' <= c_a && c_a <= 'D')) nx_a = x_a, ny_a = y_a;
   if(c_b == '#' || ('A' <= c_b && c_b <= 'D')) nx_b = x_b, ny_b = y_b;
   if(nx_a == nx_b && ny_a == ny_b) continue;
   if(nx_a == x_b && ny_a == y_b && nx_b == x_a && ny_b == y_a) continue;
   c_a = get_next(nx_a, ny_a, mask);
   c_b = get_next(nx_b, ny_b, mask);
   int flag = false;
   for(int j = 0; j < 4; j++) {
    if(c_a == ('1' + j) && c_b == ('a' + j) && (nx_a != x_a || ny_a != y_a)) flag = true;
    if(c_b == ('1' + j) && c_a == ('a' + j) && (nx_b != x_b || ny_b != y_b)) flag = true;
   }
   if(flag) continue;
   int cur_mask = mask;
   for(int j = 0; j < 4; j++) {
    int l = (c_a == ('1' + j) && c_b == ('A' + j));
    int r = (c_b == ('1' + j) && c_a == ('A' + j));
    if(l || r) {
     cur_mask = cur_mask ^ (1 << j);
     if(l && nx_b == x_b && ny_b == y_b) cur_mask = mask;
     if(r && nx_a == x_a && ny_a == y_a) cur_mask = mask;
     goto nxt;
    }
   }
   if('1' <= c_a && c_a <= '4' && (nx_a != x_a || ny_a != y_a)) cur_mask ^= 1 << (c_a - '1');
   if('1' <= c_b && c_b <= '4' && (nx_b != x_b || ny_b != y_b)) cur_mask ^= 1 << (c_b - '1');
  nxt:;
   if(dp[nx_a][ny_a][nx_b][ny_b][cur_mask] == -1) {
    dp[nx_a][ny_a][nx_b][ny_b][cur_mask] = d + 1;
    q.push({nx_a, ny_a, nx_b, ny_b, cur_mask});
   }
  }
 }
 return 0;
}
