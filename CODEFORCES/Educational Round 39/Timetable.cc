#include "bits/stdc++.h"
 
using namespace std; 
 
#define sz(x) int(x.size())
const int oo = 1e8; 
 
int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N, M, K; 
  cin >> N >> M >> K; 
  vector<vector<char>>g(N, vector<char>(M)); 
  for(int i = 0; i < N; i++) { 
    for(int j = 0; j < M; j++) { 
      cin >> g[i][j]; 
    } 
  }
  vector<vector<int>>dp(N + 1, vector<int>(K + 1, oo)); 
  dp[0][0] = 0; 
  for(int i = 0; i < N; i++) { 
    vector<int>prefix(M); 
    for(int j = 0; j < M; j++) { 
      prefix[j] = prefix[max(0, j - 1)] + (g[i][j] == '1'); 
    }
    vector<int>skip(M + 1, oo); 
    for(int j = 0; j < M; j++) { 
      for(int k = j; k < M; k++) { 
        int numSkip = (j ? prefix[j - 1] : 0) + (prefix[M - 1] - prefix[k]); 
        skip[numSkip] = min(skip[numSkip], k - j + 1); 
      }
    }
    skip[prefix.back()] = 0; 
    for(int j = 0; j <= K; j++) { 
      for(int k = 0; k + j <= K && k < sz(skip); k++) { 
        dp[i + 1][j + k] = min(dp[i + 1][j + k], dp[i][j] + skip[k]); 
      }  
    }
  }
  for(int i = 1; i <= K; i++) { 
    dp[N][i] = min(dp[N][i], dp[N][i - 1]); 
  }
  cout << dp[N][K] << '\n'; 
  return 0; 
}
/*
 skip[i] = {what is the minimum number of hours to go to class such that we can skip exactly ith class} 

*/ 