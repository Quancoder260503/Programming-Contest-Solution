#include <bits/stdc++.h> 

using namespace std; 

#define sz(x) int(x.size())

int main() {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N, C, T; 
 for(cin >> T; T--; ) { 
  cin >> C >> N; 
  vector<pair<int, int>>a(N); 
  for(int i = 0; i < N; i++) {
   cin >> a[i].first >> a[i].second; 
  }
  vector<int>dp(C + 1, -1); 
  dp[0] = 0; 
  for(int i = 0; i < N; i++) {
   for(int w = C; w >= a[i].first; w--) {
    if(dp[w - a[i].first] == -1) continue; 
    dp[w] = max(dp[w], dp[w - a[i].first] + a[i].second); 
   } 
  }
  cout << *max_element(dp.begin(), dp.end()) << '\n'; 
 } 
 return 0;
}