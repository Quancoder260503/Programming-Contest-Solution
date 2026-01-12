#include "bits/stdc++.h"

using namespace std; 

const int LOG = 30; 

int main(void) {
  ios_base::sync_with_stdio(0); 
  cin.tie(0); 
  cout.tie(0); 
  int N, M, T; 
  for(cin >> T; T--; ) { 
   cin >> N >> M; 
   vector<vector<int>>a(N, vector<int>(M)), b(N, vector<int>(M)); 
   for(int i = 0; i < N; i++) { 
    for(int j = 0; j < M; j++) { 
     cin >> a[i][j]; 
    }
   }
   for(int i = 0; i < N; i++) { 
    for(int j = 0; j < M; j++) { 
     cin >> b[i][j]; 
    }
   }
   for(int bit = LOG; bit >= 0; bit--) { 
    vector<vector<int>>g(N + M); 
    vector<int>color(N + M); 
    function<int(int)> dfs = [&](int u) -> int { 
     if(color[u] != 0) return false; 
     color[u] = 1; 
     int ret = false; 
     for(auto v : g[u]) { 
      if(color[v] == 2) continue; 
      else if(color[v] == 0) { 
        ret |= dfs(v); 
      }
      else { 
        ret = true; 
      }
     }
     color[u] = 2; 
     return ret; 
    };
    vector<int>row(N), col(M); 
    for(int i = 0; i < N; i++) { 
     for(int j = 0; j < M; j++) { 
      if((a[i][j] >> bit & 1) != (b[i][j] >> bit & 1)) { 
       if(b[i][j] >> bit & 1) col[j] = true; 
       else row[i] = true; 
      }
      if(b[i][j] >> bit & 1) { 
        g[i].push_back(j + N); 
      } else { 
        g[j + N].push_back(i); 
      }
     }
    }
    int state = true; 
    for(int i = 0; i < N; i++) { 
     if(row[i] && dfs(i)) { 
      state = false; 
      break; 
     }
    }
    if(!state) { 
     cout << "No\n"; 
     goto done;    
    } 
    for(int j = 0; j < M; j++) { 
     if(col[j] && dfs(N + j)) { 
      state = false; 
     }
    }
    if(!state) { 
     cout << "No\n"; 
     goto done; 
    }
   }
   cout << "Yes\n"; 
done:; 
  }
  return 0; 
}
