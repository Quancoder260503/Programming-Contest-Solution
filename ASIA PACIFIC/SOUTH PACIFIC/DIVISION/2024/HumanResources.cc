#include <bits/stdc++.h> 

using namespace std; 

#define sz(x) int(x.size())

int main() {
  int N, K; 
  cin >> N >> K; 
  vector<int>par(N, -1), h(N); 
  vector<vector<int>>g(N); 
  for(int i = 1; i < N; i++) { 
    cin >> par[i]; 
    par[i]--; 
    g[par[i]].push_back(i); 
    h[i] = h[par[i]] + 1; 
  } 
  vector<int>marked(N); 
  function<void(int, int)> dfs = [&](int u, int dist) { 
   if(dist > K || marked[u]) return; 
   marked[u] = true; 
   for(auto v : g[u]) { 
    dfs(v, dist + 1); 
   }
  }; 
  vector<int>ord(N); 
  iota(ord.begin(), ord.end(), 0); 
  sort(ord.begin(), ord.end(), [&](int i, int j) { 
    return h[i] > h[j];    
  }); 
  int ret = 0; 
  for(auto x : ord) { 
    if(!marked[x]) { 
      int cnt = 0; 
      while(par[x] != -1 && cnt < K) { 
       x = par[x]; 
       cnt++; 
      }
      dfs(x, 0);
      ret++; 
    } 
  }
  cout << ret << '\n'; 
  return 0;
}