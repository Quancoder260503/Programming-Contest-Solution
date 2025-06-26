#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int oo = 1e9; 

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  int N, M, K; 
  cin >> N >> K; 
  vector<vector<int>>g(N, vector<int>(N)); 
  vector<vector<pair<int, int>>>comp(K); 
  for(int i = 0; i < N; i++) { 
   for(int j = 0; j < N; j++) { 
    cin >> g[i][j]; 
    comp[--g[i][j]].push_back({i, j}); 
   }
  } 
  vector<vector<int>>dp(N, vector<int>(N, oo)); 
  for(auto [x, y] : comp[0]) { 
   dp[x][y] = 0;
  }
  for(int i = 1; i < K; i++) { 
   using T = array<int, 3>; 
   priority_queue<T, vector<T>, greater<T>>pq; 
   for(auto [x, y] : comp[i - 1]) { 
    if(dp[x][y] == oo) continue; 
    pq.push({dp[x][y], x, y});
   } 
   while(sz(pq)) { 
    auto [d, x, y] = pq.top(); 
    pq.pop(); 
    if(d != dp[x][y]) continue; 
    for(auto [x2, y2] : comp[i]) { 
     if(dp[x2][y2] > dp[x][y] + abs(x2 - x) + abs(y2 - y)) { 
      dp[x2][y2] = dp[x][y] + abs(x2 - x) + abs(y2 - y);
     }
    }
   }
  }
  int ret = oo; 
  for(auto [x, y] : comp[K - 1]) { 
   ret = min(ret, dp[x][y]); 
  }
  cout << (ret == oo ? -1 : ret) << '\n';   
  return 0; 
}