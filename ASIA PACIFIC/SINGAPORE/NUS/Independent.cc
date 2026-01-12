#include "bits/stdc++.h"

using namespace std; 


int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N, K; 
 cin >> N >> K; 
 vector<int>b(N); 
 for(int i = 0; i < N; i++) { 
  cin >> b[i]; 
 }
 vector<int>pw3(K + 1, 1); 
 for(int i = 1; i <= K; i++) { 
  pw3[i] = pw3[i - 1] * 3; 
 }
 int64_t ans = 0; 
 function<int64_t(int, int, int)> dfs = [&](int k, int x, int y) -> int64_t { 
  if(k == K) {
  // cout << x << " " << y << '\n';  
   return x < y ? (b[x] > b[y]) : b[x] < b[y];  
  }
  int64_t ans = 0; 
  ans += dfs(k + 1, x, y + pw3[k]) + 
         dfs(k + 1, x, y + 2 * pw3[k]) + 
         dfs(k + 1, x + pw3[k], y) + 
         dfs(k + 1, x + pw3[k], y + 2 * pw3[k]) + 
         dfs(k + 1, x + 2 * pw3[k], y) + 
         dfs(k + 1, x + 2 * pw3[k], y + pw3[k]); 
  return ans; 
 }; 
 cout << dfs(0, 0, 0) / 2 << '\n'; 
 return 0; 
}