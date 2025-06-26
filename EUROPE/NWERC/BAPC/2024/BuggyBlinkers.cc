#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int oo = 1e9; 

int dp[5002][22][3][4]; 

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N, M;
 cin >> N >> M; 
 vector<array<int, 4>>dest(N); 
 for(int i = 0; i < N; i++) { 
  for(int j = 0; j < 4; j++) { 
   cin >> dest[i][j];
   dest[i][j]--;  
  }
 }
 memset(dp, 63, sizeof(dp)); 
 queue<array<int, 4>>q; 
 for(int i = 0; i < 4; i++) { 
  q.push({0, 0, 1, i}); 
  dp[0][0][1][i] = 0; 
 }
 while(sz(q)) { 
  auto [u, num_blinks, blink_dir, cars_dir] = q.front(); 
  if(u == N - 1) { 
   cout << dp[u][num_blinks][blink_dir][cars_dir] << '\n'; 
   return 0; 
  }
  q.pop(); 
  for(int j = 0; j < 3; j++) { 
   int new_num_blinks = num_blinks + (j != 1 && blink_dir != j);
   if(new_num_blinks > M) continue; 
   int pos = dest[u][(j + cars_dir + 1) % 4]; 
   if(pos < 0) continue; 
   int next_car_dirs = find(dest[pos].begin(), dest[pos].end(), u) - dest[pos].begin(); 
   int &ret = dp[pos][new_num_blinks][j][next_car_dirs]; 
   if(ret > 1 + dp[u][num_blinks][blink_dir][cars_dir]) { 
    ret = 1 + dp[u][num_blinks][blink_dir][cars_dir];
    q.push({pos, new_num_blinks, j, next_car_dirs}); 
   }
  }
 } 
 cout << "impossible\n"; 
 return 0; 
}