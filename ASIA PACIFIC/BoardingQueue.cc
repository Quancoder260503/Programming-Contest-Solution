#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int oo = 1e9; 

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);
 int r, c, n, src; 
 cin >> r >> c >> n >> src; 
 --src; 
 vector<vector<int>>g(r, vector<int>(c)); 
 vector<pair<int, int>>pos(n); 
 for(int i = 0; i < r; i++) { 
  for(int j = 0; j < c; j++) { 
   cin >> g[i][j];
   --g[i][j]; 
   if(g[i][j] >= 0) pos[g[i][j]] = {i, j}; 
  }
 }
 set<int>ms;
 const int dx[4] = {-1, 1, 0, 0}; 
 const int dy[4] = {0, 0, -1, 1}; 
 for(int i = 0; i <= src; i++) { 
  auto [x, y] = pos[src - i]; 
  for(int k = 0; k < 4; k++) { 
   int nx = x + dx[k], ny = y + dy[k]; 
   if(0 <= nx && nx < r && 0 <= ny && ny < c && g[nx][ny] != -1) { 
    if(g[nx][ny] + i != src && g[nx][ny] + i < n) { 
    // cout << g[nx][ny] << " " << i << " " << src << '\n'; 
     ms.insert(g[nx][ny] + i); 
    } 
   }
  }
 }
 cout << sz(ms) << "/" << (n - 1) << '\n'; 
 return 0; 
}