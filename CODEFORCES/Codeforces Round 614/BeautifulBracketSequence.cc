#include "bits/stdc++.h"

using namespace std; 


#define sz(x) int(x.size())

const int mod = 998244353; 
const int maxf = 2500; 

int64_t dyn[maxf][maxf], pw2[maxf]; 

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  pw2[0] = 1; 
  for(int i = 1; i < maxf; i++) { 
    pw2[i] = pw2[i - 1] * 2 % mod; 
  } 
  string S; 
  cin >> S;
  vector<int>prefix(sz(S)); 
  for(int i = 0; i < sz(S); i++) { 
    prefix[i] = (S[i] == '?') + (i ? prefix[i - 1] : 0); 
  }
  auto range = [&](int i, int j) { 
    if(i > j) return 0; 
    return prefix[j] - prefix[i - 1];  
  }; 
  for(int i = sz(S) - 1; i >= 0; i--) { 
    for(int j = i + 1; j < sz(S); j++) { 
      if(S[i] != '(') (dyn[i][j] += dyn[i + 1][j]) %= mod;
      if(S[j] != ')') (dyn[i][j] += dyn[i][j - 1]) %= mod; 
      if(S[i] != '(' && S[j] != ')') (dyn[i][j] += mod - dyn[i + 1][j - 1]) %= mod;  
      if(S[i] != ')' && S[j] != '(') (dyn[i][j] += dyn[i + 1][j - 1] + pw2[range(i + 1, j - 1)]) %= mod;
    }
  }
  cout << dyn[0][sz(S) - 1] << '\n'; 
  return 0; 
}

/*
  dyn[i][j] = {expected maximum value of the correct bracket sequeneces after removal}
  if(Can match) dyn[i][j] = 1 + dyn[i + 1][j - 1]
  if(Not match) dyn[i][j] = dyn[i + 1][j] + dyn[i][j - 1] - dyn[i + 1][j - 1]

*/