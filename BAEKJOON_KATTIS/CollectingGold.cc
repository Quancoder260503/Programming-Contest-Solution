#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int64_t oo = LLONG_MAX / 2; 

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 vector<int>primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67}; 
 int N, M; 
 cin >> N >> M; 
 unordered_map<int64_t, int>mp; 
 vector<int64_t>a(N); 
 for(int i = 0; i < N; i++) { 
  cin >> a[i]; 
  mp[a[i]] = i; 
 }
 vector<vector<pair<int, int>>>g(N); 
 vector<vector<int>>par(N); 
 for(int i = 0; i < M; i++) { 
  int64_t x, y, c; 
  cin >> x >> y >> c; 
  g[mp[x]].push_back({mp[y], c}); 
  g[mp[y]].push_back({mp[x], c}); 
 }
 vector<int64_t>dist(N); 
 auto dij = [&](int st, int en) {
  fill(dist.begin(), dist.end(), oo);
  dist[st] = 0; 
  using T = pair<int64_t, int>; 
  priority_queue<T, vector<T>, greater<T>>pq; 
  pq.push({dist[st], st}); 
  while(sz(pq)) { 
   auto [d, u] = pq.top(); 
   pq.pop(); 
   if(dist[u] != d) continue; 
   for(auto [v, c] : g[u]) { 
    if(dist[v] == dist[u] + c) { 
     par[v].push_back(u);    
    } else if(dist[v] > dist[u] + c) { 
     dist[v] = dist[u] + c; 
     pq.push({dist[v], v}); 
     par[v].clear(); 
     par[v].push_back(u);
    }
   }
  }   
 };
 int64_t mx = *max_element(a.begin(), a.end()); 
 int64_t mn = *min_element(a.begin(), a.end()); 
 int st = 0, en = 0; 
 for(int i = 0; i < N; i++) { 
  if(a[i] == mx) { en = i; }
  if(a[i] == mn) { st = i; }
 } 
 dij(st, en); 
 vector<int>cost(N); 
 for(int i = 0; i < N; i++) {
  int64_t c = 1; 
  int j;  
  for(j = 0; j < sz(primes) && c <= a[i] / primes[j]; j++) { 
   c = c * primes[j]; 
  }
  cost[i] = j; 
 }
 vector<int>dp(N, -1);
 function<int(int)> dfs = [&](int u) { 
  int &ret = dp[u];
  if(ret != -1) return ret; 
  ret = cost[u]; 
  for(auto v : par[u]) { 
   ret = max(ret, dfs(v) + cost[u]); 
  }
  return ret; 
 }; 
 cout << dfs(en) << '\n'; 
 return 0; 
}