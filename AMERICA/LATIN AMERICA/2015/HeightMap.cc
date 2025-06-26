#include "bits/stdc++.h"

using namespace std;

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N, M; 
  cin >> N >> M;
  vector<vector<int>>height(N + 2, vector<int>(M + 2));
  vector<vector<int>>vis(N + 2, vector<int>(M + 2)); 
  int ret = 1; 
  auto F = [&](int i, int j, int x, int y, int r) { 
    int x1 = height[i][j],                 x2 = height[i + x][j + y]; 
    int y1 = height[i - 1 - x][j - 1 - y], y2 = height[i - 1][j - 1]; 
    if(r) { swap(x1, x2); swap(y1, y2); }
    if(x1 < x2 && (y2 <= y1 || y2 <= x1 || x2 <= y1)) ret++; 
    return; 
  };  
  for(int i = 1; i < N + 2; i++) { 
    for(int j = 1; j < M + 2; j++) { 
      if(i < N + 1 && j < M + 1) { 
        cin >> height[i][j]; 
      }
      F(i, j, -1, 0, false); 
      F(i, j, -1, 0, true); 
      F(i, j, 0, -1, false); 
      F(i, j, 0, -1, true); 
    }
  }
  const int dx[4] = {0, 0, -1, 1}; 
  const int dy[4] = {-1, 1, 0, 0};
  function<void(int, int)> doit = [&](int x, int y) { 
    if(vis[x][y]) return; 
    vis[x][y] = true; 
    for(int dir = 0; dir < 4; dir++) { 
      int px = dx[dir] + x, py = dy[dir] + y; 
      if(0 < px && px < N + 1 && 0 < py && py < M + 1 && height[x][y] == height[px][py]) { 
        doit(px, py); 
      }
    }
  }; 
  for(int i = 1; i < N + 1; i++) { 
    for(int j = 1; j < M + 1; j++) { 
      if(vis[i][j]) continue; 
      doit(i, j); 
      ret++; 
    }
  }
  cout << ret << '\n'; 
  return 0; 
}