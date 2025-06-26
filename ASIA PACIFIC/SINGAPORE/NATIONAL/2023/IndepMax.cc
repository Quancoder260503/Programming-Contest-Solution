#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int maxf = 2e5 + 10; 

vector<int>graph[maxf]; 
int N, dp[maxf][2]; 

void dfs(int u, int p) { 
  dp[u][0] = 0; 
  dp[u][1] = 1; 
  for(auto v : graph[u]) { 
    if(v == p) continue; 
    dfs(v, u); 
    dp[u][1] += dp[v][0]; 
    dp[u][0] += max(dp[v][1], dp[v][0]); 
  }
  return; 
}

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  cin >> N;
  if(N == 2) { 
    cout << 0 << '\n'; 
    return 0; 
  }
  for(int i = 0, u, v; i < N - 1; i++) { 
    cin >> u >> v;
    graph[u].push_back(v); 
    graph[v].push_back(u); 
  }
  dfs(1, 0); 
  cout << 1LL * max(dp[1][0], dp[1][1]) * (N - 1) << '\n'; 
  return 0; 
}