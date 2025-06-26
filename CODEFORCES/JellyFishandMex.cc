#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int64_t oo = 1e15; 

void solve(void) { 
 int N; 
 cin >> N;
 vector<int>a(N); 
 vector<int>coord; 
 for(int i = 0; i < N; i++) { 
  cin >> a[i]; 
  coord.push_back(a[i]); 
 }
 sort(coord.begin(), coord.end()); 
 coord.erase(unique(coord.begin(), coord.end()), coord.end()); 
 vector<int>freq(sz(coord)); 
 for(int i = 0; i < N; i++) { 
  int pos = lower_bound(coord.begin(), coord.end(), a[i]) - coord.begin(); 
  freq[pos]++; 
 }
 if(coord[0] > 0) { 
  cout << 0 << '\n'; 
  return; 
 }
 int start, M = sz(coord); 
 for(start = 0; start + 1 < M; start++) { 
  if(coord[start] + 1 != coord[start + 1]) { break; }
 }
 vector<vector<int64_t>>dp(M + 1, vector<int64_t>(M + 2, -1)); 
 function<int64_t(int, int)> memo = [&](int pos, int bound) -> int64_t { 
  if(pos == 0) return (freq[0] - 1) * (coord[bound] + 1); 
  int64_t &ret = dp[pos][bound]; 
  if(ret != -1) return ret; 
  ret = oo; 
  ret = min(ret, memo(pos - 1, pos - 1) + 1LL * (freq[pos] - 1) * (coord[bound] + 1) + coord[pos]);  // erase all of this element and get the bound equals the second
  ret = min(ret, memo(pos - 1, bound)); // Leave it for the lower to execute  
  return ret; 
 }; 
 cout << memo(start, start) << '\n'; 
 return; 
}

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);
 int T; 
 for(cin >> T; T--; ) { 
  solve(); 
 }
 return 0; 
}