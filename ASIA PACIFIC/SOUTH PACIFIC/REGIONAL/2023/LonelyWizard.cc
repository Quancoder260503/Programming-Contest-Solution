#include "bits/stdc++.h"

using namespace std;

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);  
  int N, F; 
  cin >> N >> F;
  vector<vector<int>>g(N, vector<int>(N)); 
  for(int i = 0, u, v; i < F; i++) { 
    cin >> u >> v;
    --u, --v; 
    g[u][v] = g[v][u] = 1; 
  } 
  int ret = 0; 
  for(int mask = 0; mask < (1 << N); mask++) { 
    vector<int>a, b; 
    for(int i = 0; i < N; i++) { 
      if(mask & (1 << i)) a.push_back(i); 
      else b.push_back(i); 
    }
    int ctr = 0; 
    for(auto &x : a) for(auto &y : a) { 
      ctr += g[x][y]; 
    }
    for(auto &x : b) for(auto &y : b) { 
      ctr += g[x][y]; 
    }
    ctr = ctr / 2; 
    ret = max(ret, F - ctr); 
  }
  cout << ret << '\n'; 
  return 0; 
}