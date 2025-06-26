#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())

const int maxf = 2000; 
const int mod = 1e9 + 7; 

int64_t dyn[maxf][maxf][2]; 
string S; 
int N, K; 

int64_t memo(int pos, int ones, int carry) { 
  if(pos == N) return (ones == carry);
  if(ones < 0) return 0;  
  int64_t &ret = dyn[pos][ones][carry];
  if(ret != -1) return ret;
  ret = 0; 
  if(carry) {
    if(S[pos] == '0') { 
      ret += (memo(pos + 1, ones - 1, false) + memo(pos + 1, ones, true)) % mod;  
      ret %= mod; 
    }
    else {
      ret += (memo(pos + 1, ones - 1, true) + memo(pos + 1, ones, true)) % mod;   
      ret %= mod; 
    }
  }
  else { 
    if(S[pos] == '0') { 
      ret += (memo(pos + 1, ones - 1, false) + memo(pos + 1, ones, false)) % mod;  
      ret %= mod; 
    }
    else {
      ret += (memo(pos + 1, ones, true) + memo(pos + 1, ones - 1, false)) % mod;   
      ret %= mod; 
    }
  }
  return ret;    
}


int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0);
  memset(dyn, -1, sizeof(dyn)); 
  cin >> N >> K >> S; 
  reverse(S.begin(), S.end());   
  cout << memo(0, K, 0) << '\n'; 
  return 0; 
}
/*

*/ 