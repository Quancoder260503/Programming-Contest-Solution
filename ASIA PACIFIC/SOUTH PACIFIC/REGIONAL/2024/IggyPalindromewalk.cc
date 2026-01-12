#include "bits/stdc++.h"

using namespace std;  

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int n, m; 
 cin >> n >> m;
 vector<char>c(n); 
 for(int i = 0; i < n; i++) { 
  cin >> c[i]; 
 }
 vector<vector<int>>dp(n, vector<int>(n, -1)), g(n), rev_g(n);
 vector<vector<pair<int, int>>>par(n, vector<pair<int, int>>(n, {-1, -1}));   
 for(int i = 0, u, v; i < m; i++) { 
  cin >> u >> v; 
  --u, --v; 
  g[u].push_back(v); 
  rev_g[v].push_back(u); 
 }
 queue<pair<int, int>>q;  
 for(int i = 0; i < n; i++) { 
  dp[i][i] = 1; 
  q.push({i, i}); 
 }
 for(int i = 0; i < n; i++) { 
  for(auto v : g[i]) { 
   if(c[i] == c[v] && dp[i][v] == -1) { 
    dp[i][v] = 2; 
    q.push({i, v}); 
   }
  }
  for(auto u : rev_g[i]) { 
   if(c[i] == c[u] && dp[u][i] == -1) { 
    dp[u][i] = 2; 
    q.push({u, i}); 
   }
  }
 }
 while(q.size()) { 
  auto [u, v] = q.front(); 
  q.pop(); 
  for(auto nu : rev_g[u]) { 
   for(auto nv : g[v]) { 
    if(c[nu] == c[nv] && dp[nu][nv] == -1) { 
     dp[nu][nv] = dp[u][v] + 2;
     par[nu][nv] = {u, v}; 
     q.push({nu, nv}); 
    }
   }
  }
 }
 if(dp[0][n - 1] == -1) cout << "Impossible\n"; 
 else { 
  cout << "Possible\n" << dp[0][n - 1] << '\n';
  int ni = 0, nj = n - 1; 
  vector<pair<int, int>>res; 
  deque<int>dq; 
  while(ni != -1 && nj != -1) { 
   res.push_back({ni, nj}); 
   auto [nni, nnj] = par[ni][nj]; 
   ni = nni, nj = nnj;  
  }
  reverse(res.begin(), res.end()); 
  for(auto [u, v] : res) { 
   dq.push_front(u); 
   if(u != v) dq.push_back(v); 
  }
  for(auto x : dq) cout << x + 1 << ' '; 
  cout << '\n'; 
 } 
 return 0; 
}