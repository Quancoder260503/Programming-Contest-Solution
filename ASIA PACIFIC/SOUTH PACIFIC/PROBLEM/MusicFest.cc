#include "bits/stdc++.h"
 
using namespace std; 
 
#define int64_t long long
#define sz(x) int(x.size())

const int oo = 1e8; 
 
int main(void) { 
  int N, M, K; 
  cin >> N >> M >> K; 
  vector<vector<char>>g(N, vector<char>(M)); 
  for(int i = 0; i < N; i++) { 
   for(int j = 0; j < M; j++) { 
    cin >> g[i][j]; 
   }
  }
  vector<vector<int>>dp_min(N, vector<int>(M, -1)), 
                     dp_max(N, vector<int>(M, -1)), 
                     dp(N,     vector<int>(M, -1)); 
  function<int(int, int)> func_min = [&](int i, int j) -> int { 
   if(i == N - 1 && j == M - 1) return (g[ i][j] - '0'); 
   if(i >= N || j >= M) return oo; 
   int &ret = dp_min[i][j]; 
   if(ret != -1) return ret; 
   ret = (g[i][j] - '0') + min(func_min(i + 1, j), func_min(i, j + 1)); 
   return ret; 
  }; 
  function<int(int, int)> func_max = [&](int i, int j) -> int { 
   if(i == N - 1 && j == M - 1) return (g[i][j] - '0'); 
   if(i >= N || j >= M) return -oo; 
   int &ret = dp_max[i][j]; 
   if(ret != -1) return ret; 
   ret = (g[i][j] - '0') + max(func_max(i + 1, j), func_max(i, j + 1)); 
   return ret; 
  }; 
  function<int(int, int, int)> func = [&](int i, int j, int k) -> int { 
   if(i == N - 1 && j == M - 1) return k + (g[i][j] - '0') == K;
   if(func_min(i, j) + k  > K || K > k + func_max(i, j)) return 0; 
   int &ret = dp[i][j]; 
   if(ret != -1) return ret; 
   ret = func(i + 1, j, k + (g[i][j] - '0')); 
   if(ret) return ret; 
   ret = func(i, j + 1, k + (g[i][j] - '0')); 
   return ret; 
  };  
  cout << func(0, 0, 0) << '\n'; 
  return 0; 
}