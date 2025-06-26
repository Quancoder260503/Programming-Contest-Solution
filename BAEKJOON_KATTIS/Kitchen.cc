#include <bits/stdc++.h> 

using namespace std; 

#define sz(x) int(x.size())

int main(void) {
 string S, t; 
 cin >> S >> t;
 int cnt_v = 0, cnt_h = 0; 
 for(int i = 0; i < sz(t); i++) { 
  cnt_h += (t[i] == 'h' || t[i] == 'r'); 
  cnt_v += (t[i] == 'v' || t[i] == 'r'); 
 } 
 if(cnt_h % 2 == 1) {  
  reverse(S.begin(), S.end()); 
  for(int i = 0; i < sz(S); i++) { 
    if(S[i] == 'b') S[i] = 'd'; 
    else if(S[i] == 'd') S[i] = 'b'; 
    else if(S[i] == 'p') S[i] = 'q'; 
    else S[i] = 'p'; 
  } 
 }
 if(cnt_v % 2 == 1) { 
  for(int i = 0; i < sz(S); i++) { 
    if(S[i] == 'b') S[i] = 'p'; 
    else if(S[i] == 'd') S[i] = 'q'; 
    else if(S[i] == 'p') S[i] = 'b'; 
    else S[i] = 'd'; 
  }      
 }
 cout << S << '\n'; 
 return 0; 
} 