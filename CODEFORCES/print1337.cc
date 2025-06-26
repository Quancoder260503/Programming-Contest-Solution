#include "bits/stdc++.h"

using namespace std; 

const int MOD = 998244353; 

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);
 int N, T; 
 for(cin >> T; T--; ) { 
  cin >> N;
  int len = 0; 
  while(len * (len + 1) / 2 <= N) { 
   len++; 
  }
  N = N - len * (len - 1) / 2;
  string ret = "133";
  for(int i = 0; i < N; i++) { 
   ret = ret + '7'; 
  } 
  len = len - 2; 
  for(int i = 0; i < len; i++) { 
   ret = ret + '3'; 
  }
  ret += '7'; 
  cout << ret << '\n'; 
 }
 return 0; 
}