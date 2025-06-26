#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int Prob_Num, N, Q; 
  cin >> Q;
  for(int iter = 0; iter < Q; iter++) { 
    cin >> Prob_Num >> N; 
    vector<vector<int>>gr(N), gc(N); 
    for(int i = 0, x; i < N; i++) { 
      cin >> x; 
      gr[x].push_back(i); 
    }
    for(int i = 0, x; i < N; i++) { 
      cin >> x; 
      gc[x].push_back(i); 
    }
    vector<vector<int>>visited(N, vector<int>(N)); 
    queue<pair<int, int>>q;
    for(int i = 0; i < N; i++) { 
      visited[i][i] = true; 
      q.push({i, i}); 
    }
    while(sz(q)) { 
      auto [c, d] = q.front(); 
      q.pop(); 
      for(int i = 0; i < sz(gr[c]); i++) {
        for(int j = 0; j < sz(gr[d]); j++) { 
           int u = gr[c][i], v = gr[d][j]; 
           if(!visited[u][v]) {
            visited[u][v] = true;
            q.push({u, v}); 
           } 
        }
      }
      for(int i = 0; i < sz(gc[c]); i++) { 
        for(int j = 0; j < sz(gc[d]); j++) { 
           int u = gc[c][i], v = gc[d][j]; 
           if(!visited[u][v]) {
            visited[u][v] = true;
            q.push({u, v}); 
           } 
        }
      }
    }
    int ret = true; 
    for(int i = 0; i < N; i++) { 
      for(int j = 0; j < N; j++) { 
        if(visited[i][j]) continue; 
        ret = false; 
      }
    }
    cout << Prob_Num << " " << (ret ? "YES" : "NO") << '\n'; 
  }
  return 0; 
}

