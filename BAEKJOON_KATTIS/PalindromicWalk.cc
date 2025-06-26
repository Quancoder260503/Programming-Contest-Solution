#include <bits/stdc++.h> 

using namespace std; 

#define sz(x) int(x.size())

const int64_t oo = LLONG_MAX / 2; 

void solve() { 
 int N, M, S, E; 
 cin >> N >> M >> S >> E; 
 vector<vector<tuple<int, int, char>>>g(N); 
 char c; 
 --S, --E; 
 for(int i = 0, u, v, w; i < M; i++) { 
  cin >> u >> v >> w >> c; 
  --u, --v;
  g[u].push_back({v, w, c}); 
  g[v].push_back({u, w, c}); 
 } 
 vector<vector<int64_t>>dp(N, vector<int64_t>(N, oo)); 
 using T = tuple<int64_t, int, int>; 
 priority_queue<T, vector<T>, greater<T>>pq; 
 for(int i = 0; i < N; i++) { 
  pq.push({0, i, i}); 
 } 
 for(int i = 0; i < N; i++) { 
  for(auto [v, cost, _] : g[i]) {
    pq.push({cost, i, v}); 
  } 
 } 
 while(sz(pq)) { 
  auto [dist, start, end] = pq.top(); 
  pq.pop(); 
  if(dp[start][end] != oo) continue; 
  dp[start][end] = dp[end][start] = dist; 
  for(auto [vstart, costv1, vc1] : g[start]) {
   for(auto [vend, costv2, vc2] : g[end]) { 
    if(vc1 == vc2 && dp[vstart][vend] > dp[start][end] + costv1 + costv2) {
     pq.push({dp[start][end] + costv1 + costv2, vstart, vend}); 
    } 
   } 
  } 
 }
 int64_t ret  = min(dp[S][E], dp[E][S]); 
 if(ret == oo) ret = -1; 
 cout << ret << '\n'; 
 return; 
} 

int main() {
  int T; 
  for(cin >> T; T--; ) { 
    solve(); 
  } 
  return 0; 
}