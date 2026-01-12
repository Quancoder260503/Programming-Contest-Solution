#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int oo = 1e9; 

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);
 int n, m; 
 cin >> n >> m; 
 vector<vector<char>>g(n, vector<char>(m)); 
 vector<int>freeRow(n), freeCol(m); 
 for(int i = 0; i < n; i++) { 
  for(int j = 0; j < m; j++) { 
   cin >> g[i][j]; 
  }
 }
 for(int i = 0; i < n; i++) { 
  for(int j = 0; j < m; j++) { 
   freeRow[i] += (g[i][j] == '.');  
  }
 }
 for(int i = 0; i < m; i++) { 
  for(int j = 0; j < n; j++) { 
   freeCol[i] += (g[j][i] == '.'); 
  }
 }
 vector<vector<vector<int64_t>>>dp(n, vector<vector<int64_t>>(m, vector<int64_t>(4))); 
 for(int i = 0; i < n; i++) { 
  for(int j = 0; j < m; j++) { 
   if(g[i][j] == '#') continue;
   dp[i][j][0] = 1; 
  }
 }
 for(int k = 1; k < 4; k++) { 
  vector<int64_t>row(n), col(m); 
  for(int i = 0; i < n; i++) { 
   for(int j = 0; j < m; j++) { 
    row[i] += dp[i][j][k - 1]; 
   }
  } 
  for(int i = 0; i < m; i++) { 
   for(int j = 0; j < n; j++) { 
    col[i] += dp[j][i][k - 1]; 
   }
  }
  for(int i = 0; i < n; i++) { 
   for(int j = 0; j < m; j++) { 
    if(g[i][j] == '.') { 
     dp[i][j][k] = row[i] + col[j] - 2 * dp[i][j][k - 1]; 
    } 
   }
  }
 }
 int64_t ret = 0; 
 for(int i = 0; i < n; i++) { 
  for(int j = 0; j < m; j++) { 
   ret += dp[i][j][3]; 
  }
 }
 { 
  for(int i = 0; i < n; i++) { 
   for(int j = 0; j < m; j++) { 
    if(g[i][j] == '.') { 
     int64_t curr = 0; 
     curr += (freeRow[i] - 1) * (freeCol[j] - 1) * 4; 
     curr += (freeRow[i] - 1) * (3 * freeRow[i] - 5); 
     curr += (freeCol[j] - 1) * (3 * freeCol[j] - 5); 
     ret = ret - curr; 
    } 
   }
  }
 }
 cout << ret << '\n'; 
 return 0; 
}