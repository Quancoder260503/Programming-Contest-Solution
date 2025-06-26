#include "bits/stdc++.h"

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

using namespace std; 

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);
 int N, M, K;  
 cin >> N >> M >> K; 
 vector<vector<int>>g(N, vector<int>(M)); 
 vector<int>row(K), col(K); 
 for(int i = 0, r, c, d; i < K; i++) { 
  cin >> r >> c >> d;
  --r, --c;  
  row[i] = r, col[i] = c; 
  for(int j = c; j >= 0 && c - j <= d; j--) { 
   g[max(0, r - d + c - j)][j]++;
   if(r + d - (c - j) + 1 < N) { 
    g[r + d - (c - j) + 1][j]--; 
   }
  }
  for(int j = c + 1; j < M && j - c <= d; j++) { 
   g[max(0, r - d + j - c)][j]++; 
   if(r + d - (j - c) + 1 < N) { 
    g[r + d - (j - c) + 1][j]--; 
   } 
  }
 }
 for(int i = 0; i < M; i++) { 
  for(int j = 1; j < N; j++) { 
   g[j][i] += g[j - 1][i]; 
  }
 }
 int curr_max = 0, ind = 0; 
 for(int i = 0; i < K; i++) { 
  if(g[row[i]][col[i]] > curr_max) { 
   ind = i; 
   curr_max = g[row[i]][col[i]]; 
  }
 }
 cout << ind + 1 << " " << curr_max - 1 << '\n'; 
 return 0; 
}