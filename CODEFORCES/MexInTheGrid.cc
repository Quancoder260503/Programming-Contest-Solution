#include "bits/stdc++.h"

using namespace std; 

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N, T; 
 for(cin >> T; T--; ) { 
  cin >> N; 
  vector<vector<int>>ret(N, vector<int>(N, -1));
  int x = N / 2, y = N / 2; 
  if(N % 2 == 0) { 
    x--, y--; 
  }
  ret[x][y] = 0; 
  int value = 1, s = 1; 
  const int dx[4] = {0, 1, 0, -1}; 
  const int dy[4] = {1, 0, -1, 0};
  while (value < N * N) {
   for(int k = 0; k < 4; k++) {  
    int cc = s;  
    s += k % 2; 
    for(int _ = 0; _ < cc; _++) { 
      x += dx[k], y += dy[k]; 
      if(0 <= x && x < N && 0 <= y && y < N && ret[x][y] == -1) { 
       ret[x][y] = value++; 
      }
      if(value >= N * N) { 
        break; 
      }
    }
    if(value >= N * N) { 
      break; 
    }
   }
  }
  for(int i = 0; i < N; i++) { 
    for(int j = 0; j < N; j++) { 
      cout << ret[i][j] << " "; 
    }
    cout << '\n'; 
  }
 }
 return 0; 
}