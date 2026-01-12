#include "bits/stdc++.h" 

using namespace std; 


int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  int N, M; 
  cin >> N >> M; 
  vector<vector<char>>g(N, vector<char>(M)); 
  for(int i = 0; i < N; i++) { 
   for(int j = 0; j < M; j++) { 
    cin >> g[i][j]; 
   }
  }
  vector<vector<int>>palin(N, vector<int>(M)); 
  for(int col = 0; col < M; col++) { 
   for(int row = 0; row < N; row++) { 
    if(row + 1 < N && g[row][col] == g[row + 1][col]) { 
     int L = row - 1, R = row + 2, len = 0; 
     while(L >= 0 && R < N && g[L][col] == g[R][col]) { 
      L--; 
      R++; 
      len++; 
     }
     for(int ptr = row - len; ptr <= row + 1 + len; ptr++) { 
       palin[ptr][col] = max(palin[ptr][col], 2 * len + 2);   
     }
    } 
    int L = row - 1, R = row + 1, len = 0; 
    while(L >= 0 && R < N && g[L][col] == g[R][col]) { 
      len++; 
      L--; 
      R++;   
    }
    for(int ptr = row - len; ptr <= row + len; ptr++) { 
      palin[ptr][col] = max(palin[ptr][col], 2 * len + 1); 
    } 
   }
  }
  int ans = 0; 
  for(int row = 0; row < N; row++) { 
   for(int col = 0; col < M; col++) { 
    if(col + 1 < M && g[row][col] == g[row][col + 1]) { 
     int L = col - 1, R = col + 2, len = 0; 
     while(L >= 0 && R < M && g[row][L] == g[row][R]) { 
      L--; 
      R++; 
      len++;   
     }   
     for(int ptr = col - len; ptr <= col + len + 1; ptr++) { 
      ans = max(ans, palin[row][ptr] * (2 * len + 2)); 
     }
    }
    int L = col - 1, R = col + 1, len = 0; 
    while(L >= 0 && R < M && g[row][L] == g[row][R]) { 
     len++;
     L--;
     R++;
    }
    for(int ptr = col - len; ptr <= col + len; ptr++) { 
     ans = max(ans, palin[row][ptr] * (2 * len + 1));    
    }
   }
  }
  cout << ans << '\n'; 
  return 0;   
}