#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int oo = 1e7; 

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int R, C;
  cin >> R >> C; 
  vector<vector<char>>g(R, vector<char>(C)); 
  pair<int, int>src = {-1, -1}, sink = {-1, -1}; 
  for(int i = 0; i < R; i++) { 
    for(int j = 0; j < C; j++) { 
      cin >> g[i][j];   
      if(g[i][j] == 'A') { 
        if(src.first == -1) src = {i, j}; 
        else sink = {i, j}; 
      }
    }
  }
  vector<vector<pair<int, int>>>comp; 
  vector<vector<int>>cc(R, vector<int>(C, -1)), marked(R, vector<int>(C)); 
  const int dx[4] = {1, -1, 0, 0}; 
  const int dy[4] = {0, 0, -1, 1}; 
  function<void(int, int, int)> dfs = [&](int i, int j, int ind) { 
    if(g[i][j] != 'O' && g[i][j] != '.') return; 
    cc[i][j] = ind; 
    comp[ind].push_back({i, j}); 
    marked[i][j] = true; 
    for(int k = 0; k < 4; k++) {
      int ni = i + dx[k], nj = j + dy[k]; 
      if(0 <= ni && ni < R && 0 <= nj && nj < C && !marked[ni][nj]) { 
        dfs(ni, nj, ind); 
      } 
    } 
    return; 
  };
  int c = 0; 
  for(int i = 0; i < R; i++) { 
    for(int j = 0; j < C; j++) {
      if(marked[i][j] || g[i][j] == '#' || g[i][j] == 'A') continue; 
      comp.push_back({}); 
      dfs(i, j, c++);   
    }
  } 
  auto dij = [&](int src_x, int src_y) { 
    vector<vector<int>>dist(R, vector<int>(C, oo)), visited(R, vector<int>(C)); 
    vector<vector<pair<int, int>>>par(R, vector<pair<int, int>>(C, {-1, -1})); 
    using T = tuple<int, int, int>;
    priority_queue<T, vector<T>, greater<T>>pq; 
    dist[src_x][src_y] = (g[src_x][src_y] == 'O'); 
    pq.push({dist[src_x][src_y], src_x, src_y}); 
    while(sz(pq)) { 
      auto [d, i, j] = pq.top(); 
      pq.pop(); 
      if(dist[i][j] != d) continue; 
      for(int k = 0; k < 4; k++) { 
        int ni = i + dx[k], nj = j + dy[k]; 
        if(ni < 0 || ni >= R || nj < 0 || nj >= C || g[ni][nj] == '#') continue; 
        if(g[ni][nj] == 'A') { 
          if(dist[ni][nj] > dist[i][j]) { 
            par[ni][nj] = {i, j}; 
            dist[ni][nj] = dist[i][j]; 
          }
        }
        else {
          if(dist[ni][nj] > dist[i][j] + (g[ni][nj] == 'O')) { 
            dist[ni][nj] = dist[i][j] + (g[ni][nj] == 'O'); 
            par[ni][nj] = {i, j}; 
            pq.push({dist[ni][nj], ni, nj}); 
          }  
        }
      }
    }
    if(dist[sink.first][sink.second] < oo) {
      if(dist[sink.first][sink.second] & 1) { 
        pair<int, int> at = sink; 
        while(at.first != -1) { 
          visited[at.first][at.second] = true; 
          at = par[at.first][at.second]; 
        }
        int ctr = 0; 
        for(auto [r, c] : comp[cc[src_x][src_y]]) { 
          if(!visited[r][c] && g[r][c] == 'O') ctr++;   
        }
        dist[sink.first][sink.second] = (ctr > 0 ? 1 + dist[sink.first][sink.second] : oo); 
      }
    } 
    return dist[sink.first][sink.second]; 
  }; 
  int ret = oo; 
  for(int k = 0; k < 4; k++) { 
    int ni = src.first + dx[k], nj = src.second + dy[k];
    if(ni < 0 || ni >= R || nj < 0 || nj >= C || g[ni][nj] == '#') continue;
    ret = min(ret, dij(ni, nj)); 
  }
  cout << (ret == oo ? -1 : ret / 2 + 1) << '\n'; 
  return 0;
}