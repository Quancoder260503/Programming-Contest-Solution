#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

const int MOD = 1e9 + 7;
const int maxf = 1002;  

int g[1002], K;
string S;  
int64_t dp[1004][1004][2]; 

void init() {
 g[0] = -1;
 g[1] = 0; 
 for(int i = 2; i < maxf; i++) { 
  g[i] = g[__builtin_popcount(i)] + 1; 
 }
 return; 
}

int64_t memo(int isEqual, int pos, int numOnes) { 
 if(pos == sz(S)) return (g[numOnes] == K - 1); 
 int64_t &ret = dp[pos][numOnes][isEqual]; 
 if(ret != -1) return ret; 
 if(isEqual) { 
  switch(S[pos]) { 
   case '0' : 
    ret = memo(isEqual, pos + 1, numOnes);
    break; 
   default : 
    ret = (memo(isEqual, pos + 1, numOnes + 1) + 
           memo(false,   pos + 1, numOnes)) % MOD; 
  }
 } else { 
   ret = (memo(isEqual, pos + 1, numOnes + 1) + 
          memo(isEqual, pos + 1, numOnes)) % MOD; 
 }
 return ret;
}

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  init(); 
  cin >> S >> K; 
  if(K == 0) { 
   cout << 1 << '\n'; 
   return 0; 
  }
  if(K == 1) { 
   cout << sz(S) - 1 << '\n'; 
   return 0; 
  }
  memset(dp, -1, sizeof(dp)); 
  cout << memo(true, 0, 0) << '\n';   
  return 0; 
}
