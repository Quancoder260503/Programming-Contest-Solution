#include "bits/stdc++.h"
 
using namespace std; 
 
#define int64_t long long
#define sz(x) int(x.size())
 
int main(void) { 
  string S; 
  cin >> S; 
  int N = sz(S); 
  vector<int>cc(N), equal(N); 
  for(int i = 0; i < N / 2; i++) {
   equal[i] = (S[i] == S[N - i - 1]);  
   cc[i] = (S[i] == S[N - i - 2]);
  }
  for(int i = 1; i < N / 2; i++) { 
   equal[i] &= equal[i - 1]; 
  }
  for(int i = N / 2 - 2; i >= 0; i--) { 
    cc[i] &= cc[i + 1]; 
  }
  int ans = 0; 
  for(int i = 0; i < N / 2; i++) { 
   if(i) ans += equal[i - 1] & cc[i]; 
   else  ans += cc[i]; 
  }
  if(N % 2 == 1) { 
    ans += equal[N / 2 - 1]; 
  }
  reverse(S.begin(), S.end()); 
  fill(cc.begin(), cc.end(), 0); 
  fill(equal.begin(), equal.end(), 0); 
  for(int i = 0; i < N / 2; i++) {
   equal[i] = (S[i] == S[N - i - 1]);  
   cc[i] = (S[i] == S[N - i - 2]);
  }
  for(int i = 1; i < N / 2; i++) { 
   equal[i] &= equal[i - 1]; 
  }
  for(int i = N / 2 - 2; i >= 0; i--) { 
    cc[i] &= cc[i + 1]; 
  }
  for(int i = 0; i < N / 2; i++) { 
   if(i) ans += equal[i - 1] & cc[i]; 
   else  ans += cc[i]; 
  }
  cout << ans << '\n'; 
  return 0; 
}