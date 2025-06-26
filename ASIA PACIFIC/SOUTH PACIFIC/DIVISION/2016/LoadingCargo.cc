#include "bits/stdc++.h"

#pragma GCC target("popcnt")

using namespace std; 

#define sz(x) int(x.size())

const int maxf = 2e3 + 10; 

vector<int>g[maxf], cc[maxf]; 
int visited[maxf], col[maxf], N, L, R, C; 
bitset<2010>dyn[maxf]; 

void dfs(int u, int c, int ind) {
  col[u] = c;  
  visited[u] = true;
  cc[ind].push_back(u); 
  for(auto v : g[u]) { 
    if(visited[v]) {
      if(col[u] == col[v]) { 
        cout << "No\n"; 
        exit(0);  
      }
    }
    else { 
      dfs(v, c ^ 3, ind); 
    }
  }
  return; 
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  cin >> L >> R >> N >> C; 
  if(C == 0) { 
    cout << (N <= L + R  ? "Yes" : "No") << '\n'; 
    return 0; 
  }
  for(int i = 0, u, v; i < C; i++) { 
    cin >> u >> v; 
    g[u].push_back(v); 
    g[v].push_back(u); 
  }
  int ctr = 0; 
  memset(visited, 0, sizeof(visited)); 
  vector<pair<int, int>>bags; 
  for(int i = 0; i < N; i++) {
    if(visited[i]) continue;
    dfs(i, 1, ctr++);
    bags.emplace_back(0, 0); 
    for(auto v : cc[ctr - 1]) { 
      (col[v] == 1 ? bags.back().first : bags.back().second)++;   
    }
  }
  dyn[0][0] = true;
  for(int i = 1; i <= sz(bags); i++) {
    int red = bags[i - 1].first, black = bags[i - 1].second; 
    for(int j = L; j >= 0; j--) {         
      if(j >= red)   dyn[j] |= (dyn[j - red] << black);
      if(j >= black) dyn[j] |= (dyn[j - black] << red); 
    } 
  } 
  int ret = false; 
  for(int i = 0; i <= L; i++) { 
    if(N - i <= R && dyn[i][N - i]) { 
      ret = true; 
      break; 
    }
  }
  cout << (ret ? "Yes" : "No") << '\n'; 
  return 0; 
}