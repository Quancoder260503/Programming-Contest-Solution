#include "bits/stdc++.h"

using namespace std;

const int maxf = 1e4 + 10; 
const int mod = 1e9 + 7; 

int64_t dyn[maxf][120][2][2]; 
string S; 
int D;

int memo(int pos, int rem, int leading_zero, int smaller) {  
  if(pos == S.size()) return (rem == 0 && !leading_zero); 
  int64_t &ret = dyn[pos][rem][leading_zero][smaller]; 
  if(ret != -1) return ret; 
  ret = 0; 
  int bound = (smaller ? S[pos] - '0' : 9); 
  for(int digit = 0; digit <= bound; digit++) { 
    ret += memo(pos + 1, (rem + digit) % D, leading_zero & (digit == 0), smaller & (digit == bound)); 
    ret %= mod; 
  }
  return ret; 
}

int main(void) { 
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  cin >> S >> D; 
  memset(dyn, -1, sizeof(dyn)); 
  cout << memo(0, 0, true, true) << '\n'; 
  return 0; 
}