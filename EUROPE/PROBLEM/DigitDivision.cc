#include "bits/stdc++.h"

using namespace std;

#define sz(x) int(x.size())
const int mod = 1e9 + 7; 

int main(void) {
  ios_base::sync_with_stdio(false); 
  cin.tie(0); 
  cout.tie(0); 
  string S;
  int N, M, acc = 0, rem = 0;  
  cin >> N >> M >> S; 
  for(int i = 0; i < sz(S); i++) { 
    rem = (10 * rem + S[i] - '0') % M; 
    acc += (rem == 0);  
  }
  int64_t ret = 1; 
  for(int i = 1; i < acc; i++) { 
    ret = ret * 2 % mod; 
  }
  cout << (rem ? 0 : ret) << '\n'; 
  return 0;
}