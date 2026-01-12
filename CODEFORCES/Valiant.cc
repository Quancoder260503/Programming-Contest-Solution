#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int maxn = 1e7 + 2; 

int64_t suffix[maxn]; 

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  int n, m, T; 
  for(cin >> T; T--; ) { 
   cin >> n >> m;
   vector<vector<int>>g(n, vector<int>(m)), c(n, vector<int>(m)); 
   for(int i = 0; i < n; i++) { 
    for(int j = 0; j < m; j++) { 
     cin >> g[i][j]; 
    }
   } 
   auto sum_2D = [&](int i, int j, int i1, int j1) { 
    return c[i1][j1] - (i ? c[i - 1][j1] : 0) - (j ? c[i1][j - 1] : 0) + (i && j ? c[i - 1][j - 1] : 0); 
   }; 
   auto check = [&](int l) { 
    for(int i = 0; i < n; i++) { 
     for(int j = 0; j < m; j++) { 
      c[i][j] = (g[i][j] >= l); 
      if(i) c[i][j] += c[i - 1][j]; 
      if(j) c[i][j] += c[i][j - 1]; 
      if(i && j) c[i][j] -= c[i - 1][j - 1]; 
     }
    }
    for(int i = 0; i < n; i++) { 
     for(int j = 0; j < m; j++) { 
      if(i + l - 1 < n && j + l - 1 < m && sum_2D(i, j, i + l - 1, j + l - 1) == l * l) { 
        return true; 
      }
     }
    }
    return false; 
   }; 
   int lo = 1; 
   int hi = 1e9; 
   while(lo < hi) { 
    int mid = (lo + hi + 1) / 2; 
    if(check(mid)) lo = mid; 
    else hi = mid - 1; 
   }
   cout << lo << '\n'; 
  } 
  return 0; 
}
