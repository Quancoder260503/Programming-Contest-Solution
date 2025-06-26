#include "bits/stdc++.h"
 
using namespace std;
 
#define sz(x) int(x.size())
 
const int MOD = 1e9 + 7;
 
int main() {
 int N, M; 
 cin >> N >> M; 
 vector<vector<char>>g(N + 1, vector<char>(M + 1)); 
 for(int i = 1; i <= N; i++) { 
  for(int j = 1; j <= M; j++) { 
   cin >> g[i][j]; 
  } 
 } 
 vector<vector<vector<int64_t>>>dp(2, vector<vector<int64_t>>(N + 10, vector<int64_t>(N + 10)));
 auto inRange = [&](int a, int b) { 
  return 1 <= a & a <= N && 1 <= b && b <= M; 
 }; 
 if(g[1][1] == g[N][M]) {
  dp[0][1][N] = 1; 
 }
 int curr = 0; 
 for(int step = 0; step <= (M + N - 2) / 2; step++) { 
  curr = curr ^ 1; 
  for(int i = 0; i <= N; i++) { 
    fill(dp[curr][i].begin(), dp[curr][i].end(), 0); 
  }
  for(int x1 = 1; x1 <= N && x1 - 1 <= step; x1++) { 
   for(int x2 = N; x2 > 0 && N - x2 <= step; x2--) { 
    int y1 = 1 + step - (x1 - 1); 
    int y2 = M - step + (N - x2); 
    if(inRange(x1, y1) && inRange(x2, y2) && g[x1][y1] == g[x2][y2]) { 
     dp[curr][x1][x2] = dp[curr ^ 1][x1][x2] + dp[curr ^ 1][x1 - 1][x2] + 
                        dp[curr ^ 1][x1][x2 + 1] + dp[curr ^ 1][x1 - 1][x2 + 1]; 
     dp[curr][x1][x2] %= MOD; 
    } 
   } 
  } 
 }
 int64_t ret = 0; 
 for(int i = 1; i <= N; i++) {
  (ret += dp[curr][i][i]) %= MOD; 
 }
 if((M + N) & 1) { 
  for(int i = 1; i < N; i++) {
   (ret += dp[curr][i][i + 1]) %= MOD; 
  }
 } 
 cout << ret << '\n'; 
 /* 
 function<int64_t(int, int, int)> F = [&](int x, int y, int dist) -> int64_t {
  if(!inRange(x, y)) return 0; 
  int cx = N - (x + y - 2 - dist), cy = M - dist;
  if(y > cy || x > cx) return 0; 
  if(x + y - 1 == (N + M) / 2) {
   if((N + M - 1) & 1) { 
     return cx == x && cy == y; 
   } else { 
      
     return inRange(cx, cy) && abs(y - cy) <= 1 && abs(x - cx) <= 1 && g[x][y] == g[cx][cy];
   } 
  }
  if(dp[x][y].count(dist)) return dp[x][y][dist]; 
  int64_t ret = 0; 
  if(inRange(cx, cy) && g[x][y] == g[cx][cy]) { 
   ret = F(x + 1, y, dist) + F(x + 1, y, dist + 1) + F(x, y + 1, dist) + F(x, y + 1, dist + 1); 
   ret %= MOD; 
  } 
  return dp[x][y][dist] = ret; 
 }; 
 cout << F(1, 1, 0) << '\n';
 */ 
 return 0;
}