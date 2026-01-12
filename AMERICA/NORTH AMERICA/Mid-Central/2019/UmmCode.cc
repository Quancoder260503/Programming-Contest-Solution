#include "bits/stdc++.h"

using namespace std;

int main(void) {
 ios_base::sync_with_stdio(false); 
 cin.tie(0); 
 cout.tie(0);
 string curr, s, ret; 
 while(cin >> curr) { 
  int good = true; 
  string cc; 
  for(int j = 0; j < curr.size(); j++) {
   if('a' <= curr[j] && curr[j] <= 'z') cc += curr[j]; 
   if('A' <= curr[j] && curr[j] <= 'Z') cc += curr[j]; 
  }
  for(int j = 0; j < cc.size(); j++) { 
   good &= (cc[j] == 'm' || cc[j] == 'u'); 
  }
  if(good) { 
   s += cc; 
  }
 }
 for(int i = 0; i < s.size(); i += 7) { 
  string c = s.substr(i, 7); 
  reverse(c.begin(), c.end()); 
  int ord = 0; 
  for(int j = 0; j < c.size(); j++) { 
   ord += (c[j] == 'u' ? 1 : 0) * (1 << j); 
  }
  ret += char(ord); 
 }
 cout << ret << '\n'; 
 return 0; 
}