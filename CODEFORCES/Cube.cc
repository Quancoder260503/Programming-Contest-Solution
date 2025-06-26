#include "bits/stdc++.h"

using namespace std; 

const int oo = 1e9; 

int N, pN; 
vector<vector<int>>dp; 
vector<vector<vector<int>>>grid;

int memo(int maskSpace, int maskCol) { 
  if(maskSpace == pN && maskCol == pN) return 0; 
  if(dp[maskSpace][maskCol] != -1) return dp[maskSpace][maskCol]; 
  int ret = oo;
  int row = __builtin_popcount(maskSpace); 
  for(int z = 0; z < N; z++) { 
   if(maskSpace >> z & 1) continue; 
   for(int col = 0; col < N; col++) { 
    if(maskCol >> col & 1) continue; 
    ret = min(ret, grid[z][row][col] + memo(maskSpace | (1 << z), maskCol | (1 << col))); 
   }
  }
  return dp[maskSpace][maskCol] = ret; 
}

int main(void) {  
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);  
 cin >> N;  
 for(int i = 0; i < N; i++) { 
  vector<vector<int>>g(N, vector<int>(N)); 
  for(int j = 0; j < N; j++) { 
   for(int k = 0; k < N; k++) { 
    cin >> g[j][k]; 
   }
  }
  grid.push_back(g); 
 }
 dp.resize(1 << N, vector<int>(1 << N, -1)); 
 pN = (1 << N) - 1; 
 cout << memo(0, 0) << '\n'; 
 return 0;
}