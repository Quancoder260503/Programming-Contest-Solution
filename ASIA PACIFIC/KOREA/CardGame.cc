#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <cstring>

using namespace std;

const int maxn = 30;

int n, m, grundy[2][maxn][maxn][maxn][maxn];
char s[maxn][maxn], g[2][maxn][maxn];

int Grundy(int s, int st_x, int st_y, int en_x, int en_y) {
 if(st_x > en_x || st_y > en_y) return 0;
 int &ret = grundy[s][st_x][st_y][en_x][en_y];
 if(ret != -1) return ret;
 unordered_set<int>ms;
 for(int i = st_x; i <= en_x; i++) {
  for(int j = st_y; j <= en_y; j++) {
   int curr = 0;
   if(g[s][i][j] == 'R') {
    curr = curr ^ Grundy(s, st_x, st_y, i - 1, en_y);
    curr = curr ^ Grundy(s, i + 1, st_y, en_x, en_y);
    ms.insert(curr);
   } else if(g[s][i][j] == 'B') {
    curr = curr ^ Grundy(s, st_x, st_y, en_x, j - 1);
    curr = curr ^ Grundy(s, st_x, j + 1, en_x, en_y);
    ms.insert(curr);
   } else if(g[s][i][j] == 'G') {
    curr = curr ^ Grundy(s, st_x, st_y, i - 1, j - 1);
    curr = curr ^ Grundy(s, st_x, j + 1, i - 1, en_y);
    curr = curr ^ Grundy(s, i + 1, st_y, en_x, j - 1);
    curr = curr ^ Grundy(s, i + 1, j + 1, en_x, en_y);
    ms.insert(curr);
   }
  }
 }
 ret = 0;
 while(ms.count(ret)) ret++;
 return ret;
}

int main(void) {
 cin >> n >> m;
 for(int i = 0; i < maxn; i++) {
  for(int j = 0; j < maxn; j++) {
   g[0][i][j] = g[1][i][j] = '.';
  }
 }
 for(int i = 0; i < n; i++) {
  for(int j = 0; j < m; j++) {
   cin >> s[i][j];
   g[(i + j) % 2][(i + j) / 2][(i - j + m - 1) / 2] = s[i][j];
  }
 }
 memset(grundy, -1, sizeof grundy);
 int ret = Grundy(0, 0, 0, maxn - 1, maxn - 1) ^ Grundy(1, 0, 0, maxn - 1, maxn - 1);
 cout << ("LW"[ret > 0]) << '\n';
 return 0;
}
