#include "bits/stdc++.h"
using namespace std; 

#define sz(x) int(x.size())

const int MOD = 1e9 + 7; 

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0); 
 int y; 
 cin >> y; 
 for(int base = 2; base <= 16; base++) {
  vector<char>cc; 
  int x = y; 
  while(x) { 
   cc.push_back(x % base <= 9 ? x % base + '0' : (x % base) - 10 + 'a'); 
   x = x / base; 
  }
  if(sz(cc) >= 2 && cc[0] == '0' && cc[1]  == '0') { 
    cout << base << " "; 
    reverse(cc.begin(), cc.end()); 
    for(auto &v : cc) { 
     cout << v; 
    } 
    cout << '\n'; 
    return 0; 
  }
 }
 cout << "impossible\n"; 
 return 0; 
}