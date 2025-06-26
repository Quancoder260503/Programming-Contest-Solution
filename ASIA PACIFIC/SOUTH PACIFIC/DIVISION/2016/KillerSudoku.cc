#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  string s; 
  getline(cin, s); 
  vector<vector<int>>g; 
  vector<vector<int>>graph(9 * 9); 
  for(int iter = 0; iter < 17; iter++) { 
    getline(cin, s);
    string parse; 
    if(iter % 2 == 0) {    
      vector<int>c; 
      for(int i = 0; i < sz(s); i++) { 
        if(s[i] == ' ') continue; 
        parse += s[i]; 
      }     
      for(int i = 1; i < sz(parse) - 1; i++) { 
        if('0' <= parse[i] && parse[i] <= '9') { 
          if(sz(c) + 1 < 9) { 
            if(parse[i + 1] != '|') { 
              graph[(iter / 2) * 9 + sz(c)].push_back((iter / 2) * 9 + sz(c) + 1); 
              graph[(iter / 2) * 9 + sz(c) + 1].push_back((iter / 2) * 9 + sz(c)); 
            }
          }
          c.push_back(parse[i] - '0'); 
        }
      }
      g.push_back(c); 
    }
    else {
      parse = s;  
      int c = 0;  
      for(int i = 0; i < sz(parse); i++) { 
        if(parse[i] == ' ') { 
          int u = (iter - 1) * 9 / 2 + c - 1;
          int v = (iter + 1) * 9 / 2 + c - 1; 
       //   cout << u << " " << v << " " << c - 1 << '\n'; 
          graph[u].push_back(v); 
          graph[v].push_back(u); 
        }
        else if(parse[i] == '+') { 
          c++; 
        }
      }  
    }
  }
  int ret = true;
  for(int i = 0; i < 9; i++) { 
    set<int>s; 
    for(int j = 0; j < 9; j++) { 
      s.insert(g[i][j]); 
    }
    ret &= (sz(s) == 9); 
    s.clear(); 
    for(int j = 0; j < 9; j++) { 
      s.insert(g[j][i]); 
    }
    ret &= (sz(s) == 9); 
  }
  for(int i = 0; i < 9; i += 3) {
    for(int j = 0; j < 9; j += 3) { 
      set<int>s; 
      for(int k1 = 0; k1 < 3; k1++) { 
        for(int k2 = 0; k2 < 3; k2++) { 
          s.insert(g[i + k1][j + k2]); 
        }
      } 
      ret &= (sz(s) == 9); 
    }
  }
  getline(cin, s); 
  if(!ret) { 
    cout << "NotOK\n"; 
    return 0; 
  }
  vector<int>par(9 * 9), sum(9 * 9); 
  iota(par.begin(), par.end(), 0); 
  function<int(int)> find = [&](int u) { 
    return u == par[u] ? u : par[u] = find(par[u]); 
  }; 
  auto join = [&](int u, int v) { 
    int ku = find(u), kv = find(v); 
    if(ku == kv) return; 
    par[kv] = ku; 
    sum[ku] += sum[kv]; 
    return; 
  }; 
  vector<vector<int>>comp(9 * 9); 
  for(int i = 0; i < 81; i++) { 
    sum[i] = g[i / 9][i % 9]; 
  }
  for(int u = 0; u < 81; u++) {
    for(auto v : graph[u]) { 
      join(u, v); 
    }
  }
  for(int i = 0; i < 81; i++) { 
    comp[find(i)].push_back(g[i / 9][i % 9]); 
  }
  for(int i = 0; i < 81; i++) {
    for(int x = 0; x < sz(comp[i]); x++) { 
      for(int y = x + 1; y < sz(comp[i]); y++) { 
        if(comp[i][x] == comp[i][y]) { 
          cout << "NotOK"; 
          return 0; 
        }
      }
    }
  }
  int r, c, total; 
  while(cin >> r >> c >> total) { 
    --r, --c; 
    ret &= (sum[find(r * 9 + c)] == total); 
  }
  cout << (ret ? "" : "Not") << "OK" << '\n';  
  return 0; 
}
