#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

vector<vector<int>>g; 
int N, M; 
vector<int64_t>dyn; 

void dfs(int u, int p) { 
  dyn[u] = 1; 
  for(auto v : g[u]) if(v != p) { 
    dfs(v, u); 
    dyn[u] = dyn[u] % M * (1 + dyn[v]) % M; 
  }
  return; 
}

void dfs2(int u, int p, int64_t x) { 
  dyn[u] = dyn[u] % M * x % M; 
  vector<int64_t>prefix, suffix; 
  vector<int>ord; 
  for(auto v : g[u]) if(v != p) { 
    prefix.push_back(1 + dyn[v]); 
    ord.push_back(v); 
  }
  suffix = prefix; 
  for(int j = 1; j < sz(prefix); j++) { 
    prefix[j] = prefix[j] % M * prefix[j - 1] % M; 
  }
  for(int j = sz(suffix) - 2; j >= 0; j--) { 
    suffix[j] = suffix[j] % M * suffix[j + 1] % M; 
  }
  for(int j = 0; j < sz(prefix); j++) { 
    int64_t n_x = x; 
    if(j > 0)              n_x = n_x % M * prefix[j - 1] % M; 
    if(j + 1 < sz(prefix)) n_x = n_x % M * suffix[j + 1] % M; 
    dfs2(ord[j], u, (1 + n_x) % M); 
  }
  return; 
}

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  cin >> N >> M; 
  g.resize(N); 
  dyn.resize(N); 
  for(int i = 0, x, y; i < N - 1; i++) { 
    cin >> x >> y; 
    --x, --y; 
    g[x].push_back(y); 
    g[y].push_back(x); 
  } 
  dfs(0, -1); 
  dfs2(0, -1, 1);
  for(int i = 0; i < N; i++) { 
    cout << dyn[i] << '\n'; 
  }
  return 0; 
}
