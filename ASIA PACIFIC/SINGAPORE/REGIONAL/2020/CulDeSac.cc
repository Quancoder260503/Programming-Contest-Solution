#include "bits/stdc++.h"
 
using namespace std; 
 
#define int64_t long long
#define sz(x) int(x.size())
 
const int oo = 1e9; 
 
class Culdesac { 
 public :
  void solve() { 
  int N; 
  cin >> N; 
  vector<vector<pair<int, int>>>g(N); 
  for(int i = 0, u, v, w; i < N - 1; i++) { 
   cin >> u >> v >> w;  
   --u, --v; 
   g[u].push_back({v, w}); 
   g[v].push_back({u, w}); 
  }
  function<pair<int64_t, int64_t>(int, int)> dfs = [&](int u, int p) -> pair<int64_t, int64_t> {
   int first = true; 
   pair<int64_t, int64_t>ret = make_pair(0, 0);
   for(auto [v, w] : g[u]) { 
    if(v == p) continue; 
    pair<int64_t, int64_t> curr = dfs(v, u);  
    if(first) { 
     ret = make_pair(ret.first + curr.first, ret.first + curr.second + w); 
     first = false; 
    } else { 
     ret = make_pair(max(ret.first + curr.first, ret.second + curr.second + w),
                     max(ret.second + curr.first, ret.first + curr.second + w)); 
    }
   }
   return ret;  
  }; 
  pair<int64_t, int64_t>ans = dfs(0, -1); 
  if(sz(g[0]) == 1) { 
    ans.first = max(ans.first, ans.second); 
  }
  cout << ans.first << '\n'; 
  return; 
 } 
}; 
 
int main(void) { 
  Culdesac task; 
  task.solve(); 
  return 0; 
}