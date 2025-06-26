#include "bits/stdc++.h"

using namespace std;

const int maxf = 1000; 

int vis[maxf][maxf], deg[maxf][maxf], ret[maxf][maxf]; 

const int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2}; 
const int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

void doit(int x, int y, int id) {
  ret[x][y] = id;  
  vis[x][y] = true;
  for(int dir = 0; dir < 8; dir++) { 
    int _nx = x + dx[dir], _ny = y + dy[dir]; 
    if(0 <= _nx && _nx < 8 && 0 <= _ny && _ny < 8 && !vis[_nx][_ny]) { 
      deg[_nx][_ny]--; 
    }
  }
  return; 
}

void doit2(int x, int y) {
  ret[x][y] = -1; 
  vis[x][y] = false;
  for(int dir = 0; dir < 8; dir++) { 
    int _nx = x + dx[dir], _ny = y + dy[dir]; 
    if(0 <= _nx && _nx < 8 && 0 <= _ny && _ny < 8 && !vis[_nx][_ny]) { 
      deg[_nx][_ny]++; 
    }
  }
  return; 
}

int dfs(int x, int y, int id) { 
  doit(x, y, id); 
  if(id >= 64) return true; 
  vector<tuple<int, int, int>>sort_me; 
  for(int dir = 0; dir < 8; dir++) { 
    int _nx = x + dx[dir], _ny = y + dy[dir]; 
    if(0 <= _nx && _nx < 8 && 0 <= _ny && _ny < 8 && !vis[_nx][_ny]) { 
      sort_me.push_back({deg[_nx][_ny], _nx, _ny}); 
    }
  }
  sort(sort_me.begin(), sort_me.end()); 
  for(auto [_, nx, ny] : sort_me) { 
    if(dfs(nx, ny, id + 1)) return true; 
  }
  doit2(x, y); 
  return false; 
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0); 
  cout.tie(0);   
  for(int x = 0; x < 8; x++) { 
    for(int y = 0; y < 8; y++) {
      for(int dir = 0; dir < 8; dir++) { 
        int _nx = x + dx[dir], _ny = y + dy[dir]; 
        if(0 <= _nx && _nx < 8 && 0 <= _ny && _ny < 8) { 
           deg[x][y]++; 
        }
      }
    }
  }
  int x, y; 
  cin >> y >> x; 
  dfs(x - 1, y - 1, 1); 
  for(int i = 0; i < 8; i++) { 
    for(int j = 0; j < 8; j++) {
        cout << ret[i][j] << " "; 
    }
    cout << '\n'; 
  }
  return 0;
}