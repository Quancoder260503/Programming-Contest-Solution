#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int oo = 1e9; 

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N; 
  cin >> N;
  vector<array<int, 4>>crane; 
  for(int i = 0, h, x, y; i < N; i++) { 
   cin >> x >> y >> h; 
   crane.push_back({h, x, y, i}); 
  } 
  sort(crane.rbegin(), crane.rend()); 
  vector<int>ans(N); 
  for(int i = 0; i < N; i++) { 
   int curr = crane[i][0]; 
   for(int j = 0; j < i; j++) { 
    int dist = int(hypot(crane[i][1] - crane[j][1], crane[i][2] - crane[j][2])); 
    curr = min(curr, dist); 
   }
   ans[crane[i][3]] = curr; 
  }
  for(int i = 0; i < N; i++) { 
   cout << ans[i] << '\n'; 
  }
  return 0; 
}
