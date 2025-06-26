#include "bits/stdc++.h"

using namespace std; 

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  int N, K; 
  cin >> N >> K; 
  if(K == 0) { 
    cout << (N == 1 ? "POSSIBLE\n.\n" : "IMPOSSIBLE\n"); 
    return 0; 
  }
  if((N - 1) * (N - 1) + 1 <= K && K <= N * N - N) { 
   cout << "POSSIBLE\n"; 
   vector<vector<char>>ret(N, vector<char>(N, '.')); 
   for(int i = 0; i < N - 1; i++) { 
    for(int j = 0; j < N - 1; j++) { 
      ret[i][j] = '#';   
    }
   }
   ret[N - 1][N - 1] = '#'; 
   K = K - 1 - (N - 1) * (N - 1);
   for(int i = 0; i < N - 1; i++) { 
    if(K == 0) break; 
    K--; 
    ret[i][i] = '.';
    ret[i][N - 1] = '#';
    ret[N - 1][i] = '#';  
   } 
   for(int i = 0; i < N; i++) { 
    for(int j = 0; j < N; j++) { 
      cout << ret[i][j]; 
    }
    cout << '\n'; 
   }
  }
  else { 
    cout << "IMPOSSIBLE\n"; 
  }
  return 0; 
}