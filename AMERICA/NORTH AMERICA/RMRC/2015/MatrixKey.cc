#include "bits/stdc++.h"

using namespace std;

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  int tc; 
  cin >> tc; 
  for(int iter = 0; iter < tc; iter++) { 
    int N, M; 
    cin >> N >> M; 
    vector<vector<char>>g(N, vector<char>(M));
    set<int>rows, cols; 
    for(int i = 0; i < N; i++) { 
      for(int j = 0; j < M; j++) { 
        cin >> g[i][j]; 
      }
    }
    for(int i = 0; i < N; i++) { 
      for(int j = 0; j < M; j++) if(g[i][j] == '1') { 
        rows.insert(i); 
        cols.insert(j); 
      }
    }
    if(rows.size() <= 1 || cols.size() <= 1) { 
      for(int i = 0; i < N; i++) { 
        for(int j = 0; j < M; j++) { 
           cout << (g[i][j] == '1' ? 'P' : 'N');
        }
        cout << '\n'; 
      }
      goto done; 
    }
    for(auto r : rows) { 
      for(auto c : cols) if(g[r][c] == '0') {
        cout << "impossible\n"; 
        goto done;  
      }
    }
    for(int i = 0; i < N; i++) { 
      for(int j = 0; j < M; j++) { 
        cout << (g[i][j] == '1' ? 'I' : 'N');
      }
      cout << '\n'; 
    }
done:
    cout << string(10, '-') << '\n'; 
  }
  return 0; 
}
/*

*/ 
