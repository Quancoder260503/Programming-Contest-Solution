#include "bits/stdc++.h"

using namespace std;

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);
 string S, T; 
 cin >> S >> T; 
 if(S == T) { 
  cout << "Yes\n"; 
  return 0; 
 }
 for(int i = 0; i < 10; i++) { 
  string c(1, '0' + i); 
  string pc = c + T; 
  string ac = T + c; 
  if(pc == S || ac == S) { 
    cout << "Yes\n"; 
    return 0; 
  }
 }
 string rT = T; 
 for(int i = 0; i < rT.size(); i++) { 
  if('0' <= rT[i] && rT[i] <= '9') continue; 
  rT[i] = ('a' <= rT[i] ? toupper(rT[i]) : tolower(rT[i])); 
 }
 if(rT == S) { 
  cout << "Yes\n";
  return 0;  
 }
 cout << "No\n"; 
 return 0; 
}