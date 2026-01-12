#include "bits/stdc++.h"

using namespace std; 

#define sz(x) int(x.size())

int main(void) { 
 ios_base::sync_with_stdio(false); 
 cin.tie(nullptr); 
 int n;
 cin >> n; 
 pair<int, int>ans; 
 for(int i = 0; i < n; i++) { 
  string s; 
  cin >> s; 
  function<pair<int, int>(int)> hex_to_dec = [&](int idx) { 
   if(idx == -1) return make_pair(0, 0); 
   char c = s[idx]; 
   int val_c = (c >= 'A' ? c - 'A' + 10 : c - '0');
   int val_d = val_c; 
   if(c == '0') {
    val_c = 13;
    if(idx == 0 && sz(s) > 1) val_d = 13;  
   }
   if(c == 'D') { 
    if(idx == 0 && sz(s) > 1) val_d = 13;
    else val_d = 0;  
   }
   if(c == '8') val_c = 11; 
   if(c == 'B') val_d = 8;   
   auto cc = hex_to_dec(idx - 1); 
   return make_pair(val_c + 16 * cc.first, val_d + 16 * cc.second);  
  }; 
  auto res = hex_to_dec(sz(s) - 1); 
  ans.first += res.first; 
  ans.second += res.second;
  //cout << ans.first << ' ' << ans.second << " " << s << '\n';   
}
 cout << hex << uppercase << ans.first << '\n'; 
 cout << hex << uppercase << ans.second << '\n'; 
 return 0; 
}
