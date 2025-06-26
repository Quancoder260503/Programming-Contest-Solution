#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int maxf = 300; 
const int oo = 1e9; 

int dp[maxf][maxf][maxf]; 

int main(void) {    
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int N, K; 
 string S, T; 
 cin >> N >> K >> S >> T; 
 for(int i = 0; i < maxf; i++) { 
  for(int j = 0; j < maxf; j++) { 
   for(int k = 0; k < maxf; k++) { 
    dp[i][j][k] = -oo; 
   }
  }
 }
 int num = 0; 
 for(int i = 0; i < sz(S); i++) { 
  num += (S[i] == T[0]); 
 }
 if(T[0] == T[1]) {
  int cnt = 0;  
  for(int i = 0; i < N; i++) { 
   if(S[i] != T[0]) { 
    if(K > 0) cnt++; 
    K--; 
   } else { 
    cnt++; 
   }
  }
  cout << cnt * (cnt - 1) / 2 << '\n'; 
  return 0;     
 }
 dp[0][0][0] = 0; 
 for(int pos = 0; pos < N; pos++) { 
  for(int change = 0; change <= K; change++) { 
   for(int numFirst = 0; numFirst <= pos; numFirst++) { 
    if(dp[pos][change][numFirst] < 0) continue; 
    if(S[pos] == T[0]) { 
     dp[pos + 1][change][numFirst + 1] = max(dp[pos + 1][change][numFirst + 1], dp[pos][change][numFirst]);
    } else { 
     dp[pos + 1][change + 1][numFirst + 1] = max(dp[pos + 1][change + 1][numFirst + 1], dp[pos][change][numFirst]); 
    }
    if(S[pos] == T[1]) { 
     dp[pos + 1][change][numFirst] = max(dp[pos + 1][change][numFirst], dp[pos][change][numFirst] + numFirst); // already got second 
    } else { 
     dp[pos + 1][change + 1][numFirst] = max(dp[pos + 1][change][numFirst], dp[pos][change][numFirst] + numFirst); // change any character to Second  
    }
    dp[pos + 1][change][numFirst] = max(dp[pos + 1][change][numFirst], dp[pos][change][numFirst]); 
   }
  }
 }
 num = min(num + K, N);
 int ret = 0; 
 for(int amt = 0; amt <= num; amt++) { 
  for(int ops = 0; ops <= K; ops++) { 
   ret = max(ret, dp[N][ops][amt]); 
  } 
 } 
 cout << ret << '\n';  
 return 0; 
}


/**
 * dp[pos][num_ops][num_first_characters_changed]
 * 
 */