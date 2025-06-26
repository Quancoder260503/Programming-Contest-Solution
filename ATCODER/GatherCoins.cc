#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int H, W, N; 
  cin >> H >> W >> N; 
  vector<pair<int, int>>coins(N); 
  for(int i = 0; i < N; i++) { 
   cin >> coins[i].first >> coins[i].second; 
  }
  sort(coins.begin(), coins.end(), [&](pair<int, int>a, pair<int, int> b) { 
   return a.first == b.first ? a.second < b.second : a.first < b.first;
  }); 
  vector<int>dp(N, 1e9), ind(N, -1), pre(N); 
  for(int i = 0; i < N; i++) { 
   int pos = upper_bound(dp.begin(), dp.end(), coins[i].second) - dp.begin(); 
   dp[pos] = coins[i].second; 
   ind[pos] = i; 
   pre[i] = (pos ? ind[pos - 1] : -1);
//   cout << pre[i] << '\n';  
  }
  int m = N - 1, ret = 0;
  for(int i = 0; i < N; i++) { 
   ret += (ind[i] != -1); 
   //cout << ind[i] << " " << pre[i] << " " << coins[i].first << " " << coins[i].second << '\n'; 
  } 
  cout << ret << '\n'; 
  while(ind[m] == -1) {m--; }
  m = ind[m]; 
  vector<pair<int, int>>path; 
  while(m != -1) { 
   path.push_back(coins[m]); 
   m = pre[m]; 
  }
  auto printDist = [&](int r, int c, int r1, int c1) { 
  // cout << r << " " << c << " " << r1 << " " << c1 << '\n'; 
   for(int i = r; i < r1; i++) { cout << "D"; }
   for(int i = c; i < c1; i++) { cout << "R"; }
  }; 
  int start_x = 1, start_y = 1;
  reverse(path.begin(), path.end());  
  for(int i = 0; i < sz(path); i++) { 
 //  cout << path[i].first << " " << path[i].second << '\n'; 
   printDist(start_x, start_y, path[i].first, path[i].second ); 
   start_x = path[i].first, start_y = path[i].second ; 
  }
  printDist(start_x, start_y, H, W); 
  return 0; 
}