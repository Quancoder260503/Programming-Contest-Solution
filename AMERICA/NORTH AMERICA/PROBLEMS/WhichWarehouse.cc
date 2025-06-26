#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int oo = 1e8; 

pair<int, vector<int>> hungarian(const vector<vector<int>> &a) {
  if (a.empty()) return {0, {}};
  int n = sz(a) + 1, m = sz(a[0]) + 1;
  vector<int> u(n), v(m), p(m), ans(n - 1);
  for (int i = 1; i < n; i++) {
    p[0] = i;
    int j0 = 0;  // add "dummy" worker 0
    vector<int> dist(m, INT_MAX), pre(m, -1);
    vector<bool> done(m + 1);
    do {  // dijkstra
      done[j0] = true;
      int i0 = p[j0], j1, delta = INT_MAX;
      for (int j = 1; j < m; j++)
        if (!done[j]) {
          auto cur = a[i0 - 1][j - 1] - u[i0] - v[j];
          if (cur < dist[j]) dist[j] = cur, pre[j] = j0;
          if (dist[j] < delta) delta = dist[j], j1 = j;
        }
      for (int j = 0; j < m; j++) {
        if (done[j])
          u[p[j]] += delta, v[j] -= delta;
        else
          dist[j] -= delta;
      }
      j0 = j1;
    } while (p[j0]);
    while (j0) {  // update alternating path
      int j1 = pre[j0];
      p[j0] = p[j1], j0 = j1;
    }
  }
  for (int j = 1; j < m; j++)
    if (p[j]) ans[p[j] - 1] = j - 1;
  return {-v[0], ans};  // min cost
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int N, M; 
  cin >> N >> M; 
  vector<vector<int>>g(N, vector<int>(M)), dist(N, vector<int>(N)); 
  for(int i = 0; i < N; i++) { 
    for(int j = 0; j < M; j++) { 
      cin >> g[i][j]; 
    }
  }
  for(int i = 0; i < N; i++) { 
    for(int j = 0; j < N; j++) { 
      cin >> dist[i][j]; 
      if(dist[i][j] == -1) dist[i][j] = oo; 
    }
  }
  for(int k = 0; k < N; k++) { 
    for(int i = 0; i < N; i++) { 
      for(int j = 0; j < N; j++) { 
        if(dist[i][k] == oo || dist[k][j] == oo) continue; 
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]); 
      }
    }
  }
  vector<vector<int>>cost(N, vector<int>(M)); 
  for(int dst = 0; dst < N; dst++) { 
    for(int j = 0; j < M; j++) { 
      for(int src = 0; src < N; src++) { 
        cost[dst][j] += dist[src][dst] * g[src][j];
      }
    }
  }
  if(N > M) { 
    vector<vector<int>>transpose(M, vector<int>(N)); 
    for(int i = 0; i < N; i++) { 
      for(int j = 0; j < M; j++) { 
        transpose[j][i] = cost[i][j]; 
      }
    }
    cost = transpose; 
  }
  cout << hungarian(cost).first << '\n'; 
  return 0;
}