#include "bits/stdc++.h"

using namespace std;

const int64_t oo = 1e14; 
const int maxn = 5e5 + 5; 

vector<pair<int, int>>g[maxn]; 
unordered_map<int, int64_t>cache[maxn]; 
int n, m; 

int64_t dijsktra(int src, int dst) { 
  vector<int64_t>dp(n, oo); 
  dp[src] = 0; 
  using T = pair<int64_t, int>;
  priority_queue<T, vector<T>, greater<T>>pq; 
  pq.push({dp[src], src}); 
  while(pq.size()) { 
   auto [d, u] = pq.top(); 
   pq.pop(); 
   if(d != dp[u]) continue; 
   for(auto [v, w] : g[u]) { 
    if(dp[v] > dp[u] + w) { 
     dp[v] = dp[u] + w; 
     pq.push({dp[v], v}); 
    }
   }
  }
  return dp[dst]; 
}


int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);
 cin >> n >> m; 
 for(int i = 0, u, v, w; i < m; i++) { 
  cin >> u >> v >> w; 
  --u, --v; 
  g[u].push_back({v, w}); 
  g[v].push_back({u, w}); 
 }
 vector<int>cc(7); 
 for(auto &x : cc) { 
  cin >> x; 
  x--; 
  cache[0][x] = dijsktra(0, x); 
 }
 int64_t ans = oo; 
 sort(cc.begin(), cc.end()); 
 cc.erase(unique(cc.begin(), cc.end()), cc.end()); 
 do { 
  int64_t curr = cache[0][cc[0]];  
  for(int i = 0; i + 1 < cc.size(); i++) {
   int x = cc[i], y = cc[i + 1]; 
   if(cache[x].count(y))  { 
    curr += cache[x][y]; 
    continue;
   } 
   cache[x][y] = dijsktra(x, y); 
   curr += cache[x][y]; 
  }
  ans = min(ans, curr); 
 } while(next_permutation(cc.begin(), cc.end())); 
 cout << (ans == oo ? -1 : ans) << '\n'; 
 return 0; 
}