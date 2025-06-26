#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int oo = 1e9;

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int N, M, T;
  cin >> T;
  const vector<int> dx = {0, 0, -1, 1};
  const vector<int> dy = {1, -1, 0, 0};
  for (int _case = 0; _case < T; _case++) {
    cin >> N >> M;
    vector<vector<int>> S(N, vector<int>(M)), W(N, vector<int>(M)),
        T(N, vector<int>(M));
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        cin >> S[i][j] >> W[i][j] >> T[i][j];
        T[i][j] %= (S[i][j] + W[i][j]);
      }
    }
    using Type = array<int, 3>;
    priority_queue<Type, vector<Type>, greater<Type>> pq;
    N = 2 * N;
    M = 2 * M;
    vector<vector<int>> dist(N, vector<int>(M, oo));
    dist[N - 1][0] = 0;
    pq.push({0, N - 1, 0});
    auto goNorthSouth = [&](int currX, int currY, int sx, int sy) {
      int lightX = currX / 2, lightY = currY / 2;
      if (dist[currX][currY] < T[lightX][lightY]) {
        if(dist[currX][currY] < T[lightX][lightY] - W[lightX][lightY]) {
          // Light currently turn green on north-south link 
           if(dist[sx][sy] > 1 + dist[currX][currY]) { 
             dist[sx][sy] = 1 + dist[currX][currY]; 
             pq.push({dist[sx][sy], sx, sy}); 
           }
        }
        else {
          // Light currenly turn red on north -> south link 
          if (dist[sx][sy] > 1 + (T[lightX][lightY] - dist[currX][currY]) + dist[currX][currY]) {
            dist[sx][sy] = 1 + (T[lightX][lightY] - dist[currX][currY]) + dist[currX][currY];
            pq.push({dist[sx][sy], sx, sy});
          }
        }
      } else {
        int modTime =
            (dist[currX][currY] - T[lightX][lightY]) % (W[lightX][lightY] + S[lightX][lightY]);
        if (modTime < S[lightX][lightY]) {
          // the north->south link turn green
          if (dist[sx][sy] > dist[currX][currY] + 1) {
            dist[sx][sy] = dist[currX][currY] + 1;
            pq.push({dist[sx][sy], sx, sy});
          }
        } else {
          // otherwise turn red we have to wait until it turn next green
          if (dist[sx][sy] > 1 + dist[currX][currY] +
                                 (W[lightX][lightY] + S[lightX][lightY]) -
                                 modTime) {
            dist[sx][sy] = dist[currX][currY] +
                           (W[lightX][lightY] + S[lightX][lightY] - modTime) +
                           1;
            pq.push({dist[sx][sy], sx, sy});
          }
        }
      }
      return;
    };
    auto goWestEast = [&](int currX, int currY, int sx, int sy) { 
     //if(currX == 0 && currY == 0) cout << currX << " " << currY << " " << sx << " " << sy << " " << d << '\n'; 
      int lightX = currX / 2, lightY = currY / 2;
      if (dist[currX][currY] < T[lightX][lightY]) {
        if(dist[currX][currY] >= T[lightX][lightY] - W[lightX][lightY]) { 
           // Light currenly turn green on west->east link
          if (dist[sx][sy] > 1 + dist[currX][currY]) {
            dist[sx][sy] = 1 + dist[currX][currY];
            pq.push({dist[sx][sy], sx, sy});
          }
        }
        else {
          // Light currenly turn red on west->east link 
          if (dist[sx][sy] > 1 + T[lightX][lightY] - W[lightX][lightY]) {
            dist[sx][sy] = 1 + T[lightX][lightY] - W[lightX][lightY];
            pq.push({dist[sx][sy], sx, sy});
          }
        }
      } else {
        int modTime =
            (dist[currX][currY] - T[lightX][lightY]) % (W[lightX][lightY] + S[lightX][lightY]);
        //if(currX == 0 && currY == 0) cout << currX << " " << currY << " " << sx << " " << sy << " " << modTime << '\n'; 
        if (modTime >= S[lightX][lightY]) {
          // the west->east link turn green
          if (dist[sx][sy] > dist[currX][currY] + 1) {
            dist[sx][sy] = dist[currX][currY] + 1;
            pq.push({dist[sx][sy], sx, sy});
          }
        } else {
          // otherwise turn red we have to wait until it turn next green
          if (dist[sx][sy] > 1 + S[lightX][lightY] - modTime + dist[currX][currY]) {
            dist[sx][sy] = 1 + S[lightX][lightY] - modTime + dist[currX][currY]; 
            pq.push({dist[sx][sy], sx, sy});
          }
        }
      }
    }; 
    while (sz(pq)) {
      auto [d, currX, currY] = pq.top();
      pq.pop();
      if (dist[currX][currY] != d) continue;
      for (int dir = 0; dir < 4; dir++) {
        int sx = dx[dir] + currX;
        int sy = dy[dir] + currY;
        if(sx < 0 || sy < 0 || sx >= N || sy >= M) continue;
        if (dx[dir] == 1) {
          if (currX % 2 == 1 && dist[sx][sy] > dist[currX][currY] + 2) {
            dist[sx][sy] = dist[currX][currY] + 2;
            pq.push({dist[sx][sy], sx, sy});
          }
          if (currX % 2 == 0) {
            goNorthSouth(currX, currY, sx, sy);
          }
        }
        if (dx[dir] == -1) {
          if (currX % 2 == 0 && dist[sx][sy] > dist[currX][currY] + 2) {
            dist[sx][sy] = dist[currX][currY] + 2;
            pq.push({dist[sx][sy], sx, sy});
          }
          if (currX % 2 == 1) {
            goNorthSouth(currX, currY, sx, sy);
          }
        }
        if (dy[dir] == 1) {
          if (currY % 2 == 1 && dist[sx][sy] > dist[currX][currY] + 2) {
            dist[sx][sy] = dist[currX][currY] + 2;
            pq.push({dist[sx][sy], sx, sy});
          }
          if(currY % 2 == 0) { 
            goWestEast(currX, currY, sx, sy); 
          }
        }
        if (dy[dir] == -1) {
          if (currY % 2 == 0 && dist[sx][sy] > dist[currX][currY] + 2) {
            dist[sx][sy] = dist[currX][currY] + 2;
            pq.push({dist[sx][sy], sx, sy});
          }
          if(currY % 2 == 1) { 
            goWestEast(currX, currY, sx, sy); 
          }
        }
      }
    } 
    cout << "Case #" << _case + 1 << ": " << dist[0][M - 1] << '\n'; 
  }
  return 0;
}
